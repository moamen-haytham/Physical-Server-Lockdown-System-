#include <WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <RTClib.h>

const char* ssid = "Bellabit_Secure_Net";    
const char* password = "StrongPassword123";  

const char* serverIP = "255.255.255.255";    
const int targetPort = 9999;                 
const char* secretKey = "BELLABIT_SECURE_KEY_123"; 

WiFiUDP udp;
const int localUdpPort = 8888; 

const int MC38_PIN = 27;     
const int IR_PIN = 32;       
const int BUZZER_PIN = 26;   

RTC_DS3231 rtc;
unsigned long lastAuthTime = 0;
unsigned long lastDebugTime = 0;
bool isSystemCalm = true;    

void setup() {
  Serial.begin(115200);
  
  pinMode(MC38_PIN, INPUT_PULLUP); 
  pinMode(IR_PIN, INPUT); 
  pinMode(BUZZER_PIN, OUTPUT);
  
  digitalWrite(BUZZER_PIN, HIGH); 

  Wire.begin(21, 22);
  rtc.begin();

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  udp.begin(localUdpPort);
  
  delay(2000); 
}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    char incomingPacket[255];
    int len = udp.read(incomingPacket, 255);
    if (len > 0) incomingPacket[len] = 0;
    
    if (strcmp(incomingPacket, "AUTH_SUCCESS") == 0) {
      lastAuthTime = millis(); 
    }
  }

  bool doorOpen = (digitalRead(MC38_PIN) == LOW); 
  bool motionDetected = (digitalRead(IR_PIN) == LOW); 

  if (millis() - lastDebugTime > 1000) {
    Serial.print("DOOR:"); 
    Serial.print(doorOpen ? "OPEN " : "CLOSED ");
    Serial.print(" | IR:"); 
    Serial.println(motionDetected ? "MOTION" : "CLEAR");
    lastDebugTime = millis();
  }

  bool breachDetected = doorOpen || motionDetected;

  if (breachDetected) {
    digitalWrite(BUZZER_PIN, LOW);

    if (isSystemCalm) { 
      isSystemCalm = false; 
      
      DateTime now = rtc.now();
      bool isWithinShift = (now.hour() >= 8 && now.hour() < 22); 
      bool isAuthRecent = (millis() - lastAuthTime <= 5000);

      if (isAuthRecent && isWithinShift) {
        digitalWrite(BUZZER_PIN, HIGH); 
      } else {
        udp.beginPacket(serverIP, targetPort);
        String payload = String(secretKey) + ":ENCRYPT_NOW";
        udp.print(payload);
        udp.endPacket();
      }
    }
  } else {
    isSystemCalm = true;
    digitalWrite(BUZZER_PIN, HIGH);   
  }
}