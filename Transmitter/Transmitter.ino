#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define RADIO_CE_PIN 7
#define RADIO_CSN_PIN 8

#define JOYSTICK_X_AXIS_PIN A1
#define JOYSTICK_Y_AXIS_PIN A0

#define BUTTON_UP_PIN 7
#define BUTTON_DOWN_PIN 9
#define BUTTON_LEFT_PIN 6
#define BUTTON_RIGHT_PIN 8

#define SWITCH_PIN 5

#define LED_ON_PIN 4

struct Data_Package {
  byte moveStatus;
  byte buttonStatus;
  bool switchStatus;
};

RF24 Receiver(RADIO_CE_PIN, RADIO_CSN_PIN);

Data_Package data;

const byte address[6] = "sobad";

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

void setup() {
  Serial.begin(9600);

  Transmitter.begin();
  Transmitter.openWritingPipe(address);
  Transmitter.setPALevel(RF24_PA_MIN);
  Transmitter.stopListening();

  pinMode(JOYSTICK_X_AXIS_PIN, INPUT);
  pinMode(JOYSTICK_Y_AXIS_PIN, INPUT);

  pinMode(BUTTON_UP_PIN, INPUT);
  pinMode(BUTTON_DOWN_PIN, INPUT);
  pinMode(BUTTON_LEFT_PIN, INPUT);
  pinMode(BUTTON_RIGHT_PIN, INPUT);
  pinMode(SWITCH_PIN, INPUT);

  pinMode(LED_ON_PIN, OUTPUT);

  digitalWrite(LED_ON_PIN, HIGH);
}

void loop() {
  // static byte prvMoveStatus;
  // static byte prvButtonStatus;
  // static bool prvSwitchStatus;
  data.moveStatus = moveControl();
  data.buttonStatus = buttonUDLR();
  data.switchStatus = digitalRead(SWITCH_PIN);
  // Serial.println(text);
  // if (data.moveStatus != prvMoveStatus || data.buttonStatus != prvButtonStatus || data.switchStatus != prvSwitchStatus) {
  // Serial.println("move:" + data.moveStatus);
  // Serial.println("button:" + data.buttonStatus);
  // Serial.println("switch:" + data.switchStatus);
  Transmitter.write(&data, sizeof(Data_Package));
  //   prvMoveStatus = data.moveStatus;
  //   prvButtonStatus = data.buttonStatus;
  //   prvSwitchStatus = data.switchStatus;
  // }
}