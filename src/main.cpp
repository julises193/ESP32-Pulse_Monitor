#include <Arduino.h>
#include <U8g2lib.h>
#include <MAX30105.h>
#include <Wire.h>

// start sensor and OLED
MAX30105 particleSensor;
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 22, /* data=*/ 21, /* reset=*/ U8X8_PIN_NONE);
int fingerGoneCounter = 0;

long lastScreenUpdate = 0;
long lastIRValue2 = 0; //from 2 samples ago
long lastIRValue = 0; //from 1 sample ago
long lastBeatTime = 0;
long delta = 0;
int bpm = 0;

void setup() {
  // Start Serial and screen
  Serial.begin(115200);
  delay(1000);
  Serial.println("Pulse Monitor Initializing...");

  u8g2.begin();

  // check if sensor is connected
  Wire.begin();
  Wire.setClock(100000);

  while (!particleSensor.begin(Wire, I2C_SPEED_STANDARD)) {
    Serial.println("Sensor not found. Retrying...");
  }

 byte ledBrightness = 20;
 byte sampleAverage = 4;
 byte ledMode = 2;
 int sampleRate = 100;
 int pulseWidth = 411;
 int adcRange = 4096;

 particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange);

 particleSensor.nextSample();

 Serial.println("Configuration complete. Place finger.");
}

void loop() {
  // read infrared value and store it in long variable
  long irValue = particleSensor.getIR(); // current IR value
  particleSensor.check();

  // IR value when finger is detected is usually > 50000
  if (irValue > 7000) { 
    fingerGoneCounter = 0; //set counter to 0

      if ((lastIRValue > irValue) && (lastIRValue > lastIRValue2)) { //peak detected!
        delta = millis() - lastBeatTime;
        
        if (delta > 400) { //make sure that BPM is a realistic value
          lastBeatTime = millis();
          bpm = 60000 / delta;
        }
      }

    Serial.print("IR Value: ");
    Serial.println(irValue);

    // screen update
    if (millis() - lastScreenUpdate > 250) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 10, "Pulse: Active");
    u8g2.setCursor(0, 30);
    u8g2.print(bpm);
    u8g2.sendBuffer();
    
    lastScreenUpdate = millis();
    }

  } else {
    fingerGoneCounter++;
    if (fingerGoneCounter > 20) {

      if (millis() - lastScreenUpdate > 250) { // prevents flooding data bus
      bpm = 0;
    
      Serial.println("No finger detected");
    
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_ncenB08_tr);
      u8g2.drawStr(0, 10, "Place Finger");
      u8g2.sendBuffer();

      lastScreenUpdate = millis();
    }
    }
  }

  delay(20); // delay to make monitor readable

  lastIRValue2 = lastIRValue;
  lastIRValue = irValue;
  }
  


