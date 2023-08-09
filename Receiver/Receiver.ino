const char token = 'K';

#define Receiver Serial1

#define FRONT_LEFT_FORWARD_PIN 1
#define FRONT_LEFT_BACKWARD_PIN 2
#define FRONT_LEFT_STOP_PIN 3

#define FRONT_RIGHT_FORWARD_PIN 4
#define FRONT_RIGHT_BACKWARD_PIN 5
#define FRONT_RIGHT_STOP_PIN 6

#define BACK_LEFT_FORWARD_PIN 7
#define BACK_LEFT_BACKWARD_PIN 8
#define BACK_LEFT_STOP_PIN 9

#define BACK_RIGHT_FORWARD_PIN 10
#define BACK_RIGHT_BACKWARD_PIN 11
#define BACK_RIGHT_STOP_PIN 12


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

  moveControl(0);
}

void loop() {
  if (Receiver.available() >= 4) {
    byte dataPacket[4];
    Receiver.readBytes(dataPacket, 4);
    if (dataPacket[0] == token) {
      byte statusControl = dataPacket[1];
      byte buttonUDLR = dataPacket[2];
      bool switchPick = dataPacket[3];

      moveControl(statusControl);
      buttonControl(buttonUDLR);

      Serial.print("statusControl: ");
      Serial.println(statusControl);
      Serial.print("buttonUDLR: ");
      Serial.println(buttonUDLR);
      Serial.print("switchPick: ");
      Serial.println(switchPick);
    }
  } else {
    moveControl(0);
  }
}

void moveControl(int value) {
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
  } else if (value == 2) {
    //DOWN RAIL
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
  }
}