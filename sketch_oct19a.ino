#include <WiFi.h>
#include <MQTT.h>

#define LED1 4

#define Client_Id   "kakcikcomel"
#define NamaBroker  "broker.emqx.io"
#define namaSSID    "ASDA97";
#define SSIDpwd     "lahfizihasah17";

const char ssid[] = namaSSID;
const char pass[] = SSIDpwd;

WiFiClient net;
MQTTClient client;

void connect() {
    if(WiFi.status() == WL_CONNECTED) {
      if(client.connect(Client_Id)) {
        Serial.println("\nconnected!");
          client.subscribe("kakcik/LED1");
      }
    }
}

void button(String &topic, String &payload) {
     if(String(topic) == "kakcik/LED1") 
  {
      if(payload =="1")
      {
      Serial.println(payload);
      digitalWrite(LED1,HIGH);
      Serial.println("LED1 ON");
      }
      
      else if(payload =="0")
      {
        Serial.println(payload);
        digitalWrite(LED1,LOW);
        Serial.println("LED1 OFF");
        
      }
  }
}

void setup() {
  pinMode(LED1, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  client.begin(NamaBroker, net);
  client.onMessage(button);
  connect();
}

void loop() {
 client.loop();
 delay(10);
  if (!client.connected()) {
    connect();
  }
}

