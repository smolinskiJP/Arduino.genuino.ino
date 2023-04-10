#include <WiFi.h>    
#include <HTTPClient.h>
#include <UrlEncode.h>
#include <SoftwareSerial.h>

const char* ssid = "IoT";
const char* password = "coltec2022";

String phoneNumber = "553198878607";
String apiKey = "6017051";

SoftwareSerial loraSerial(22, 23); // TX, RX

void sendMessage(String tempC, String humi, String tempF){

  // Data to send with HTTP POST
  //String url = "https://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);    
  String url = "https://script.google.com/macros/s/AKfycbxCofRAYm2pXUjpQaSAEDoUZKAP-wlDVxNzNh0GLp9h7evkjHqaNGyiYq_bivg4j2z_0Q/exec?UniqueID=ColtecIoT&temperatureC=" + tempC + "&humidity=" + humi + "&temperatureF=" + tempF;
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
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  loraSerial.begin(9600);
}

void loop() {
  String tempC, humi, tempF;
  if(loraSerial.available()>1){
    tempC = loraSerial.readString();
    Serial.println(tempC);
    humi = loraSerial.readString();
    Serial.println(humi);
    tempF = loraSerial.readString();
    Serial.println(tempF);
  }
  delay(5000);
  sendMessage(tempC, humi, tempF);
}
