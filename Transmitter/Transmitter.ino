//Transmitter
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define JOYSTICK_X_AXIS_PIN A1
#define JOYSTICK_Y_AXIS_PIN A0

#define BUTTON_UP_PIN 5
#define BUTTON_DOWN_PIN 9
#define BUTTON_LEFT_PIN 4
#define BUTTON_RIGHT_PIN 3

#define SWITCH_PIN 6

RF24 Transmitter(8, 7);  // CE, CSN

const byte address[6] = "sogod";

struct Data_Package {
  byte joystickControlStatus = 0;
  byte buttonsControlStatus = 0;
  byte switchControlStatus = 0;
};

Data_Package data;

void setup() {
  Serial.begin(9600);
  Transmitter.begin();
  Transmitter.openWritingPipe(address);
  Transmitter.setPALevel(RF24_PA_MIN);
  Transmitter.stopListening();
}

void loop() {
  data.joystickControlStatus = moveControl();
  data.buttonsControlStatus = buttonUDLR();
  data.switchControlStatus = digitalRead(SWITCH_PIN);
  // Serial.println(data.joystickControlStatus);
  // Serial.println(data.buttonsControlStatus);
  // Serial.println(data.switchControlStatus);
  Transmitter.write(&data, sizeof(Data_Package));
}


byte moveControl() {
  byte status = 0;
  int joyStickX = analogRead(JOYSTICK_X_AXIS_PIN);
  int joyStickY = analogRead(JOYSTICK_Y_AXIS_PIN);
  if (joyStickX < 200 && joyStickY > 823) {
    //forwardLeft
    status = 1;
  } else if (joyStickX < 200 && joyStickY < 200) {
    //forwardRight
    status = 2;
  } else if (joyStickX > 823 && joyStickY > 823) {
    //backwardLeft
    status = 3;
  } else if (joyStickX > 823 && joyStickY < 200) {
    //backwardRight
    status = 4;
  } else if (joyStickX < 200) {
    //forward
    status = 5;
  } else if (joyStickX > 823) {
    //backward
    status = 6;
  } else if (joyStickY > 823) {
    //left
    status = 7;
  } else if (joyStickY < 200) {
    //right
    status = 8;
  }
  return status;
}

byte buttonUDLR() {
  byte status = 0;
  if (!digitalRead(BUTTON_UP_PIN)) {
    status = 1;
  } else if (!digitalRead(BUTTON_DOWN_PIN)) {
    status = 2;
  } else if (!digitalRead(BUTTON_LEFT_PIN)) {
    status = 3;
  } else if (!digitalRead(BUTTON_RIGHT_PIN)) {
    status = 4;
  }
  return status;
}