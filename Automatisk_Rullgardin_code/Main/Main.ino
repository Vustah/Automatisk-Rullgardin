#include <SoftwareSerial.h>
#define RX 9
#define TX 10

#define MASTER_RX 11
#define MASTER_TX 12


#define LED_BLUE 3
#define LED_RED 5
#define LED_GREEN 6

SoftwareSerial BT(RX, TX);
SoftwareSerial MOTOR_CONTROL(MASTER_RX, MASTER_TX);

void ReadBT(String *cmd);

void setup() {

  init_LED();
  init_BT();
  init_Serial();
  init_MOTOR();

  Serial.println("Starting Program");
}
void init_BT() {
  pinMode(RX, INPUT);
  pinMode(TX, OUTPUT);
  BT.begin(9600);
}

void init_Serial() {
  Serial.begin(9600);
}

void init_MOTOR() {
  pinMode(MASTER_RX, INPUT);
  pinMode(MASTER_TX, OUTPUT);
  MOTOR_CONTROL.begin(9600);
}

void init_LED() {
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  analogWrite(LED_BLUE, 255);
  analogWrite(LED_RED, 255);
  analogWrite(LED_GREEN, 255);

}

void loop() {
  /*
    String command[2];
    ReadBT(&command[0]);
  */
  ReadSerial();

  SendCommandMotor("cw");
  analogWrite(LED_BLUE, 255);
  analogWrite(LED_RED, 250);
  analogWrite(LED_GREEN, 255);
  delay(500);
  SendCommandMotor("ccw");
  analogWrite(LED_BLUE, 255);
  analogWrite(LED_RED, 255);
  analogWrite(LED_GREEN, 250);
  delay(500);
}

void SendCommandMotor(String cmd) {
  Serial.println(cmd);
  if (cmd.equals("cw")) {
    Serial.println("cmd: cw");
    MOTOR_CONTROL.print("1\n");
  }
  else if (cmd.equals("ccw")) {
    Serial.println("cmd: ccw");
    MOTOR_CONTROL.print("2\n");
  }
}

void ReadSerial() {
  String Test;
  Serial.print(Serial.available());
  if (Serial.available()) {
    Serial.print("\nTransmit Terminal Test: ");
    Test = Serial.readStringUntil('\n');
    Serial.print(Test);
    Serial.print("\n");
    BT.write('a');
  }
}

void ReadBT(String *cmd) {
  Serial.println(BT.available());
  if (BT.available()) {
    Serial.print("\nTransmit BT Test: ");
    cmd[0] = BT.readStringUntil('\n');
    cmd[1] = BT.readStringUntil('\n');
    Serial.print(cmd[0]);
    Serial.print(" " );
    Serial.print(cmd[1]);
    Serial.print("\n");
  }
}
