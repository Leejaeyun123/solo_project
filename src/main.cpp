#include <Arduino.h>            // 아두이노 기본 함수들 (예: pinMode, digitalWrite, delay)을 사용할 수 있음
#include <DHT.h>                // DHT 시리즈 센서를 제어하기 위한 라이브러리
#include <LiquidCrystal_I2C.h>  // I2C 방식의 LCD (16x2 등)를 제어하기 위한 라이브러리
#include <Wire.h>               // I2C 통신을 위한 기본 라이브러리

#define DHTPIN D4               // DHT11 센서의 데이터 핀을 D4에 연결
#define DHTTYPE DHT11           // 사용할 센서가 DHT11이라는 것을 명시

DHT dht(DHTPIN, DHTTYPE);       // DHT 센서 객체를 생성

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD 객체를 생성하며, 주소 0x27 (보통 기본값)이고 크기는 16x2 문자형

void setup() {                  // 아두이노가 처음 전원을 켜거나 리셋되었을 때 실행. 초기화 코드 (센서 설정, 시리얼 통신 시작, 핀모드 설정 등)를 이곳에 작성. 한 번만 실행되는 함수
  Serial.begin(115200);         // 시리얼 통신 시작 (115200bps로 PC와 아두이노 간 데이터 주고받기)
  dht.begin();                  // DHT11 센서 초기화 (센서가 동작하도록 준비)

  lcd.init();                   // I2C LCD 초기화 (LCD 사용 시작)
  lcd.backlight();              // LCD 백라이트 켜기 (글자 보기 위해)

  lcd.setCursor(0, 0);          // LCD 화면의 첫 번째 줄, 첫 번째 칸으로 커서 이동
  lcd.print("Init DHT11...");   // LCD에 초기화 메시지 출력
}

void loop() {                                   // 센서 값을 읽거나, 데이터를 처리하거나, 화면을 갱신하는 등의 지속적인 동작을 이곳에 작성. 계속 반복되는 함수
  float humidity = dht.readHumidity();          // 습도 측정 (0~100%)
  float temperature = dht.readTemperature();    // 온도 측정 (섭씨)

  // 측정값이 비정상이면 (예: 센서 연결 실패 시)
  if (isnan(humidity) || isnan(temperature)) {  
    Serial.println("센서 읽기 실패!");           //  // PC 시리얼 모니터에 오류 메시지 출력
    lcd.clear();                                // LCD 화면 지우기
    lcd.setCursor(0, 0);                        // LCD 첫 번째 줄의 첫 번째 칸으로 커서를 이동
    lcd.print("Sensor Error");                  // 에러 메시지 출력
    delay(5000);                                // 5초 대기 (사용자에게 메시지 보이도록)
    return;                                     // loop 끝내고 다시 반복
  }

  // 시리얼 모니터 출력 (정상 상태)
  Serial.print("온도: ");           // PC의 시리얼 모니터에 "온도: "라는 텍스트를 출력
  Serial.print(temperature);        // 측정된 온도값(float)을 출력
  Serial.print(" *C  |  습도: ");   // 단위 표시와 함께 습도 출력을 준비
  Serial.print(humidity);           // 측정된 습도값(float)을 출력
  Serial.println(" %");             // 습도의 단위 %를 출력하고 줄 바꿈. println()은 출력 후 자동 줄 바꿈이 포함

  // LCD 출력 (화면에 현재 온도/습도 표시)
  lcd.clear();            // LCD 화면의 모든 문자를 지우고 초기화
  lcd.setCursor(0, 0);    // LCD 첫 번째 줄의 첫 번째 칸으로 커서를 이동
  lcd.print("Temp: ");    // LCD에 "Temp: "라는 텍스트를 출력
  lcd.print(temperature); // LCD에 측정된 온도(float 값)을 출력
  lcd.print(" C");        // 온도 단위를 출력

  lcd.setCursor(0, 1);      // LCD 두 번째 줄의 첫 번째 칸으로 커서를 이동
  lcd.print("Humidity: ");  // "Humidity: " 텍스트를 출력
  lcd.print(humidity);      // 측정된 습도(float 값)을 LCD에 출력
  lcd.print(" %");          // 습도의 단위 %를 출력

  delay(5000);              // 5초간 대기
}