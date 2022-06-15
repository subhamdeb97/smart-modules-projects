
#include <dht.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
//#include <ArduinoJson.h>

#define dht_apin 4 // D4 in esp8266
dht DHT;

WiFiClient wifiClient;

const char* ssid = "DEB";
const char* pw = "deb123456";

//String temp&humidity = "";

void setup(){
  WiFi.begin(ssid,pw);
  Serial.begin(9600);
  delay(1000);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
  
  while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(500);  
  }
  Serial.println("");
  Serial.print(WiFi.localIP());
 
}//end "setup()"
 
void loop(){
  //Start of Program 
 
    DHT.read11(dht_apin);
    
//    Serial.print("Current humidity = ");
//    Serial.print(DHT.humidity);
//    Serial.print("%  ");
//    Serial.print("temperature = ");
//    Serial.print(DHT.temperature); 
//    Serial.println("C  ");
    
    if(WiFi.status() == WL_CONNECTED){

      HTTPClient http;
      
      http.begin(wifiClient ,"http://192.168.0.143:2000/esp8266");
      
//      http.addHeader("content-Type", "text/plain");
//      http.addHeader("content-Type", "application/x-www-form-urlencoded");
        http.addHeader("Content-Type", "application/json");


      String temp_humidity = "{\"temp\":"+ String(DHT.temperature)+", \"humi\" :"+ String(DHT.humidity) +" }" ;
//            String temp_humidity = "{\" name \" : \" Subham\" }" ;
      
      int httpCode = http.POST(temp_humidity);

      String payload = http.getString();
      Serial.println("the response");
      Serial.println(payload);
      
  }
 //end wifi connect if con 
  
 delay(5000);
}// end loop(
