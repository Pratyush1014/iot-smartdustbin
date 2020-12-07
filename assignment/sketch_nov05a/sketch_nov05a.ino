#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

/*************************** Sketch Code ************************************/
#define R_SSID "KNET"      //"wifi router name"
#define PASS "pratyush@1234"        //"wifi password"

/************************* Adafruit.io Setup *********************************/

#define auth " 5yOumDII_IMbVgysLjkvv_2UX2vYl1uM"          

/************ Global State ******************/

WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;


/****************************** Feeds ***************************************/

void setup(){
  Serial.begin(9600);

 delay(10);
  
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(R_SSID);

  WiFi.begin(R_SSID, PASS);
  int counter=10;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    counter--;
    if(counter==0){
      // reset me
        ESP.reset();
    }
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
  Blynk.begin(auth, R_SSID, PASS);
}

void loop(){
  //while(NodeMCU.available()>0){
  //MQTT_connect();
  Blynk.run();
  int val = Serial.read(); 
  if (val != 0) Serial.println(val);
  if(val == 0) Blynk.notify("BIn Filled") ;


  delay(500);
 
  }
