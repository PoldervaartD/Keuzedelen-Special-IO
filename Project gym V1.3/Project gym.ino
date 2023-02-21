#include <LiquidCrystal.h>
#define trigPin 9
#define echoPin 10
const int DISTANCE_THRESHOLD_CM = 20;
const int LED_PIN = 13;

LiquidCrystal lcd(1, 2, 4, 5, 6, 7);

enum ObjectDetectionState {
  NOT_DETECTED,
  DETECTED
};
ObjectDetectionState currentState = NOT_DETECTED;
ObjectDetectionState previousState = NOT_DETECTED;

int repsDetected = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED_PIN, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(3, 0);
  lcd.print("Aantal reps");
}

float calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  float distance = (duration/2) / 29.1;
  return distance;
}

void updateLCD() {
  lcd.setCursor(7, 1);
  lcd.print(repsDetected);
}

void setReady() {
  lcd.begin(16, 2);
  lcd.setCursor(3, 0);
  lcd.print("Set klaar");
  digitalWrite(LED_PIN, HIGH);
}

void loop() {
  float distance = calculateDistance();

  if (distance <= DISTANCE_THRESHOLD_CM) {
    currentState = DETECTED;
  } else {
    currentState = NOT_DETECTED;
  }

  if (currentState != previousState) {
    if (currentState == DETECTED) {
      repsDetected++;
      updateLCD();
    }
  }

  if (repsDetected >= 10) {
    setReady();
  }

  previousState = currentState;
  delay(500);
}
