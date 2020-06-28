#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11);
// creates a "virtual" serial port/UART
// connect BT module TX to D10
// connect BT module RX to D11
// connect BT Vcc to 5V, GND to GND
int Vsensor = A0;

void setup()
{
  pinMode(Vsensor, INPUT);
  // set digital pin to control as an output
  pinMode(13, OUTPUT);
  // set the data rate for the SoftwareSerial port
  BT.begin(9600);
  // Send test message to other device
  BT.println("Hello from Arduino");
  Serial.begin(115200);
}
char a; // stores incoming character from other device
unsigned int lastMillis = 0;
void loop()
{
  if (BT.available())
    // if text arrived in from BT serial...
  {
    a = (BT.read());
    if (a == '1')
    {
      digitalWrite(13, HIGH);
      BT.println("LED on");
    }
    if (a == '2')
    {
      digitalWrite(13, LOW);
      BT.println("LED off");
    }
    if (a == '?')
    {
      BT.println("Send '1' to turn LED on");
      BT.println("Send '2' to turn LED on");
    }

    // you can add more "if" statements with other characters to add more commands
  }
  if (detect()>1000){
    BT.println("Finger in front of sensor");
  }



}

int detect() {
  return analogRead(Vsensor);
}
