#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define RADIO_CE_PIN 7
#define RADIO_CSN_PIN 8

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

struct Data_Package {
  byte moveStatus;
  byte buttonStatus;
  bool switchStatus;
};

RF24 Receiver(RADIO_CE_PIN, RADIO_CSN_PIN);

Data_Package data;

const byte address[6] = "sobad";

void setup() {
  Serial.begin(9600);

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

  pinMode(DIR_UP_DOWN_PIN, OUTPUT);
  pinMode(CONTROL_SPEED_UP_DOWN_PIN, OUTPUT);

  pinMode(RELAY_PIN, OUTPUT);

  pinMode(IR_PIN, INPUT);

  joystickControl(0);
  buttonControl(0);
  switchControl(0);
}

void loop() {
  if (Receiver.available()) {
    Receiver.read(&data, sizeof(Data_Package));
  }

  Serial.println("move:" + data.moveStatus);
  Serial.println("button:" + data.buttonStatus);
  Serial.println("switch:" + data.switchStatus);

  joystickControl(data.moveStatus);
  buttonControl(data.buttonStatus);
  switchControl(data.switchStatus);
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

void switchControl(bool value) {
  if (value == 1) {
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    digitalWrite(RELAY_PIN, LOW);
  }
}
