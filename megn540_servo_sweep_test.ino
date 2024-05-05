#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 90;    // variable to store the servo position
const int ledPin = 13;

void setup() {

  // myservo.write(0);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

   // setup led pin as output
  pinMode(ledPin, OUTPUT);

  // for use in led pin blinking
  Serial.begin(9600);
  
}

void loop() {

  // myservo.write(90);

  for (pos = 5; pos <= 175; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }

  // display one blink on the led
  digitalWrite(ledPin, HIGH);
  delay(200 );
  digitalWrite(ledPin, LOW);
  delay(200);

  for (pos = 175; pos >= 5; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }

  // display one blink on the led
  digitalWrite(ledPin, HIGH);
  delay(200);
  digitalWrite(ledPin, LOW);
  delay(200);
}

