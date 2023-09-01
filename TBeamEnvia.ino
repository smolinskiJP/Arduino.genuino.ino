#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include <SoftwareSerial.h>

#define BME_SCK 14
#define BME_MISO 21
#define BME_MOSI 22
#define BME_CS 13

#define uS_TO_S_FACTOR 10000000
#define TIME_TO_SLEEP 10

#define SEALEVELPRESSURE_HPA (1013.25)

//Adafruit_BME680 bme; // I2C
//Adafruit_BME680 bme(BME_CS); // hardware SPI
Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);

SoftwareSerial loraSerial(32, 33);  // TX, RX

void setup() {
  Serial.begin(115200);
  loraSerial.begin(9600);
  Serial.println(F("BME680 test"));

  if (!bme.begin()) {
    loraSerial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1)
      ;
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150);  // 320*C for 150 ms




  Serial.println("ACORDEU");
}

void loop() {
  if (!bme.performReading()) {
    loraSerial.println("Failed to perform reading :(");
    return;
  }
  sendMessage();
  delay(1000);
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_deep_sleep_start();
}

void sendMessage() {
  String url = "https://script.google.com/macros/s/AKfycbxCofRAYm2pXUjpQaSAEDoUZKAP-wlDVxNzNh0GLp9h7evkjHqaNGyiYq_bivg4j2z_0Q/exec?UniqueID=ColtecIoT&temperatureC=" + (String)bme.temperature + "&humidity=" + (String)bme.humidity + "&temperatureF=" + (String)(bme.pressure / 100.0);
  loraSerial.print(url);
  Serial.print(url);
}
