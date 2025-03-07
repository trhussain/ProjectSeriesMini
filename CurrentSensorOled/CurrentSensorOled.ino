
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


const int sensorIn = 26;  // pin where the OUT pin from sensor is connected on Arduino
int mVperAmp = 185;       // this the 5A version of the ACS712 -use 100 for 20A Module and 66 for 30A Module
int Watt = 0;
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;


void setup() {
  Serial.begin(9600);
  Serial.println("ACS712 current sensor");
  displaySetup();
}

void loop() {
  playBouncingEarsAnimation();
  Serial.println("");
  Voltage = getDCAmps();

  delay(100);
}


float getDCAmps() {
  int readValue = analogRead(sensorIn);        // Read ADC value
  float voltage = (readValue * 3.3) / 4096.0;  // Convert ADC to voltage (ESP32, 12-bit ADC)

  // Need to adjust processing
  float current = (voltage - 2.5) * 1000 / mVperAmp;

  Serial.print("ADC Value: ");
  Serial.println(readValue);
  Serial.print("Pin Input Voltage: ");
  Serial.println(voltage, 3);
  Serial.print("Current (A) - Might be VERY large: ");
  Serial.println(current, 3);

  return current;
}
