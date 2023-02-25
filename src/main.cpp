#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "env.h"

#define switch_1 21
#define switch_2 19
#define switch_3 18

char * endpoint = "https://ecse-three-led-api.onrender.com/api/state";

void setup() {

  pinMode(switch_1, OUTPUT);
  pinMode(switch_2, OUTPUT);
  pinMode(switch_3, OUTPUT);

  Serial.begin(9600);
  WiFi.begin(WIFI_SSID,WIFI_PASS);

  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:

  if (WiFi.status() == WL_CONNECTED){
    HTTPClient http;

    String http_response;

    http.begin(endpoint);
    http.addHeader("X-API-Key","Kingsley#9729");

    int httpResponseCode = http.GET();

    if(httpResponseCode>0){
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      Serial.print("Response from server: ");
      http_response = http.getString();
      

    }
    else {
      Serial.print("Error Code: ");
      Serial.println(httpResponseCode);
    }

    http.end();

    // Stream& input;

StaticJsonDocument<192> doc;

DeserializationError error = deserializeJson(doc, http_response);

if (error) {
  Serial.print("deserializeJson() failed: ");
  Serial.println(error.c_str());
  return;
}

const char* id = doc["_id"]; // "63fa370b77ef4b58d465b0bd"
const char* user = doc["user"]; // "Kingsley#9729"
bool light_switch_1 = doc["light_switch_1"]; // false
bool light_switch_2 = doc["light_switch_2"]; // true
bool light_switch_3 = doc["light_switch_3"]; // true

Serial.println("");

Serial.print("light_switch_1: ");
Serial.println(light_switch_1);

Serial.print("light_switch_2: ");
Serial.println(light_switch_2);

Serial.print("light_switch_3: ");
Serial.println(light_switch_3);

Serial.println("");

//switch 1
if (light_switch_1==0)
{
  digitalWrite(switch_1,LOW);
}
else{
  digitalWrite(switch_1,HIGH);
}

//switch 2
if (light_switch_2==0)
{
  digitalWrite(switch_2,LOW);
}
else{
  digitalWrite(switch_2,HIGH);
}

//switch 3
if (light_switch_3==0)
{
  digitalWrite(switch_3,LOW);
}
else{
  digitalWrite(switch_3,HIGH);
}


  }

  else {
    return;
  }
}