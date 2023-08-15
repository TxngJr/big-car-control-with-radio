#include <SPI.h>
#include <nRF24L01p.h>
nRF24L01p receiver(7, 8);  //CSN,CE


String message;
void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    digitalWrite(13, HIGH);
    receiver.txPL("1");   // ค่าที่ต้องการส่ง
    receiver.send(FAST);  // สั่งให้ส่งออกไป
    Serial.println("ส่ง");

  } else {
    receiver.txPL("2");   // ค่าที่ต้องการส่ง
    receiver.send(FAST);  // สั่งให้ส่งออกไป
    digitalWrite(13, LOW);
    Serial.println("ไม่ส่ง");
  }
}

#define FRONT_LEFT_FORWARD_PIN 26
#define FRONT_LEFT_BACKWARD_PIN 27
#define FRONT_LEFT_STOP_PIN 28

#define FRONT_RIGHT_FORWARD_PIN 17
#define FRONT_RIGHT_BACKWARD_PIN 18
#define FRONT_RIGHT_STOP_PIN 16

#define BACK_LEFT_FORWARD_PIN 2
#define BACK_LEFT_BACKWARD_PIN 1
#define BACK_LEFT_STOP_PIN 0

#define BACK_RIGHT_FORWARD_PIN 10
#define BACK_RIGHT_BACKWARD_PIN 9
#define BACK_RIGHT_STOP_PIN 11

#define DIR_UP_DOWN_PIN 3
#define CONTROL_SPEED_UP_DOWN_PIN 6

#define RELAY_PIN 7

#define IR_PIN 22

void setup() {
  delay(150);
  Serial.begin(9600);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  receiver.channel(90);         // ตั้งช่องความถี่ให้ตรงกัน
  receiver.TXaddress("gaynn");  // ตั้งชื่อตำแหน่งให้ตรงกัน ชื่อตั้งได้สูงสุด 5 ตัวอักษร
  receiver.init();

  pinMode(FRONT_LEFT_FORWARD_PIN, OUTPUT);
  pinMode(FRONT_LEFT_BACKWARD_PIN, OUTPUT);
  pinMode(FRONT_LEFT_STOP_PIN, OUTPUT);

  pinMode(FRONT_RIGHT_FORWARD_PIN, OUTPUT);
  pinMode(FRONT_RIGHT_BACKWARD_PIN, OUTPUT);
  pinMode(FRONT_RIGHT_STOP_PIN, OUTPUT);

  pinMode(BACK_LEFT_FORWARD_PIN, OUTPUT);
  pinMode(BACK_LEFT_BACKWARD_PIN, OUTPUT);
  pinMode(BACK_LEFT_STOP_PIN, OUTPUT);

  pinMode(BACK_RIGHT_FORWARD_PIN, OUTPUT);
  pinMode(BACK_RIGHT_BACKWARD_PIN, OUTPUT);
  pinMode(BACK_RIGHT_STOP_PIN, OUTPUT);

  pinMode(DIR_UP_DOWN_PIN, OUTPUT);
  pinMode(CONTROL_SPEED_UP_DOWN_PIN, OUTPUT);

  pinMode(RELAY_PIN, OUTPUT);

  pinMode(IR_PIN, INPUT);

  joystickControl(0);
  buttonControl(0);
  switchControl(0);
}
String receivedData;
void loop() {
  if (receiver.available()) {
    receiver.read();              // สั่งให้เริ่มอ่าน
    receiver.rxPL(receivedData);  // สั่งใหอ่านเก็บไว้ที่ตัวแปร
    Serial.println(receivedData);
    // String callbackData = receivedData + "&";
    // Receiver.write(callbackData.c_str());
    // Serial.println("Received: " + receivedData);
    String moveStatus = receivedData.substring(0, 1);
    String buttonStatus = receivedData.substring(1, 2);
    String switchStatus = receivedData.substring(2, 3);

    joystickControl(moveStatus.toInt());
    buttonControl(buttonStatus.toInt());
    switchControl(switchStatus.toInt());

    // Serial.println("move:" + moveStatus);
    // Serial.println("button:" + buttonStatus);
    // Serial.println("switch:" + switchStatus);
    // else {
    //   joystickControl(0);
    //   buttonControl(0);
    //   switchControl(0);
    // }
  }
}

