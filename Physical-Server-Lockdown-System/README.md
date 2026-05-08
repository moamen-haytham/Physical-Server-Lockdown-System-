# [cite_start]Physical Server Lockdown System [cite: 2, 3]

[cite_start]**Integrated Physical Security and Instant Cyber Response System** [cite: 4]
[cite_start]*Developed by Team Bellabit [cite: 5] - [cite_start]Helwan Technological University (HITU)* [cite: 1]

## 📌 Project Overview
This project bridges the critical gap between physical security and cybersecurity[cite: 5]. Enterprise firewalls protect networks, but physical vulnerabilities are often overlooked. Our standalone system detects physical breaches and triggers an instantaneous cyber response (server encryption) in milliseconds, neutralizing the threat before data extraction[cite: 5]. 

## 🏗️ System Architecture
[cite_start]The system operates independently without relying on corporate infrastructure [cite: 22, 61][cite_start], divided into two main zones[cite: 33]:
* [cite_start]**External Zone:** RFID Card Authentication handled by an ESP8266[cite: 30, 31].
* [cite_start]**Internal Core:** The central ESP32E microcontroller handling sensor logic and sending encrypted UDP commands[cite: 39, 41].

## ⚙️ Core Logic (Zero-Trust)
[cite_start]We implemented a strict **Zero-Trust Logic**[cite: 136]. [cite_start]Access is granted ONLY if two conditions are met simultaneously[cite: 137]:
1. [cite_start]A valid RFID card is scanned within a 5-second window[cite: 137].
2. [cite_start]The current time (verified by a battery-backed RTC ZS-042) falls within the authorized working shift[cite: 137, 200].

[cite_start]If any condition fails during a door opening, the system classifies it as a breach[cite: 137].

## 🛡️ Defense Layers
* [cite_start]**First Line of Defense:** MC-38 Magnetic Door Sensor detects forced entry[cite: 94, 95].
* [cite_start]**Backup Layer:** IR Motion Sensor detects movement if walls/windows are bypassed[cite: 112, 114].
* [cite_start]**Physical Deterrence:** An Active Buzzer triggers immediately to disorient the intruder[cite: 127, 128].
* [cite_start]**Ultimate Cyber Response:** An instant UDP payload is transmitted to the enterprise server, executing an automated encryption script in milliseconds[cite: 161, 163].

## 🔌 Hardware Components
* ESP32E (Main Controller / Air-Gapped AP)
* NodeMCU ESP8266 (External Auth)
* RC522 RFID Reader
* MC-38 Magnetic Door Contact (Wired COM & NO)
* Infrared (IR) Motion Sensor
* RTC ZS-042 (Time Validation)
* Active Piezo Buzzer

## 🚀 How to Use
1. Flash `External_Auth.ino` to the ESP8266 board.
2. Flash `Internal_Core.ino` to the ESP32E board.
3. Power up the Internal Core first and wait 2 seconds for sensor calibration.
4. The system is armed automatically. Scan a valid RFID card to open the 5-second access window.