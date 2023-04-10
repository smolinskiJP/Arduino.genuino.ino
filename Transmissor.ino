#include <SoftwareSerial.h>

SoftwareSerial loraSerial(22, 23); // TX, RX

#include <DHT.h>

#define DHTPIN 32
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  loraSerial.begin(9600);

  //sendMessage("ols");
  dht.begin();
}

void loop() {
  loraSerial.print(String(dht.readTemperature()));
  loraSerial.print(String(dht.readHumidity()));
  loraSerial.print(String(dht.readTemperature(true)));
  delay(10000);
}
