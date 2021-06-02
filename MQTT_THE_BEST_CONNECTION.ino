#include <Servo.h>
#include <FastLED.h>
#include "EspMQTTClient.h"

EspMQTTClient client(
  "Smartnes",
  "acdb2020",
  "192.168.89.99",
  "password",
  "password",
  "testClient",
  1883
);

long int vaqt2 = 0;

void setup()
{
  Serial.begin(115200);
  client.enableDebuggingMessages();
  client.enableHTTPWebUpdater(); 
  client.enableLastWillMessage("TestClient/lastwill", "I am going offline");

}
void onConnectionEstablished()
{
  client.subscribe("room/lamp22", [](const String & payload) {
    Serial.println(payload);
  });
}

void loop()
{
  client.loop();
  if (vaqt2 + 100 < millis()) {
    vaqt2 = millis();
    client.publish("room/tuproq", String(vaqt2, DEC) );
  }
}
