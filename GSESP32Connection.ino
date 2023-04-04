#include <WiFi.h>    
#include <HTTPClient.h>
#include <UrlEncode.h>


const char* ssid = "IoT";
const char* password = "coltec2022";

String phoneNumber = "553198878607";
String apiKey = "6017051";


#include <DHT.h>

#define DHTPIN 32
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void sendMessage(String message){

  // Data to send with HTTP POST
  //String url = "https://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);    
  String url = "https://script.google.com/macros/s/AKfycbxCofRAYm2pXUjpQaSAEDoUZKAP-wlDVxNzNh0GLp9h7evkjHqaNGyiYq_bivg4j2z_0Q/exec?UniqueID=ColtecIoT&temperatureC=" + String(dht.readTemperature()) + "&humidity=" + String(dht.readHumidity()) + "&temperatureF=" + String(dht.readTemperature(true));
  HTTPClient http;
  http.begin(url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/json");
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  if (httpResponseCode == 200){
    Serial.print("Message sent successfully");
    Serial.print(url);
  }
  else{
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  //sendMessage("ols");
  dht.begin();
}

void loop() {
  sendMessage("Dr. Alex Fabiani de Brito Torres ");
  delay(10000);
  Serial.println(String(dht.readTemperature()));
  Serial.println(String(dht.readHumidity()));
  Serial.println(String(dht.readTemperature(true)));
}