void joystickControl(int value) {
  if (value == 1) {
    //forwardLeft
    digitalWrite(FRONT_LEFT_FORWARD_PIN, HIGH);
    digitalWrite(FRONT_LEFT_BACKWARD_PIN, HIGH);
    digitalWrite(FRONT_LEFT_STOP_PIN, LOW);

    digitalWrite(FRONT_RIGHT_FORWARD_PIN, LOW);
    digitalWrite(FRONT_RIGHT_BACKWARD_PIN, HIGH);
    digitalWrite(FRONT_RIGHT_STOP_PIN, HIGH);

    digitalWrite(BACK_LEFT_FORWARD_PIN, LOW);
    digitalWrite(BACK_LEFT_BACKWARD_PIN, HIGH);
    digitalWrite(BACK_LEFT_STOP_PIN, HIGH);

    digitalWrite(BACK_RIGHT_FORWARD_PIN, HIGH);
    digitalWrite(BACK_RIGHT_BACKWARD_PIN, HIGH);
    digitalWrite(BACK_RIGHT_STOP_PIN, LOW);
  } else if (value == 2) {
    //forwardRight
    digitalWrite(FRONT_LEFT_FORWARD_PIN, LOW);
    digitalWrite(FRONT_LEFT_BACKWARD_PIN, HIGH);
    digitalWrite(FRONT_LEFT_STOP_PIN, HIGH);

    digitalWrite(FRONT_RIGHT_FORWARD_PIN, HIGH);
    digitalWrite(FRONT_RIGHT_BACKWARD_PIN, HIGH);
    digitalWrite(FRONT_RIGHT_STOP_PIN, LOW);

    digitalWrite(BACK_LEFT_FORWARD_PIN, HIGH);
    digitalWrite(BACK_LEFT_BACKWARD_PIN, HIGH);
    digitalWrite(BACK_LEFT_STOP_PIN, LOW);

    digitalWrite(BACK_RIGHT_FORWARD_PIN, LOW);
    digitalWrite(BACK_RIGHT_BACKWARD_PIN, HIGH);
    digitalWrite(BACK_RIGHT_STOP_PIN, HIGH);
  } else if (value == 3) {
    //backwardLeft
    digitalWrite(FRONT_LEFT_FORWARD_PIN, HIGH);
    digitalWrite(FRONT_LEFT_BACKWARD_PIN, LOW);
    digitalWrite(FRONT_LEFT_STOP_PIN, HIGH);

    digitalWrite(FRONT_RIGHT_FORWARD_PIN, HIGH);
    digitalWrite(FRONT_RIGHT_BACKWARD_PIN, HIGH);
    digitalWrite(FRONT_RIGHT_STOP_PIN, LOW);

    digitalWrite(BACK_LEFT_FORWARD_PIN, HIGH);
    digitalWrite(BACK_LEFT_BACKWARD_PIN, HIGH);
    digitalWrite(BACK_LEFT_STOP_PIN, LOW);

    digitalWrite(BACK_RIGHT_FORWARD_PIN, HIGH);
    digitalWrite(BACK_RIGHT_BACKWARD_PIN, LOW);
    digitalWrite(BACK_RIGHT_STOP_PIN, HIGH);
  } else if (value == 4) {
    //backwardRight
    digitalWrite(FRONT_LEFT_FORWARD_PIN, HIGH);
    digitalWrite(FRONT_LEFT_BACKWARD_PIN, HIGH);
    digitalWrite(FRONT_LEFT_STOP_PIN, LOW);

    digitalWrite(FRONT_RIGHT_FORWARD_PIN, HIGH);
    digitalWrite(FRONT_RIGHT_BACKWARD_PIN, LOW);
    digitalWrite(FRONT_RIGHT_STOP_PIN, HIGH);

    digitalWrite(BACK_LEFT_FORWARD_PIN, HIGH);
    digitalWrite(BACK_LEFT_BACKWARD_PIN, LOW);
    digitalWrite(BACK_LEFT_STOP_PIN, HIGH);

    digitalWrite(BACK_RIGHT_FORWARD_PIN, HIGH);
    digitalWrite(BACK_RIGHT_BACKWARD_PIN, HIGH);
    digitalWrite(BACK_RIGHT_STOP_PIN, LOW);
  } else if (value == 5) {
    //forward
    digitalWrite(FRONT_LEFT_FORWARD_PIN, LOW);
    digitalWrite(FRONT_LEFT_BACKWARD_PIN, HIGH);
    digitalWrite(FRONT_LEFT_STOP_PIN, HIGH);

    digitalWrite(FRONT_RIGHT_FORWARD_PIN, LOW);
    digitalWrite(FRONT_RIGHT_BACKWARD_PIN, HIGH);
    digitalWrite(FRONT_RIGHT_STOP_PIN, HIGH);

    digitalWrite(BACK_LEFT_FORWARD_PIN, LOW);
    digitalWrite(BACK_LEFT_BACKWARD_PIN, HIGH);
    digitalWrite(BACK_LEFT_STOP_PIN, HIGH);

    digitalWrite(BACK_RIGHT_FORWARD_PIN, LOW);
    digitalWrite(BACK_RIGHT_BACKWARD_PIN, HIGH);
    digitalWrite(BACK_RIGHT_STOP_PIN, HIGH);
  } else if (value == 6) {
    //backward
    digitalWrite(FRONT_LEFT_FORWARD_PIN, HIGH);
    digitalWrite(FRONT_LEFT_BACKWARD_PIN, LOW);
    digitalWrite(FRONT_LEFT_STOP_PIN, HIGH);

    digitalWrite(FRONT_RIGHT_FORWARD_PIN, HIGH);
    digitalWrite(FRONT_RIGHT_BACKWARD_PIN, LOW);
    digitalWrite(FRONT_RIGHT_STOP_PIN, HIGH);

    digitalWrite(BACK_LEFT_FORWARD_PIN, HIGH);
    digitalWrite(BACK_LEFT_BACKWARD_PIN, LOW);
    digitalWrite(BACK_LEFT_STOP_PIN, HIGH);

    digitalWrite(BACK_RIGHT_FORWARD_PIN, HIGH);
    digitalWrite(BACK_RIGHT_BACKWARD_PIN, LOW);
    digitalWrite(BACK_RIGHT_STOP_PIN, HIGH);
  } else if (value == 7) {
    //left
    digitalWrite(FRONT_LEFT_FORWARD_PIN, HIGH);
    digitalWrite(FRONT_LEFT_BACKWARD_PIN, LOW);
    digitalWrite(FRONT_LEFT_STOP_PIN, HIGH);

    digitalWrite(FRONT_RIGHT_FORWARD_PIN, LOW);
    digitalWrite(FRONT_RIGHT_BACKWARD_PIN, HIGH);
    digitalWrite(FRONT_RIGHT_STOP_PIN, HIGH);

    digitalWrite(BACK_LEFT_FORWARD_PIN, LOW);
    digitalWrite(BACK_LEFT_BACKWARD_PIN, HIGH);
    digitalWrite(BACK_LEFT_STOP_PIN, HIGH);

    digitalWrite(BACK_RIGHT_FORWARD_PIN, HIGH);
    digitalWrite(BACK_RIGHT_BACKWARD_PIN, LOW);
    digitalWrite(BACK_RIGHT_STOP_PIN, HIGH);
  } else if (value == 8) {
    //right
    digitalWrite(FRONT_LEFT_FORWARD_PIN, LOW);
    digitalWrite(FRONT_LEFT_BACKWARD_PIN, HIGH);
    digitalWrite(FRONT_LEFT_STOP_PIN, HIGH);

    digitalWrite(FRONT_RIGHT_FORWARD_PIN, HIGH);
    digitalWrite(FRONT_RIGHT_BACKWARD_PIN, LOW);
    digitalWrite(FRONT_RIGHT_STOP_PIN, HIGH);

    digitalWrite(BACK_LEFT_FORWARD_PIN, HIGH);
    digitalWrite(BACK_LEFT_BACKWARD_PIN, LOW);
    digitalWrite(BACK_LEFT_STOP_PIN, HIGH);

    digitalWrite(BACK_RIGHT_FORWARD_PIN, LOW);
    digitalWrite(BACK_RIGHT_BACKWARD_PIN, HIGH);
    digitalWrite(BACK_RIGHT_STOP_PIN, HIGH);
  } else {
    //stop
    digitalWrite(FRONT_LEFT_FORWARD_PIN, HIGH);
    digitalWrite(FRONT_LEFT_BACKWARD_PIN, HIGH);
    digitalWrite(FRONT_LEFT_STOP_PIN, LOW);

    digitalWrite(FRONT_RIGHT_FORWARD_PIN, HIGH);
    digitalWrite(FRONT_RIGHT_BACKWARD_PIN, HIGH);
    digitalWrite(FRONT_RIGHT_STOP_PIN, LOW);

    digitalWrite(BACK_LEFT_FORWARD_PIN, HIGH);
    digitalWrite(BACK_LEFT_BACKWARD_PIN, HIGH);
    digitalWrite(BACK_LEFT_STOP_PIN, LOW);

    digitalWrite(BACK_RIGHT_FORWARD_PIN, HIGH);
    digitalWrite(BACK_RIGHT_BACKWARD_PIN, HIGH);
    digitalWrite(BACK_RIGHT_STOP_PIN, LOW);
  }
}

