#include <SoftwareSerial.h>
#define GSM_TX 7    // TX to GSM Module
#define GSM_RX 8    // RX from GSM Module

SoftwareSerial gsm(GSM_TX, GSM_RX);
#define MQ2pin A0
float sensorValue;  //variable to store sensor value
int buzzer=4;
String number1 = ""; // Replace with real phone number with countru code

void setup() {
  Serial.begin(9600); // sets the serial port to 9600
  pinMode(buzzer,OUTPUT);
   gsm.begin(9600);
  Serial.println("MQ2 warming up!");
  delay(20000); // allow the MQ2 to warm up
}

void loop() {
  sensorValue = analogRead(MQ2pin); // read analog input pin 0
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
  if(sensorValue>300)
  {
    digitalWrite(buzzer,HIGH);
    sendSMS(number1, "Gas Leakage Detected");
    Serial.println("SMS sent");
  

    }
  else
  {
      digitalWrite(buzzer,LOW);
    }

}

void sendSMS(String number, String message) {
  gsm.println("AT+CMGF=1"); // Set SMS mode to text
  delay(1000);
  gsm.println("AT+CMGS=\"" + number + "\"");
  delay(1000);
  gsm.println(message);
  delay(1000);
  gsm.write(26); // Ctrl+Z to send SMS
  delay(5000);

}
