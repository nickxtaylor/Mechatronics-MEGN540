#include <Servo.h>

// servo motor structure
Servo yaw;
Servo pitch;

// variable initiation 
const int ledPin = 13;
float pos_yaw = 90;
float pos_pitch = 100;
float boundary_pitch[2] = {80, 174};
float boundary_yaw[2] = {6, 174};
float cutoff;
float vin = 5.2;
int step = 2;

void setup() {

  // attach motors to associated arduino pins
  pitch.attach(9); // pinMode(9, OUTPUT);
  yaw.attach(10); // pinMode(10, OUTPUT);
  pitch.write(pos_pitch);
  yaw.write(pos_yaw);

  // setup led pin as output // 
  pinMode(ledPin, OUTPUT);

  // initialize parameters
  Serial.begin(9600);

  // *******************************************************************************************************

  // get signal from photoresistors from ambient environment
  float voltage_bl = analogRead(A0) * (vin / 1023.0); 
  float voltage_br = analogRead(A1) * (vin / 1023.0); 
  float voltage_tr = analogRead(A2) * (vin / 1023.0); 
  float voltage_tl = analogRead(A3) * (vin / 1023.0);
  float max = max(max(voltage_bl, voltage_br), max(voltage_tr, voltage_tl));
  float min = min(min(voltage_bl, voltage_br), min(voltage_tr, voltage_tl));
  float diff = max - min;

  // assign cutoff
  if( diff < 0.35 ) {

    // float marigin = (vin - max) * 0.25;
    // cutoff = max + marigin;
    cutoff = (max + 0.5) + ((vin - 1.3 * max) * 0.333);

  } else {

    cutoff = (voltage_bl + voltage_br + voltage_tr + voltage_tl) * 0.25; //  + (vin - max) * 0.5

  }

  // *********************************************************************************************
  // print voltage drop accross photoresistors
  Serial.print("Voltage for top left: "); // Print label
  Serial.println(voltage_tl); // Print voltage value

  // **
  Serial.print("Voltage for top right: "); // Print label
  Serial.println(voltage_tr); // Print voltage value

  // **
  Serial.print("Voltage for bottom right: "); // Print label
  Serial.println(voltage_br); // Print voltage value

  // ** 
  Serial.print("Voltage for bottom left: "); // Print label
  Serial.println(voltage_bl); // Print voltage value

  // **
  Serial.print("Variable Cutoff Value: "); // Print label
  Serial.println(cutoff); // Print voltage value

  // display one blink on the led
  digitalWrite(ledPin, HIGH);
  delay(2500);
  digitalWrite(ledPin, LOW);
  delay(200);

}

void loop() { // **********************************************************************************************************************************************

  // get signal from photoresistors
  float voltage_bl = analogRead(A0) * (vin / 1023.0); 
  float voltage_br = analogRead(A1) * (vin / 1023.0); 
  float voltage_tr = analogRead(A2) * (vin / 1023.0); 
  float voltage_tl = analogRead(A3) * (vin / 1023.0); 

  // Read the voltage input from the Arduino Nano VIN pin
  // int vin_value = analogRead(A7); // A7 corresponds to the pin connected to the VIN pin
  // float vin_voltage = vin_value * (6.0 / 1023.0); 

  // ********************************************************************************************************************************************************

  // print voltage drop accross photoresistors
  Serial.print("Voltage for top left: "); // Print label
  Serial.println(voltage_tl); // Print voltage value

  // **
  Serial.print("Voltage for top right: "); // Print label
  Serial.println(voltage_tr); // Print voltage value

  // **
  Serial.print("Voltage for bottom right: "); // Print label
  Serial.println(voltage_br); // Print voltage value

  // ** 
  Serial.print("Voltage for bottom left: "); // Print label
  Serial.println(voltage_bl); // Print voltage value

  // **
  Serial.print("Variable Cutoff Value: "); // Print label
  Serial.println(cutoff); // Print voltage value

  // ********************************************************************************************************************************************************

  // PWM signal generating algorithm (4 cases) 
  if( voltage_tl > cutoff && voltage_bl > cutoff ){ // yaw to the right ********************************************************* yaw to the right
    
    // case 1
    Serial.println("top left and bottom left are in the dark");
    if( pos_yaw < 174 && pos_yaw > 6 ) {

      // change position by step degree
      pos_yaw = pos_yaw - step;
      Serial.println(pos_yaw);
      yaw.write(pos_yaw);

    } else { // motor is maxed out

      // 
      Serial.println("yaw motor is at maximum boundary");
      pos_yaw = 10;
      Serial.println(pos_yaw);

      // display one blink on the led
      digitalWrite(ledPin, HIGH);
      delay(2000);
      digitalWrite(ledPin, LOW);
      delay(2000);

    }  
  } else if( voltage_tr > cutoff && voltage_br > cutoff ){ // yaw to the left ************************************************************* yaw to the left
    
    // case 2
    Serial.println("top right and bottom right are in the dark");
    if( pos_yaw < 6 && pos_yaw > 174 ) {

      // change position by step degree
      pos_yaw = pos_yaw + step;
      Serial.println(pos_yaw);
      yaw.write(pos_yaw);

    } else { // motor is maxed out

      // serial monitor print
      Serial.println("yaw motor is at minimized boundary");
      pos_yaw = 170;

      // display one long blink on the led
      digitalWrite(ledPin, HIGH);
      delay(2000);
      digitalWrite(ledPin, LOW);
      delay(2000);

    }
  } else if( voltage_tl > cutoff && voltage_tr > cutoff ){ // pitch down *************************************************************************** pitch down

    // case 3
    Serial.println("top left and top right are in the dark");
    if( pos_pitch > 80 && pos_pitch < 175 ) {

      // change position by step degree
      pos_pitch = pos_pitch + step;
      Serial.println(pos_pitch);
      pitch.write(pos_pitch);

    } else { // motor is maxed out
      
      // serial monitor print
      Serial.println("pitch motor is at minimum boundary");
      pos_pitch = 170;

      // display one blink on the led
      digitalWrite(ledPin, HIGH);
      delay(2000);
      digitalWrite(ledPin, LOW);
      delay(2000);

    }
  } else if( voltage_bl > cutoff && voltage_br > cutoff ){ // pitch up **************************************************************************** pitch up
    
    // case 4
    Serial.println("bottom left and bottom right are in the dark");
    if( pos_pitch > 80 && pos_pitch < 175 ) {

      // change position by step degree
      pos_pitch = pos_pitch - step;
      Serial.println(pos_pitch);
      pitch.write(pos_pitch);

    } else { // motor is maxed out

      //
      Serial.println("pitch motor is at maximum boundary");
      pos_pitch = 90;
      
      // display one blink on the led
      digitalWrite(ledPin, HIGH);
      delay(2000);
      digitalWrite(ledPin, LOW);
      delay(2000);

    }
  } 

  // loop delay 
  delay(3000);

}

// Serial.print("Voltage for top left: "); // Print label
// Serial.print(voltage_tl); // Print voltage value
// Serial.println(" V"); // Print units and move to the next lin

// Serial.print("Voltage for top right: "); // Print label
// Serial.print(voltage_tr); // Print voltage value
// Serial.println(" V"); // Print units and move to the next lin

// Serial.print("Voltage for bottom right: "); // Print label
// Serial.print(voltage_br); // Print voltage value
// Serial.println(" V"); // Print units and move to the next lin

// Serial.print("Voltage for bottom left: "); // Print label
// Serial.print(voltage_bl); // Print voltage value
// Serial.println(" V"); // Print units and move to the next line
