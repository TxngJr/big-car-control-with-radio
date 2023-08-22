//Receiver
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define FRONT_LEFT_FORWARD_PIN 9
#define FRONT_LEFT_BACKWARD_PIN 10
#define FRONT_LEFT_STOP_PIN 11

#define FRONT_RIGHT_FORWARD_PIN 33
#define FRONT_RIGHT_BACKWARD_PIN 31
#define FRONT_RIGHT_STOP_PIN 35

#define BACK_LEFT_FORWARD_PIN 40
#define BACK_LEFT_BACKWARD_PIN 42
#define BACK_LEFT_STOP_PIN 44

#define BACK_RIGHT_FORWARD_PIN 39
#define BACK_RIGHT_BACKWARD_PIN 37
#define BACK_RIGHT_STOP_PIN 41

#define RELAY_1_PIN 49
#define RELAY_2_PIN 43
#define RELAY_3_PIN 45

#define IR_PIN 13

RF24 Receiver(8, 7);  // CE, CSN

const byte address[6] = "sogod";

struct Data_Package {
  byte joystickControlStatus = 0;
  byte buttonsControlStatus = 0;
  byte switchControlStatus = 0;
};

Data_Package data;

void setup() {
  Receiver.begin();
  Receiver.openReadingPipe(0, address);
  Receiver.setPALevel(RF24_PA_MIN);
  Receiver.startListening();

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

  pinMode(RELAY_1_PIN, OUTPUT);
  pinMode(RELAY_2_PIN, OUTPUT);
  pinMode(RELAY_3_PIN, OUTPUT);

  pinMode(IR_PIN, INPUT);

  joystickControl(0);
  buttonControl(0);
  switchControl(0);
}

void loop() {
  if (Receiver.available()) {
    Receiver.read(&data, sizeof(Data_Package));
    // Serial.println(data.joystickControlStatus);
    // Serial.println(data.buttonsControlStatus);
    // Serial.println(data.switchControlStatus);
  }
  joystickControl(data.joystickControlStatus);
  buttonControl(data.buttonsControlStatus);
  switchControl(data.switchControlStatus);
}

void joystickControl(byte value) {
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
  } else if (value == 9) {
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
  } else if (value == 10) {
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

void buttonControl(byte value) {
  if (value == 1) {
    //UP RAIL
    digitalWrite(RELAY_2_PIN, HIGH);
    digitalWrite(RELAY_3_PIN, LOW);
  } else if (value == 2) {
    //DOWN RAIL
    if (!digitalRead(IR_PIN)) {
      digitalWrite(RELAY_2_PIN, LOW);
      digitalWrite(RELAY_3_PIN, HIGH);
    } else {
      digitalWrite(RELAY_2_PIN, LOW);
      digitalWrite(RELAY_3_PIN, LOW);
    }
  } else if (value == 3) {
    //rotate left
    joystickControl(9);
  } else if (value == 4) {
    //rotate right
    joystickControl(10);
  } else {
    digitalWrite(RELAY_2_PIN, LOW);
    digitalWrite(RELAY_3_PIN, LOW);
  }
}

void switchControl(byte value) {
  if (value == 1) {
    digitalWrite(RELAY_1_PIN, HIGH);
  } else {
    digitalWrite(RELAY_1_PIN, LOW);
  }
}