void buttonControl(int value) {
  if (value == 1) {
    //UP RAIL
    digitalWrite(DIR_UP_DOWN_PIN, LOW);
    digitalWrite(CONTROL_SPEED_UP_DOWN_PIN, HIGH);
  } else if (value == 2) {
    //DOWN RAIL
    if (!digitalRead(IR_PIN)) {
      digitalWrite(DIR_UP_DOWN_PIN, HIGH);
      digitalWrite(CONTROL_SPEED_UP_DOWN_PIN, HIGH);
    } else {
      digitalWrite(CONTROL_SPEED_UP_DOWN_PIN, LOW);
    }
  } else if (value == 3) {
    //rotate left
    digitalWrite(FRONT_LEFT_FORWARD_PIN, HIGH);
    digitalWrite(FRONT_LEFT_BACKWARD_PIN, LOW);
    digitalWrite(FRONT_LEFT_STOP_PIN, HIGH);

    digitalWrite(FRONT_RIGHT_FORWARD_PIN, LOW);
    digitalWrite(FRONT_RIGHT_BACKWARD_PIN, HIGH);
    digitalWrite(FRONT_RIGHT_STOP_PIN, HIGH);

    digitalWrite(BACK_LEFT_FORWARD_PIN, HIGH);
    digitalWrite(BACK_LEFT_BACKWARD_PIN, LOW);
    digitalWrite(BACK_LEFT_STOP_PIN, HIGH);

    digitalWrite(BACK_RIGHT_FORWARD_PIN, LOW);
    digitalWrite(BACK_RIGHT_BACKWARD_PIN, HIGH);
    digitalWrite(BACK_RIGHT_STOP_PIN, HIGH);
  } else if (value == 4) {
    //rotate right
    digitalWrite(FRONT_LEFT_FORWARD_PIN, LOW);
    digitalWrite(FRONT_LEFT_BACKWARD_PIN, HIGH);
    digitalWrite(FRONT_LEFT_STOP_PIN, HIGH);

    digitalWrite(FRONT_RIGHT_FORWARD_PIN, HIGH);
    digitalWrite(FRONT_RIGHT_BACKWARD_PIN, LOW);
    digitalWrite(FRONT_RIGHT_STOP_PIN, HIGH);

    digitalWrite(BACK_LEFT_FORWARD_PIN, LOW);
    digitalWrite(BACK_LEFT_BACKWARD_PIN, HIGH);
    digitalWrite(BACK_LEFT_STOP_PIN, HIGH);

    digitalWrite(BACK_RIGHT_FORWARD_PIN, HIGH);
    digitalWrite(BACK_RIGHT_BACKWARD_PIN, LOW);
    digitalWrite(BACK_RIGHT_STOP_PIN, HIGH);
  } else {
    digitalWrite(CONTROL_SPEED_UP_DOWN_PIN, LOW);
  }
}

void switchControl(int value) {
  if (value == 1) {
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    digitalWrite(RELAY_PIN, LOW);
  }
}
