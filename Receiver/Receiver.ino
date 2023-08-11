UART Receiver(4, 5, 0, 0);

#define TOKEN "nonisgay"

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

#define DIR_UP_DOWN_PIN 22
#define CONTROL_SPEED_UP_DOWN_PIN 21

#define RELAY_PIN 8

void setup() {
  Serial.begin(9600);
  Receiver.begin(9600);

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

  joystickControl(0);
  buttonControl(0);
  switchControl(0);
}

void loop() {

  if (Receiver.available()) {
    String receivedData = Receiver.readStringUntil('&');
    // Serial.println("Received: " + receivedData);

    int token = receivedData.indexOf(TOKEN);
    if (token != -1) {
      String moveStatus = receivedData.substring(token + 1, token + 2);
      String buttonStatus = receivedData.substring(token + 2, token + 3);
      String switchStatus = receivedData.substring(token + 3, token + 4);
      joystickControl(moveStatus.toInt());
      buttonControl(buttonStatus.toInt());
      switchControl(switchStatus.toInt());
    }
    // String token = receivedData.substring(0, 4);
    // if (token == "good") {
    //   String moveStatus = receivedData.substring(4, 5);
    //   String buttonStatus = receivedData.substring(5, 6);
    //   String switchStatus = receivedData.substring(6, 7);
    //   // Serial.println("token : " + token);
    //   // Serial.println("move:" + moveStatus);
    //   // Serial.println("button:" + buttonStatus);
    //   // Serial.println("switch:" + switchStatus);
    //   joystickControl(moveStatus.toInt());
    //   buttonControl(buttonStatus.toInt());
    //   switchControl(switchStatus.toInt());
    // }
  } else {
    joystickControl(0);
    buttonControl(0);
    switchControl(0);
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
    digitalWrite(DIR_UP_DOWN_PIN, HIGH);
    digitalWrite(CONTROL_SPEED_UP_DOWN_PIN, HIGH);
  } else if (value == 2) {
    //DOWN RAIL
    digitalWrite(DIR_UP_DOWN_PIN, LOW);
    digitalWrite(CONTROL_SPEED_UP_DOWN_PIN, HIGH);
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
