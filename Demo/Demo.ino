#include <WiFi.h>
#include <WiFiClient.h>
#include "FirebaseESP32.h"
#include <ArduinoJson.h>

#define WIFI_SSID "Ao Thuat Gia"
#define WIFI_PASS "aothatday"

#define FIREBASE_HOST "https://system-automotive-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "xyQ6HObPzbU5g1e36Bk4nzpzn8jqG90W2Ty6plD3"

#define move_sensor 32

  FirebaseData firebaseData;
  FirebaseAuth auth;
  FirebaseConfig config;

String path = "/";
FirebaseJson json;

void setup() {

  pinMode(move_sensor, INPUT);

  Serial.begin(115200);
  WiFi.begin(WIFI_SSID,WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  config.api_key = FIREBASE_AUTH;
  config.database_url = FIREBASE_HOST;
  Firebase.begin(&config, &auth);
  //Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  if(!Firebase.beginStream(firebaseData, path))  
  {
    Serial.println("REASON: " + firebaseData.errorReason() );
    Serial.println();
  }
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

}

void loop() {

  int value = digitalRead(move_sensor);
  Firebase.setInt(firebaseData, path + "/LED/Status", 20);

}