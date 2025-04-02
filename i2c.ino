/*
  Arduino Slave for Raspberry Pi Master
  i2c_slave_ard.ino
  Connects to Raspberry Pi via I2C
  
  DroneBot Workshop 2019
  https://dronebotworkshop.com
*/

// Include the Wire library for I2C
#include <Wire.h>
#include <Servo.h>
// LED on pin 13
const int servoPin = 9;
int x;


Servo myservo;


void setup() {
  // Join I2C bus as slave with address 8
  Wire.begin(0x8);

  myservo.attach(servoPin);

  // Call receiveEvent when data received
  Wire.onReceive(receiveEvent);

  // Setup pin 13 as output and turn LED off
  pinMode(9, OUTPUT);

  Serial.begin(9600);
}

// Function that executes whenever data is received from master
void receiveEvent(int howMany) {
  while (Wire.available()) {  // loop through all but the last
    char c = Wire.read();     // receive byte as a character
    x = c - 48;
    x = map(x, 0, 9, 40, 140);
    Serial.print("c = ");
    Serial.println(c);
    Serial.print("x = ");
    Serial.println(x);
  }
}
void loop() {

  myservo.write(x);
}