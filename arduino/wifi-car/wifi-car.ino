#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Servo.h>

  Servo myservo;

  #define SERVOMIN 40      //the angle of servo
  #define SERVOMID 60
  #define SERVOMAX 85
  #define TURNLEFT myservo.write(SERVOMIN)  //turn left
  #define TURNMID myservo.write(SERVOMID)   //turn middle
  #define TURNRIGHT myservo.write(SERVOMAX)  //turn right

    const char* ssid     = ""; // wifi name
    const char* password = ""; // wifi password

    int powPin1 = 14; // pin D5
    int powPin2 = 12; // pin D6
    int powPin3 = 13; // pin D7
    int powPin4 = 15; // pin D8
    int powPin5 = 5; // pin D1
    int powPin6 = 4; // pin D2
    
    int servoPin = 16; // pin D0

    int turnPin = A0;
    int val;
    int wifiStatus;
     
 void setup() {

      myservo.attach(servoPin);
      
      Serial.begin(115200);
     
      // We start by connecting to a WiFi network
     
      WiFi.begin(ssid, password);
      
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }

      pinMode(powPin1, OUTPUT);
      pinMode(powPin2, OUTPUT);
      pinMode(powPin3, OUTPUT);
      pinMode(powPin4, OUTPUT);
      pinMode(powPin5, OUTPUT);
      pinMode(powPin6, OUTPUT);
}
     
void loop() {

      val = analogRead(turnPin);
      Serial.println(val);

      if(val > 100 && val < 800){
        TURNMID;
      }
      else if(val >= 800){
        TURNRIGHT;
      }
      else if (val <= 100){
        TURNLEFT;
      }

       wifiStatus = WiFi.status();

      if(wifiStatus == WL_CONNECTED){

         Serial.println("");
         Serial.println("Your ESP is connected!");  
         Serial.println("Your IP address is: ");
         Serial.println(WiFi.localIP());  

          HTTPClient http;    //Declare object of class HTTPClient
 
          http.begin("YOUR_URL/direction");      //Specify request destination
          http.addHeader("Content-Type", "application/x-www-form-urlencoded");  //Specify content-type header

          int httpGet = http.GET();
          String payload = http.getString();                  //Get the response payload
 
           Serial.println(httpGet);   //Print HTTP return code
           Serial.println(payload);    //Print request response payload
      
      
              if (payload[14] == '1'){
                Serial.println("Forward");
                digitalWrite(powPin1, HIGH);
                digitalWrite(powPin2, LOW);
                digitalWrite(powPin3, HIGH);
                digitalWrite(powPin4, LOW);
                digitalWrite(powPin5, HIGH);
                digitalWrite(powPin6, LOW);
              }         
              if (payload[14] == '2'){
                Serial.println("Backward");
                digitalWrite(powPin1, LOW);
                digitalWrite(powPin2, HIGH);
                digitalWrite(powPin3, LOW);
                digitalWrite(powPin4, HIGH);
                digitalWrite(powPin5, HIGH);
                digitalWrite(powPin6, LOW);
              }
              if (payload[14] == '4'){
                Serial.println("right");
                digitalWrite(powPin6, HIGH);
                digitalWrite(powPin5, LOW);
              }
              if (payload[14] == '3'){
                Serial.println("left");
                digitalWrite(powPin6, LOW);
                digitalWrite(powPin5, LOW);
              }
              if (payload[14] == '0'){
                Serial.println("Stop");
                digitalWrite(powPin1, LOW);
                digitalWrite(powPin3, LOW);
                digitalWrite(powPin2, LOW);
                digitalWrite(powPin4, LOW);
                digitalWrite(powPin5, HIGH);
              }
          
           http.end();  //Close connection
          }
 
      
      else{
        Serial.println("");
        Serial.println("WiFi not connected");
      }
      delay(300);

}
