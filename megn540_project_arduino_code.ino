#include <Servo.h>

// servo motor structure
Servo yaw;
Servo pitch;

// variable allocations
float topleft;
float topright;
float downleft;
float downright;
float cutoff;
int pos_yaw;
int pos_pitch;
const int ledPin = 13;

void setup() {

  // attach motors to associated arduino pins
  pitch.attach(9); // pinMode(9, OUTPUT);
  yaw.attach(10); // pinMode(10, OUTPUT);

  // setup led pin as output
  pinMode(ledPin, OUTPUT);

  // for use in led pin blinking
  Serial.begin(9600);

  // setup constanst
  cutoff = 3;
  pos_yaw = 90;
  pos_pitch = 90;

}

void loop() {

  // get voltage drop over photoresistors
  topright = analogRead(A2) * (5.2 / 1023.0); // R1
  downleft = analogRead(A0) * (5.2 / 1023.0); // R2
  topleft = analogRead(A3) * (5.2 / 1023.0); // R3
  downright = analogRead(A1) * (5.2 / 1023.0); // R4.

  if( topleft > cutoff && topright > cutoff ){ // tell pitch motor to pitch down

    if( pos_pitch > 75 ) {

      // change position by 1 degree
      pos_pitch = pos_pitch - 1;
      pitch.write(pos_pitch); 

    } else { // motor is maxed out

      // display one blink on the led
      digitalWrite(ledPin, HIGH);
      delay(10000);
      digitalWrite(ledPin, LOW);
      // delay(10000);

    }

  } else if( downleft > cutoff && downright > cutoff ){ // tell pitch motor to pitch up

    if( pos_pitch < 175 ) {

      // change position by 1 degree
      pos_pitch = pos_pitch + 1;
      pitch.write(pos_pitch); 

    } else { // motor is maxed out

      // display one blink on the led
      digitalWrite(ledPin, HIGH);
      delay(10000);
      digitalWrite(ledPin, LOW);
      // delay(10000);

    }

  } else if( topleft > cutoff && downleft > cutoff ){ // tell yaw motor to turn left

    if( pos_yaw < 175 ) {

      // change position by 1 degree
      pos_yaw = pos_yaw + 1;
      pitch.write(pos_yaw); 

    } else { // motor is maxed out

      // display one blink on the led
      digitalWrite(ledPin, HIGH);
      delay(10000);
      digitalWrite(ledPin, LOW);
      // delay(10000);

    }  
    
  } else if( topright > cutoff && downright > cutoff ){ // tell yaw motor to turn right

    if( pos_yaw > 75 ) {

      // change position by 1 degree
      pos_yaw = pos_yaw - 1;
      pitch.write(pos_yaw); 

    } else { // motor is maxed out

      // display one blink on the led
      digitalWrite(ledPin, HIGH);
      delay(10000);
      digitalWrite(ledPin, LOW);
      // delay(10000);

    }
    
  } else {

    // pause
    delay(10000);

  }

    // display one blink on the led
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);

}



