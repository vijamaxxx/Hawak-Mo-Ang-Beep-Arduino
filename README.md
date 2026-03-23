# Hawak Mo Ang Beep: An Arduino-Based Buzz Wire Game

[cite_start]**Project for ITC106 L: Application Development & Emerging Technologies** **Date:** March 2026 [cite: 10]

## 📋 System Overview
[cite_start]"Hawak Mo Ang Beep" is a single-player precision game where players navigate a metal ring along a wire maze within a 5-minute limit[cite: 14]. The system features:
* [cite_start]**RFID Activation:** The game remains locked until a valid ID card is scanned[cite: 21, 30].
* [cite_start]**Proximity Detection:** An ultrasonic sensor detects the player within 5 inches to start the countdown[cite: 22, 31].
* [cite_start]**Dynamic Penalty System:** Every mistake (ring touching the wire) deducts 10 seconds from the timer and triggers an audio-visual alert[cite: 16, 23].

## 🛠️ Hardware Components
* [cite_start]**Microcontroller:** Arduino [cite: 39]
* [cite_start]**Inputs:** * RFID-RC522 (Access Activation) [cite: 26]
    * [cite_start]Ultrasonic Sensor (Proximity Detection) [cite: 27]
    * [cite_start]Metal Track & Ring (Conductive Detection) [cite: 27]
* [cite_start]**Outputs:** * I2C LCD Display (16x2) (Visual Interface) [cite: 27, 40]
    * [cite_start]Active Buzzer (Audio Feedback) [cite: 27, 40]

## 🕹️ How to Play
1. [cite_start]**Idle State:** The LCD will display "TAP YOUR ID"[cite: 30].
2. [cite_start]**Activation:** Scan a valid RFID card to unlock the system[cite: 31, 45].
3. [cite_start]**Detection:** Step within 5 inches of the ultrasonic sensor[cite: 31, 46].
4. [cite_start]**Gameplay:** After a 5-second countdown, navigate the ring through the maze[cite: 32, 47]. Avoid touching the wire!
5. [cite_start]**Winning:** Reach the End Plate before time expires to see the victory message[cite: 35, 50].

## 💻 Software & Installation
1. Install the **Arduino IDE**.
2. Install the following libraries:
    * `MFRC522` (for RFID)
    * `LiquidCrystal_I2C` (for LCD)
3. Connect the hardware according to the pin definitions in the `.ino` file.
4. Upload the code to your Arduino board.

## 👥 Team Members
* [cite_start]Beron, Jepsie Joy [cite: 6]
* [cite_start]Celis, Via Bianca A. [cite: 7]
* [cite_start]Del Mundo, Janna Marion S. [cite: 8]
* [cite_start]Payo, Mark R. [cite: 9]
