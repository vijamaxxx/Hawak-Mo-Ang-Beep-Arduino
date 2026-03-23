/* * PROJECT: Smart Buzz Wire Game
 * SENSORS: RFID, Ultrasonic Sensor, Wire Contact Sensor
 * MEMBERS: Jepsie Beron, Via Celis, Janna Del Mundo, Mark Payo
 */

#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// --- PIN ASSIGNMENTS ---
#define SS_PIN 10         // RFID SDA Pin
#define RST_PIN 9         // RFID Reset Pin
const int trigPin = 2;    // Ultrasonic Trigger
const int echoPin = 3;    // Ultrasonic Echo
const int wirePin = 7;    // The Main Maze Wire
const int winPin = 4;     // The End Finish Plate
const int buzzerPin = 8;  // Active Buzzer (+)

// --- INITIALIZE HARDWARE ---
MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// --- GAME STATE VARIABLES ---
bool authorized = false;    // Becomes true after RFID scan
bool gameRunning = false;   // Becomes true after 5-inch detection
unsigned long startTime;    // Holds the timestamp when game starts
unsigned long lastPenaltyTime = 0; // For "Debouncing" the wire touch
long gameDuration = 300000; // 5 Minutes in milliseconds
int mistakes = 0;           // Total touches on the wire

void setup() {
  Serial.begin(9600);       // Start Serial Monitor for debugging
  SPI.begin();              // Start SPI for RFID
  rfid.PCD_Init();          // Start RFID Reader
  
  lcd.init();               // Start LCD
  lcd.backlight();          // Turn on LCD Light
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(wirePin, INPUT_PULLUP); // Wire stays HIGH until touched by GND
  pinMode(winPin, INPUT_PULLUP);  // End Plate stays HIGH until touched by GND
  pinMode(buzzerPin, OUTPUT);     // Output for Active Buzzer
  
  resetToStart();           // Set initial "Tap ID" screen
}

void loop() {
  // --- STEP 1: WAITING FOR RFID ---
  if (!authorized) {
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
      authorized = true;
      activeBeep(200);      // Success beep
      lcd.clear();
      lcd.print("ACCESS GRANTED");
      delay(1500);
      lcd.clear();
      lcd.print("STEP UP TO PLAY");
      lcd.setCursor(0, 1);
      lcd.print("Detecting player");
    }
  } 
  // --- STEP 2: ULTRASONIC DETECTION (5 INCHES) ---
  else if (!gameRunning) {
    int dist = getDistance(); 
    Serial.print("Distance: "); Serial.println(dist); // Check this in Serial Monitor

    if (dist > 1 && dist <= 5) { // If player is 5 inches away or closer
      lcd.clear();
      lcd.print("Player Detected!");
      activeBeep(400);
      delay(1000);
      startSequence(); // Move to 5-second countdown
    }
  } 
  // --- STEP 3: ACTIVE GAMEPLAY ---
  else {
    updateGame();
  }
}

// Resets everything to the very beginning
void resetToStart() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Buzz Wire Game ");
  lcd.setCursor(0, 1);
  lcd.print("   TAP YOUR ID  ");
  authorized = false;
  gameRunning = false;
  mistakes = 0;
  gameDuration = 300000; 
}

// 5-second countdown before timer starts
void startSequence() {
  lcd.clear();
  lcd.print("  GET READY...  ");
  for (int i = 5; i > 0; i--) {
    lcd.setCursor(7, 1);
    lcd.print(i);
    activeBeep(100); // Short tick every second
    delay(900);
  }
  lcd.clear();
  lcd.print("   GO! GO! GO!  ");
  activeBeep(600); // Long start beep
  delay(500);
  lcd.clear();
  startTime = millis(); // Save the start time
  gameRunning = true;
}

void updateGame() {
  long elapsed = millis() - startTime;
  long remaining = gameDuration - elapsed;

  // --- LOSS CONDITION: TIME OUT ---
  if (remaining <= 0) {
    lcd.clear();
    lcd.print("  TIME EXPIRED  ");
    lcd.setCursor(0, 1);
  lcd.print("   YOU LOSE :(  ");
    digitalWrite(buzzerPin, HIGH); delay(2000); digitalWrite(buzzerPin, LOW);
    resetToStart();
    return;
  }

  // --- WIN CONDITION: TOUCHED END PLATE ---
  if (digitalRead(winPin) == LOW) {
    gameRunning = false;
    lcd.clear();
    lcd.print("Congratulations!");
    lcd.setCursor(0, 1);
    lcd.print("    You won!    ");
    
    // Victory rapid beeps
    for(int i = 0; i < 6; i++) {
      activeBeep(100); delay(100);
    }
    delay(4000);
    resetToStart();
    return;
  }

  // --- PENALTY: TOUCHED THE WIRE ---
  if (digitalRead(wirePin) == LOW && (millis() - lastPenaltyTime > 1000)) {
    mistakes++;
    gameDuration -= 10000; // Subtract 10 seconds
    lastPenaltyTime = millis();
    
    lcd.setCursor(0, 0);
    lcd.print("  -10 SECONDS!  ");
    digitalWrite(buzzerPin, HIGH); delay(600); digitalWrite(buzzerPin, LOW); 
    lcd.clear();
  }

  // --- UPDATE THE LCD TIMER ---
  int seconds = (remaining / 1000) % 60;
  int minutes = (remaining / 1000) / 60;
  lcd.setCursor(0, 0);
  lcd.print("TIME: ");
  if (minutes < 10) lcd.print("0"); lcd.print(minutes);
  lcd.print(":");
  if (seconds < 10) lcd.print("0"); lcd.print(seconds);

  lcd.setCursor(0, 1);
  lcd.print("MISTAKES: "); lcd.print(mistakes);
}

// Function to control Active Buzzer (On -> Delay -> Off)
void activeBeep(int duration) {
  digitalWrite(buzzerPin, HIGH);
  delay(duration);
  digitalWrite(buzzerPin, LOW);
}

// Calculates distance in INCHES
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measures how long it takes for sound to return
  long duration = pulseIn(echoPin, HIGH, 25000); 
  
  // Sound travels at 74 microseconds per inch (round trip / 2)
  int inches = (duration / 2) / 74; 
  
  if (inches <= 0) return 999; // If no object is detected
  return inches;
}