/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 28 May 2015
  by Michael C. Miller
  modified 8 Nov 2013
  by Scott Fitzgerald

  http://arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

#define esp_pin 2
void setup() {
  Serial.begin(9600);
  myservo.attach(esp_pin); // attaches the servo on GIO2 to the servo object
  myservo.write(1000);
  delay(3000);
}

void loop() {
    
//  myservo.write(1400);
//  Serial.print()
// in steps of 1 degree
    for(int i = 1100; i< 1600; i+=10){
        myservo.write(i);
        Serial.println(i);
        delay(30);
      }
     for(int i = 1600; i> 1100; i-=10){
        myservo.write(i);
        Serial.println(i);
        delay(30);
      }

      delay(5000);
    
    // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  
  
}
