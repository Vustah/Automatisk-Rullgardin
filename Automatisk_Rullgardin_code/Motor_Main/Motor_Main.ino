#include <Wire.h>
#include <SparkFun_TB6612.h>
#include <SoftwareSerial.h>

#define MASTER_RX 11
#define MASTER_TX 12
SoftwareSerial MOTOR_CONTROL(MASTER_RX, MASTER_TX);

#define PWMA 3
#define AIN1 6
#define AIN2 5

#define PWMB 10
#define BIN1 8
#define BIN2 9

#define STANDBY 7

const int offsetA = 1;
const int offsetB = -1;

//Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STANDBY);
//Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STANDBY);

void setup() {
  init_MOTOR();
  Serial.begin(9600);
  Serial.println("Starting Program");
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(PWMA,OUTPUT);
  pinMode(STANDBY,OUTPUT);
  digitalWrite(STANDBY,1);  
}

void init_MOTOR() {
  pinMode(MASTER_RX, INPUT);
  pinMode(MASTER_TX, OUTPUT);
  MOTOR_CONTROL.begin(9600);
}

void loop() {
/*
  if (MOTOR_CONTROL.available()) {
    readMOTOR_CONTROL();
  }
  */
  if (Serial.available()) {
    ctrlMotor();
  }
}

void ctrlMotor() {
  String cmd = Serial.readStringUntil('\n');
  Serial.print(cmd);
  Serial.print(": ");
  if (cmd.equals("1")) {
    Serial.println("cw");
    //motor1.drive(255, 1000);
    digitalWrite(AIN1, 1);
    digitalWrite(AIN2, 0);
    digitalWrite(PWMA, 225);
  }
  else if (cmd.equals("2")) {
    Serial.println("ccw");
    //motor1.drive(-255, 1000);
  }
  else{
    //motor1.brake();
  }
}

/*
void readMOTOR_CONTROL() {
  signed int motorValue = 0;
  String cmd = MOTOR_CONTROL.readStringUntil('\n');
  Serial.print("Reading Command: ");
  Serial.println(cmd);
  if (cmd.equals("1")) {
    Serial.println("cw");
    motorValue = 255;
    motor1.drive(motorValue, 1);
  }
  else if (cmd.equals("2")) {
    Serial.println("ccw");
    motorValue = -255;
    motor1.drive(motorValue, 1);
  }
}
*/
