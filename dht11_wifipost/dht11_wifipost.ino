
#include <dht.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

//including lib for BMP180
#include <SFE_BMP180.h>
#include <Wire.h>
#define ALTITUDE 23.0

#define dht_apin 10 // D4 in esp8266
dht DHT;

WiFiClient wifiClient;

const char* ssid = "DEB";
const char* pw = "deb123456";

//for bmp180
SFE_BMP180 pressure;


void setup(){
  WiFi.begin(ssid,pw);
  Serial.begin(9600);
  delay(1000);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(500);  
  }
  delay(1000);
  Serial.println("");
  Serial.print(WiFi.localIP());

//  below condition for bmp180
  if (pressure.begin()){
    Serial.println("BMP180 init success");
  }
  delay(1000);
 
}
//end "setup()"
 
void loop(){
  //Start of Program 
 
    DHT.read11(dht_apin);
    
//    Serial.print("Current humidity = ");
//    Serial.print(DHT.humidity);
//    Serial.print("%  ");
//    Serial.print("temperature = ");
//    Serial.print(DHT.temperature); 
//    Serial.println("C  ");


//bmp180 part start
  char status;
  double T,P,p0,a;
  float pressureinHG = 0.00;
  float pressureinBR = 0.00;
  float bmpTemp = 0.00;

  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(status);
    status = pressure.getTemperature(T);
    if (status != 0)
    {
      Serial.print(T,2);
      Serial.print(" deg C, ");
      bmpTemp = T;
      status = pressure.startPressure(1);
      if (status != 0)
      {
        delay(status);
        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          // Print out the measurement:
          Serial.print("absolute pressure: ");
          Serial.print(P,2);
          Serial.print(" mb, ");
          Serial.print(P*0.0295333727,2);
          Serial.println(" inHg");
          pressureinHG = P*0.0295333727;
          pressureinBR = P;

          p0 = pressure.sealevel(P,ALTITUDE); // we're at 1655 meters (Boulder, CO)
          Serial.print("relative (sea-level) pressure: ");
          Serial.print(p0,2);
          Serial.print(" mb, ");
          Serial.print(p0*0.0295333727,2);
          Serial.println(" inHg");

          a = pressure.altitude(P,p0);
          Serial.print("computed altitude: ");
          Serial.print(a,0);
          Serial.print(" meters, ");
          Serial.print(a*3.28084,0);
          Serial.println(" feet");
        }
        
      }
    }
    
  }



    
    if(WiFi.status() == WL_CONNECTED){

      HTTPClient http;
      
      http.begin(wifiClient ,"http://192.168.0.232:2000/esp8266");
      
//      http.addHeader("content-Type", "text/plain");
//      http.addHeader("content-Type", "application/x-www-form-urlencoded");
        http.addHeader("Content-Type", "application/json");

      Serial.println(pressureinHG);
      String temp_humidity = "{\"temp\":"+ String(DHT.temperature)+", \"humi\" :"+ String(DHT.humidity)+ ", \"bmpPressureinHg\": "+String(pressureinHG)+", \"bmpPressureinMB\": "+String(pressureinBR) + ", \"bmpTemp\": "+String(bmpTemp)+" }" ;
//            String temp_humidity = "{\" name \" : \" Subham\" }" ;
      
      int httpCode = http.POST(temp_humidity);

      String payload = http.getString();
      Serial.println("the response");
      Serial.println(payload);
      
  }
 //end wifi connect if con 
  
 delay(15000);
}// end loop()
