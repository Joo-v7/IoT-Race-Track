#define TRIG_PIN1 2
#define ECHO_PIN1 3
#define TRIG_PIN2 4
#define ECHO_PIN2 5
#define TRIG_PIN3 6
#define ECHO_PIN3 7
#define TRIG_PIN4 8
#define ECHO_PIN4 9

#define LED_PIN1 10
#define LED_PIN2 11
#define LED_PIN3 12
#define LED_PIN4 13

long readUltrasonicDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH) / 58.2; // cm로 변환
}

void setup() {
  pinMode(TRIG_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);
  pinMode(TRIG_PIN2, OUTPUT);
  pinMode(ECHO_PIN2, INPUT);
  pinMode(TRIG_PIN3, OUTPUT);
  pinMode(ECHO_PIN3, INPUT);
  pinMode(TRIG_PIN4, OUTPUT);
  pinMode(ECHO_PIN4, INPUT);

  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN3, OUTPUT);
  pinMode(LED_PIN4, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  long distance1 = readUltrasonicDistance(TRIG_PIN1, ECHO_PIN1);
  long distance2 = readUltrasonicDistance(TRIG_PIN2, ECHO_PIN2);
  long distance3 = readUltrasonicDistance(TRIG_PIN3, ECHO_PIN3);
  long distance4 = readUltrasonicDistance(TRIG_PIN4, ECHO_PIN4);

  if (distance1 > 0 && distance1 < 10) { 
    digitalWrite(LED_PIN1, HIGH);
  } else {
    digitalWrite(LED_PIN1, LOW);
  }

  if (distance2 > 0 && distance2 < 10) {
    digitalWrite(LED_PIN2, HIGH);
  } else {
    digitalWrite(LED_PIN2, LOW);
  }

  if (distance3 > 0 && distance3 < 10) {
    digitalWrite(LED_PIN3, HIGH);
  } else {
    digitalWrite(LED_PIN3, LOW);
  }

  if (distance4 > 0 && distance4 < 10) {
    digitalWrite(LED_PIN4, HIGH);
  } else {
    digitalWrite(LED_PIN4, LOW);
  }

  delay(100);
}
