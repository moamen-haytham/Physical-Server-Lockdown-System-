#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include <MFRC522.h>

const char* ssid = "Bellabit_Secure_Net";
const char* password = "StrongPassword123";

const char* targetIP = "192.168.4.1"; 
const int targetPort = 8888;

WiFiUDP udp;

#define RST_PIN 5 
#define SS_PIN  4 

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  udp.beginPacket(targetIP, targetPort);
  udp.print("AUTH_SUCCESS");
  udp.endPacket();

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  
  delay(3000); 
}