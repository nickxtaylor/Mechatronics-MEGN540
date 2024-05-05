#include <Servo.h>

Servo servo1;
Servo servo2;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 90;    // variable to store the servo position
const int ledPin = 13;
float topleft;
float topright;
float downleft;
float downright;

void setup() {

  // myservo.write(0);
  servo1.attach(9);
  servo2.attach(10);  // attaches the servo on pin 9 to the servo object

   // setup led pin as output
  pinMode(ledPin, OUTPUT);

  // for use in led pin blinking
  Serial.begin(9600);
  
}

void loop() {

  // myservo.write(90);

  // get voltage drop over photoresistors
  topright = analogRead(A0) * (5.2 / 1023.0); // R1
  downleft = analogRead(A1) * (5.2 / 1023.0); // R2
  topleft = analogRead(A2) * (5.2 / 1023.0); // R3
  downright = analogRead(A3) * (5.2 / 1023.0); // R4.

  for (pos = 15; pos <= 175; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo1.write(pos);   
    servo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }

  // display one blink on the led
  digitalWrite(ledPin, HIGH);
  delay(200);
  digitalWrite(ledPin, LOW);
  delay(200);

  for (pos = 175; pos >= 15; pos -= 1) { // goes from 180 degrees to 0 degrees
    servo1.write(pos);   
    servo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }

  // display one blink on the led
  digitalWrite(ledPin, HIGH);
  delay(200);
  digitalWrite(ledPin, LOW);
  delay(200);

  // Print variables to the Serial Monitor
  Serial.print("R1: ");
  Serial.println(topright);
  
  Serial.print("R2; ");
  Serial.println(downleft);

  Serial.print("R3: ");
  Serial.println(topleft);

  Serial.print("R4: ");
  Serial.println(downright);

}

