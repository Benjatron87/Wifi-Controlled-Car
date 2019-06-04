#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

    const char* ssid     = ""; // wifi name
    const char* password = ""; // wifi password

    int powPin1 = 14; // pin D5
    int powPin2 = 12; // pin D6
    int powPin3 = 13; // pin D7
    int powPin4 = 15; // pin D8

    int wifiStatus;
     
 void setup() {
      
      Serial.begin(115200);
      delay(500);
     
      // We start by connecting to a WiFi network
     
      Serial.println();
      Serial.println();
      Serial.print("Your are connecting to;");
      Serial.println(ssid);

      pinMode(powPin1, OUTPUT);
      pinMode(powPin2, OUTPUT);
      pinMode(powPin3, OUTPUT);
      pinMode(powPin4, OUTPUT);
      
      WiFi.begin(ssid, password);
      
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
     
}
     
void loop() {

      wifiStatus = WiFi.status();

      if(wifiStatus == WL_CONNECTED){
        
         Serial.println("");
         Serial.println("Your ESP is connected!");  
         Serial.println("Your IP address is: ");
         Serial.println(WiFi.localIP());  

          HTTPClient http;    //Declare object of class HTTPClient
 
          http.begin("http://my-car-thing-8117.herokuapp.com/direction");      //Specify request destination
          http.addHeader("Content-Type", "application/x-www-form-urlencoded");  //Specify content-type header

          int httpGet = http.GET();
          String payload = http.getString();                  //Get the response payload
 
           Serial.println(httpGet);   //Print HTTP return code
           Serial.println(payload);    //Print request response payload
          
          if (httpGet > 0) {

            Serial.println(payload[14]);
      
              if (payload[14] == '1'){
                Serial.println("Forward");
                digitalWrite(powPin1, HIGH);
                digitalWrite(powPin2, LOW);
                digitalWrite(powPin3, HIGH);
                digitalWrite(powPin4, LOW);
              }         
              if (payload[14] == '2'){
                Serial.println("Backward");
                digitalWrite(powPin1, LOW);
                digitalWrite(powPin2, HIGH);
                digitalWrite(powPin3, LOW);
                digitalWrite(powPin4, HIGH);
              }
              if (payload[14] == '3'){
                Serial.println("Left");
                digitalWrite(powPin1, LOW);
                digitalWrite(powPin2, LOW);
                digitalWrite(powPin3, HIGH);
                digitalWrite(powPin4, LOW);
              }
              if (payload[14] == '4'){
                Serial.println("Right");
                digitalWrite(powPin1, HIGH);
                digitalWrite(powPin2, LOW);
                digitalWrite(powPin3, LOW);
                digitalWrite(powPin4, LOW);
              }
              if (payload[14] == '0'){
                Serial.println("Stop");
                digitalWrite(powPin1, LOW);
                digitalWrite(powPin3, LOW);
                digitalWrite(powPin2, LOW);
                digitalWrite(powPin4, LOW);
              }
            }
          
           http.end();  //Close connection
          }
 
      
      else{
        Serial.println("");
        Serial.println("WiFi not connected");
      }
      delay(300);

}
