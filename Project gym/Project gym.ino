#include <LiquidCrystal.h>  
 #define trigPin 9
 #define echoPin 10
 // initialize the library with the numbers of the interface pins
 LiquidCrystal lcd(1, 2, 4, 5, 6, 7);
 int counter = 0;
 int currentState = 0;
 int previousState = 0;
 
 void setup() {
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 lcd.begin(16, 2);
 lcd.setCursor(3, 0);
 lcd.print("Aantal reps");
 }
 
 void loop() {
 long duration, distance;
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 distance = (duration/2) / 29.1;
 if (distance <= 20){  
 currentState = 1;
 }
 else {
 currentState = 0;
 }
 delay(100);
 if(currentState != previousState){
 if(currentState == 1){
 counter = counter + 1;
 lcd.setCursor(7,1);
 lcd.print(counter);
    }
  }
  if (counter >=10){
    lcd.begin(16, 2);
    lcd.setCursor(3, 0);
    lcd.print("Set klaar");
  }
 }