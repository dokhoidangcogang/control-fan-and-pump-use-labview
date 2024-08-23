#include <Wire.h>
#include <SHT21.h>  // include SHT21 library

SHT21 sht;

int temp;   // variable to store temperature
int humidity; // variable to store humidity
int fan = 8;
int pump = 10;
byte labview;

void setup() {
  Wire.begin();   // begin Wire(I2C)
  Serial.begin(9600); // begin Serial
  pinMode(fan, OUTPUT);
  pinMode(pump, OUTPUT);
}

void loop() {
  temp = sht.getTemperature();  // get temp from SHT 
  humidity = sht.getHumidity(); // get humidity from SHT

  // Send temperature and humidity to Serial for LabVIEW
  Serial.print(temp);
  Serial.print(",");
  Serial.println(humidity);

  // Check for commands from LabVIEW
  if (Serial.available() > 0) {
    labview = Serial.read();
    if (labview == '1') {
      digitalWrite(pump, HIGH);
    } else if (labview == '2') {
      digitalWrite(pump, LOW);
    } else if (labview == '3') {
      digitalWrite(fan, HIGH);
    } else if (labview == '4') {
      digitalWrite(fan, LOW);
    }
  }

  delay(1000);
}
