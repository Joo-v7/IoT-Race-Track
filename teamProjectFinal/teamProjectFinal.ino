#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// I2C LCD 설정
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C 주소가 0x27인 16x2 LCD

// 서보 설정
Servo myServo;
const int servoPin = 6;

// 초음파 센서 설정
const int trigPin = 9;
const int echoPin = 8;

// 결승선 감지 거리 기준값 (5cm)
const int finishLineThreshold = 5;

// 부저 핀
const int buzzerPin = 5;

// 시간 측정 변수
unsigned long startTime;
unsigned long endTime;
bool raceStarted = false;

void setup() {
  // I2C LCD 초기화
  lcd.init();
  lcd.backlight();
  lcd.print("Ready");

  // 서보 초기화
  myServo.attach(servoPin);
  myServo.write(0); // 시작 차단기 닫힘 상태

  // 초음파 센서 핀 초기화
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // 부저 핀 초기화
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  // 시리얼 통신 시작
  Serial.begin(9600);
}

void loop() {
  if (!raceStarted) {
    // 레이스가 시작되지 않은 경우
    raceStarted = true;
    
    // 부저 소리 출력
    tone(buzzerPin, 392); // "시(C)" 주파수 (Hz)
    delay(100);
    noTone(buzzerPin);
    delay(1000);
    tone(buzzerPin, 392); // "시(C)" 주파수 (Hz)
    delay(100);
    noTone(buzzerPin);
    delay(1000);
    tone(buzzerPin, 392); // "시(C)" 주파수 (Hz)
    delay(100);
    noTone(buzzerPin);
    delay(1000);
    tone(buzzerPin, 523); // "높은 도(C)" 주파수 (Hz)
    delay(100);
    noTone(buzzerPin);
    
    // LCD 업데이트 - 부저 마지막 소리에 맞춰 표시
    lcd.clear();
    lcd.print("Start!!");

    // 타이머 시작
    startTime = millis();
    
    // 서보 모터 동작
    myServo.write(100); // 시작 차단기 열림
    delay(3000);
    myServo.write(10); // 시작 차단기 닫힘
  }

  // 결승선에 도착 여부 확인
  bool finishLineReached = checkFinishLine(trigPin, echoPin);

  // 결승선에 도착했으면 레이스 종료
  if (finishLineReached) {
    endTime = millis();
    unsigned long lapTime = endTime - startTime;

    // LCD에 걸린 시간 출력
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Lap Time:");
    lcd.setCursor(0, 1);
    lcd.print(lapTime / 1000.0);
    lcd.print(" sec");

    // 프로그램 종료
    while (true) {}
  }

  delay(100);
}

// 초음파 센서를 사용하여 결승선에 도착 여부를 확인하는 함수
bool checkFinishLine(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  long distance = (duration / 2) / 29.1;

  // 결승선 감지 거리 기준값 이내면 true 반환
  if (distance < finishLineThreshold) {
    return true;
  } else {
    return false;
  }
}

