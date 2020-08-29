// REQUIRES the following Arduino libraries:
// DHT LIBRARIES
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// DHT SETUP:
#define DHTPIN 4
#define DHTTYPE DHT22 // 11 or 21
DHT_Unified dht(DHTPIN, DHTTYPE); // Initialize DHT sensor. / DHT_Unified
uint32_t delayMS;

//ESP Software reset boolean:
bool reset = false;
// Transmission variables
String sendChars = ("");
String startChar = ("<");
String endChar = (">");
String delimeter = (",");

void setup() {
  Serial.begin(9600);

  // DHT Setup
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
}

void loop() {
delay(delayMS);
  
  sensors_event_t event;

  dht.humidity().getEvent(&event);
  float h = event.relative_humidity;
  
  if (isnan(h)) {
    return;
    }
  else { // Start Building the string to send via Serial  
    sendChars = F("");
    sendChars = (startChar + event.relative_humidity + delimeter);
    }

    dht.temperature().getEvent(&event);
  float t = event.temperature;

  if (isnan(t)) {
    return;
    } 
  else { 
    sendChars = (sendChars + event.temperature + endChar);
    // NOTE: 'println' adds a newline character '\n' 
    // that needs to be stripped on the other end
    Serial.println(sendChars); // Send Line all at once
    }
    
// Never got the ESP32 or Reset working reliably, its finicky about 
// closed/reconnections without a reset, and when it does it spits
// out something to serial that breaks my read loop in python due to encoding issues

//  while(Serial.available()){
//    receivedChars = Serial.read();
//    if (isnan(receivedChars)){
//      reset = false;
//    }
//    else {
//      reset = true;
//    }
//  }
//  if (reset == true) {
////    Serial.println(receivedChars);
////    Serial.println(F("Resetting"));
//    ESP.restart();
//  }
}
