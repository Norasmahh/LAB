#include <WiFi.h>
#include <MQTT.h>

#define sensorLDR 32

#define Client_Id   "id_anda"
#define NamaBroker  "broker.emqx.io"
#define namaSSID    "nama_wifi";
#define SSIDpwd     "pwd_wifi";

const char ssid[] = namaSSID;
const char pass[] = SSIDpwd;

WiFiClient net;
MQTTClient client;

void connect() {
    if(WiFi.status() == WL_CONNECTED) {
      if(client.connect(Client_Id)) {
        Serial.println("\nconnected!");
        client.subscribe("topik/cahaya");
        client.subscribe("topik/cahaya1");
      }
    }
}

void setup(){
  pinMode(sensorLDR, INPUT);
  Serial.begin(115200);

  WiFi.begin(ssid, pass);

  client.begin(NamaBroker, net);
  connect();
}

void loop(){
  client.loop();
  delay(10);
  if (!client.connected()) {
    connect();
  }
  int dataLDR = analogRead(sensorLDR);
  Serial.print("Cahaya: ");
  Serial.println(dataLDR);
  client.publish("topik/cahaya", String(dataLDR));
  delay(1000);

  String payload;
  if(dataLDR == 0){
    payload = "BAHAYA, TERLALU GELAP!!";
    Serial.println(payload);
  }
  else{
    payload = " ";
  }
  client.publish("topik/cahaya1", payload);
  

  }
