# Hawak Mo Ang Beep: An Arduino-Based Buzz Wire Game

📋 System Overview
"Hawak Mo Ang Beep" is a single-player precision game where players navigate a metal ring along a wire maze within a 5-minute limit. The system features:

1. **RFID Activation**: The game remains locked until a valid ID card is scanned.
2. **Proximity Detection**: An ultrasonic sensor detects the player within 5 inches to start the countdown.
3. **Dynamic Penalty System**: Every mistake (ring touching the wire) deducts 10 seconds from the timer and triggers an audio-visual alert.

🛠️ **Hardware Components**
**Microcontroller**: Arduino

**Inputs**: 
1. RFID-RC522 (Access Activation)
2. Ultrasonic Sensor (Proximity Detection)
3. Metal Track & Ring (Conductive Detection)

**Outputs**: 
1. I2C LCD Display (16x2) (Visual Interface)
2. Active Buzzer (Audio Feedback)

🕹️ **How to Play**
1. **Idle State**: The LCD will display "TAP YOUR ID".
2. **Activation**: Scan a valid RFID card to unlock the system.
3. **Detection**: Step within 5 inches of the ultrasonic sensor to trigger the player detection sequence.
4. **Gameplay**: After a 5-second countdown, navigate the ring through the maze. Avoid touching the wire!
5. **Winning**: Reach the End Plate before time expires to trigger the victory sequence.

💻 **Software & Installation**
1. Install the Arduino IDE.
2. Install the following libraries via the Library Manager:
   MFRC522 (for RFID)
   LiquidCrystal_I2C (for LCD)
3. Connect the hardware according to the pin definitions in the .ino file.
4. Upload the code to your Arduino board.
