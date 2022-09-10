//THIS IS FOR MESSURE THE AMP AND VOLATAGE 

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


WiFiClient wificlient;

const char* ssid = "DEB";
const char* pw = "deb123456";

int VOLT = A0; // analog pin


void setup() {
  // put your setup code here, to run once:
  WiFi.begin(ssid, pw);
  Serial.begin(9600);
  delay(1000);
  Serial.println("the esp is rebooting");
  delay(1000);

  while (WiFi.status() != WL_CONNECTED ){
      Serial.print("_-_-");
      delay(500);  
    };
   delay(1000);
   Serial.println(WiFi.localIP());
   

   
}


void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("comming to loop");
  if(WiFi.status() == WL_CONNECTED ){
      Serial.println("under if");
      WiFiClient client;
      HTTPClient http;
      http.begin(client ,"http://192.168.0.149:1800");
      http.addHeader("Content-Type", "application/json");

      int voltage = analogRead(VOLT);
      double finalvolt = ((voltage * 3.094) / 1024.0) / (7510.0/(37400.0));
      String postData = "{ \" data\" : \"name subham\", \"volt\" :\" " + String(finalvolt, 4)  + " \"}";
      int httpResponse = http.POST(postData); //sending the data via post request

      String payload = http.getString();
      Serial.println(payload);
    }
    //ending the status if

    delay(5000);
}
