#include <Arduino.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// DHT11 설정
#define DHTPIN D4         // WeMos D1 Mini의 D4 (GPIO2)
#define DHTTYPE DHT11     // 센서 종류

DHT dht(DHTPIN, DHTTYPE);   // DHT 객체 생성

// LCD 설정 (주소는 0x27 또는 0x3F 중 하나일 수 있음)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // 16글자 × 2줄 LCD

void setup() {
  Serial.begin(115200);   // 시리얼 통신 시작
  dht.begin();            // DHT11 시작

  lcd.init();             // LCD 초기화
  lcd.backlight();        // 백라이트 켜기

  lcd.setCursor(0, 0);
  lcd.print("Init DHT11...");
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // 값이 유효한지 확인
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("센서 읽기 실패!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error");
    delay(5000);
    return;
  }

  // 시리얼 출력
  Serial.print("온도: ");
  Serial.print(temperature);
  Serial.print(" *C  |  습도: ");
  Serial.print(humidity);
  Serial.println(" %");

  // LCD 출력
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");

  delay(5000);  // 5초 대기
}