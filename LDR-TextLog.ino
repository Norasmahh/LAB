#include <WiFi.h>
#include <MQTT.h>

#define sensorLDR 32
#define LED1 4

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
        client.subscribe("nama_topik/cahaya");
        client.subscribe("nama_topik/LED1");
      }
    }
}

void setup(){
  pinMode(sensorLDR, INPUT);
  pinMode(LED1, OUTPUT);
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
  client.publish("nama_topik/cahaya", String(dataLDR));
  delay(1000);
  
  String payload;
  if(dataLDR == 0){
    digitalWrite(LED1,HIGH);
    payload = "BAHAYA, TERLALU GELAP!!";
    Serial.println(payload);
  }
  else{
    digitalWrite(LED1,LOW);
    payload = " ";
  }
  client.publish("nama_topik/LED1", payload);
  

  }
