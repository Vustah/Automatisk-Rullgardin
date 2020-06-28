#include <Wire.h>
#include <SparkFun_VCNL4040_Arduino_Library.h>
#include <SparkFun_TB6612.h>
#include <SoftwareSerial.h>

//Bluetooth
SoftwareSerial BT(10, 11);
// creates a "virtual" serial port/UART
// connect BT module TX to D10
// connect BT module RX to D11
// connect BT Vcc to 5V, GND to GND

//Motor
#define AIN1 4
#define AIN2 3
#define PWMA A0

#define BIN1 7
#define BIN2 6
#define PWMB A1

#define STBY 9

const int offsetA = 1;
const int offsetB = -1;

//ProxSensor
VCNL4040 proximitySensor;
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

int ButtonA = 12;
int ButtonB = 13;

int lightSens = A2;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.println("Starting program");
  pinMode(ButtonA, INPUT);
  pinMode(ButtonB, INPUT);
  pinMode(lightSens, INPUT);
  BT.begin(9600);
  if (proximitySensor.begin() == false)
  {
    Serial.println("Device not found. Please check wiring.");
    while (1); //Freeze!
  }
}

unsigned int motorValue = 0;
void loop() {
  unsigned int proxValue = proximitySensor.getProximity();
  //Serial.println(proxValue);

  if (lightRead()>50){
    motorValue = 255;
    motor1.drive(motorValue, 1);
  }

  checkAndReturnBT();
  if (proxValue >= 1000) {
    motor1.brake();
  }
  else if (digitalRead(ButtonA)) {
    motorValue = 255;
    motor1.drive(motorValue, 1);
  }
  else if (digitalRead(ButtonB)) {
    motor2.drive(255, 1);
  }

  else {
    motor2.brake();
  }
}

int checkAndReturnBT() {
  char a;
  if (BT.available())
  {
    a = (BT.read());
    if (a == '1')
    {
      motorValue = 150 ;
      motor1.drive(motorValue, 1);
    }
    if (a == '2')
    {
      motor1.brake();
    }
  }
}

float lightRead() {
  float lightLevel = analogRead(lightSens);
  float square_ratio = lightLevel / 1023.0;
  square_ratio = pow(square_ratio, 2.0)*100;
  return square_ratio;
  Serial.println(square_ratio);
}
