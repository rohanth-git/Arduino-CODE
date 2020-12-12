#include <ArduinoJson.h>

#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>


 
#include <ESP8266WiFi.h>
#define WIFI_SSID "Rohan"
#define WIFI_PASSWORD "PAssWOrd"
#define WIFI_LED 5//d1
#define ledpin1 4 //d2
#define ledpin2 0 //d3
#define ledpin3 2 //d4

#define FIREBASE_HOST "our-project-90a6b.firebaseio.com"
#define FIREBASE_AUTH "W0V4jIdhirNabRTFUR0YRvQzb06e6DgZU8VBuKKb"

void setup() {
  Serial.begin(9600);
  pinMode(WIFI_LED,OUTPUT);
  pinMode(ledpin1,OUTPUT);
  pinMode(ledpin2,OUTPUT);
  pinMode(ledpin3,OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  
  //connect to wifi
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);  
    digitalWrite(WIFI_LED,LOW);
    delay(100);
    digitalWrite(WIFI_LED,HIGH);
    Serial.print("."); }
    
  Serial.println("");
  Serial.println("WiFi connected");
  digitalWrite(WIFI_LED,HIGH);  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  //Firebase.setString("Variable/Value2", "1.2");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
  delay(1000);
  
}

void loop() {
  String firebaseResult = Firebase.getString("Athar/ledno");
  delay(100);
  if(firebaseResult == "1"){
    Serial.println("status  1 is ON");
    Serial.println(firebaseResult);
    Firebase.setString("Athar/ledno", "OFF");
    digitalWrite(ledpin1,HIGH);
    delay(5000);
    digitalWrite(ledpin1,LOW);
  }else if(firebaseResult == "2"){
    Serial.println("status 2 is ON");
    Serial.println(firebaseResult);
    Firebase.setString("Athar/ledno", "OFF");
    digitalWrite(ledpin2,HIGH);
    delay(5000);
    digitalWrite(ledpin2,LOW);
  }else if(firebaseResult == "3"){
    Serial.println("status 3 is ON");
    Serial.println(firebaseResult);
    Firebase.setString("Athar/ledno", "OFF");
    digitalWrite(ledpin3,HIGH);
    delay(5000);
    digitalWrite(ledpin3,LOW);
  }else{
    Serial.println("status is OFF");
    Serial.println(firebaseResult);
  }
  
} 
