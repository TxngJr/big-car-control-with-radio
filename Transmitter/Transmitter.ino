#include <SPI.h>
#include <nRF24L01p.h>

nRF24L01p transmitter(7, 8);  //CSN,CE

#define JOYSTICK_X_AXIS_PIN A1
#define JOYSTICK_Y_AXIS_PIN A0

#define BUTTON_UP_PIN 7
#define BUTTON_DOWN_PIN 9
#define BUTTON_LEFT_PIN 6
#define BUTTON_RIGHT_PIN 8

#define SWITCH_PIN 5

#define LED_ON_PIN 4


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
  delay(150);
  Serial.begin(9600);
  Transmitter.begin(9600);

  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  transmitter.channel(90);         // ตั้งช่องความถี่ให้ตรงกัน
  transmitter.TXaddress("gaynn");  // ตั้งชื่อตำแหน่งให้ตรงกัน ชื่อตั้งได้สูงสุด 5 ตัวอักษร
  transmitter.init();

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
  static int count = 0;
  String dataTransmitter = moveControl() + buttonUDLR() + digitalRead(SWITCH_PIN) + "&";
  transmitter.txPL(dataTransmitter);  // ค่าที่ต้องการส่ง
  transmitter.send(FAST);             // สั่งให้ส่งออกไป
}