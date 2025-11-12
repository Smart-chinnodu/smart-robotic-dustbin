/*
 * Smart Robotic Dustbin - Main Controller
 * Author: Ranjith Kumar Veesam
 * Description: Complete Arduino code for intelligent waste management system
 * Features: Auto door, waste sorting, rewards, sanitizer, speech, expressions
 */

#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// ==================== PIN DEFINITIONS ====================
// Sensors
#define IR_DOOR_SENSOR 2          // IR sensor for door trigger
#define IR_WASTE_SENSOR 3         // IR sensor for waste detection
#define ULTRASONIC_TRIG 4         // Ultrasonic trigger (hand detection)
#define ULTRASONIC_ECHO 5         // Ultrasonic echo
#define MOISTURE_SENSOR A0        // Moisture sensor (wet waste)
#define CAPACITIVE_SENSOR A1      // Capacitive sensor (paper detection)
#define INDUCTIVE_SENSOR A2       // Inductive sensor (metal detection)

// Motors & Actuators
#define DOOR_SERVO_PIN 6          // Main door servo
#define SORT_SERVO_WET 7          // Sorting servo - wet compartment
#define SORT_SERVO_DRY 8          // Sorting servo - dry compartment
#define SORT_SERVO_PAPER 9        // Sorting servo - paper compartment
#define SORT_SERVO_COVERS 10      // Sorting servo - covers compartment

// Relays & Pumps
#define SANITIZER_RELAY 11        // Relay for sanitizer pump
#define CHOCOLATE_RELAY 12        // Relay for chocolate dispenser
#define LED_STRIP_PIN 13          // WS2812B LED strip

// Communication
#define MP3_RX 14                 // DFPlayer RX
#define MP3_TX 15                 // DFPlayer TX

// Display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

// ==================== CONSTANTS ====================
#define DOOR_OPEN_ANGLE 90
#define DOOR_CLOSE_ANGLE 0
#define SORT_ANGLE_WET 0
#define SORT_ANGLE_DRY 45
#define SORT_ANGLE_PAPER 90
#define SORT_ANGLE_COVERS 135

#define MOISTURE_THRESHOLD 500    // Threshold for wet waste
#define CAPACITIVE_THRESHOLD 300  // Threshold for paper
#define DISTANCE_THRESHOLD 10     // cm for hand detection
#define DOOR_TIMEOUT 5000         // Door close timeout (ms)

// ==================== OBJECT INITIALIZATION ====================
Servo doorServo;
Servo sortServoWet;
Servo sortServoDry;
Servo sortServoPaper;
Servo sortServoCovers;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
SoftwareSerial mp3Serial(MP3_RX, MP3_TX);
DFRobotDFPlayerMini mp3Player;

// ==================== GLOBAL VARIABLES ====================
enum WasteType { NONE, WET, DRY, PAPER, COVERS };
WasteType currentWasteType = NONE;

bool doorOpen = false;
unsigned long doorOpenTime = 0;
bool wasteDetected = false;
int quoteIndex = 0;

// Daily quotes array
const char* quotes[] = {
  "Cleanliness is next to godliness!",
  "Be the change you wish to see!",
  "Small actions, big impact!",
  "Keep Earth clean and green!",
  "Reduce, Reuse, Recycle!",
  "Every piece counts!",
  "Thank you for caring!",
  "You make a difference!",
  "Save Earth, Save Future!",
  "Together we can do it!"
};

// ==================== SETUP ====================
void setup() {
  Serial.begin(9600);
  mp3Serial.begin(9600);
  
  // Initialize display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  // Initialize servos
  doorServo.attach(DOOR_SERVO_PIN);
  sortServoWet.attach(SORT_SERVO_WET);
  sortServoDry.attach(SORT_SERVO_DRY);
  sortServoPaper.attach(SORT_SERVO_PAPER);
  sortServoCovers.attach(SORT_SERVO_COVERS);
  
  // Set initial positions
  doorServo.write(DOOR_CLOSE_ANGLE);
  resetSortingServos();
  
  // Initialize pins
  pinMode(IR_DOOR_SENSOR, INPUT);
  pinMode(IR_WASTE_SENSOR, INPUT);
  pinMode(ULTRASONIC_TRIG, OUTPUT);
  pinMode(ULTRASONIC_ECHO, INPUT);
  pinMode(MOISTURE_SENSOR, INPUT);
  pinMode(CAPACITIVE_SENSOR, INPUT);
  pinMode(INDUCTIVE_SENSOR, INPUT);
  pinMode(SANITIZER_RELAY, OUTPUT);
  pinMode(CHOCOLATE_RELAY, OUTPUT);
  pinMode(LED_STRIP_PIN, OUTPUT);
  
  digitalWrite(SANITIZER_RELAY, LOW);
  digitalWrite(CHOCOLATE_RELAY, LOW);
  
  // Initialize MP3 player
  if (!mp3Player.begin(mp3Serial)) {
    Serial.println(F("DFPlayer initialization failed"));
  } else {
    mp3Player.volume(25);  // Volume 0-30
    Serial.println(F("DFPlayer ready"));
  }
  
  // Welcome message
  displayWelcome();
  playSound(1);  // Welcome sound
  
  Serial.println(F("Smart Robotic Dustbin Initialized"));
}

// ==================== MAIN LOOP ====================
void loop() {
  // Check for user approach
  if (digitalRead(IR_DOOR_SENSOR) == LOW && !doorOpen) {
    openDoor();
  }
  
  // Check for waste dropped
  if (doorOpen && digitalRead(IR_WASTE_SENSOR) == LOW && !wasteDetected) {
    wasteDetected = true;
    delay(500);  // Allow waste to settle
    currentWasteType = detectWasteType();
    sortWaste(currentWasteType);
    dispenseReward();
    displayThankYou();
    playQuote();
  }
  
  // Auto-close door after timeout
  if (doorOpen && (millis() - doorOpenTime > DOOR_TIMEOUT)) {
    closeDoor();
    wasteDetected = false;
  }
  
  // Check for hand sanitizer request
  if (getDistance() < DISTANCE_THRESHOLD) {
    dispenseSanitizer();
  }
  
  // Idle animation
  if (!doorOpen) {
    displayIdleAnimation();
  }
  
  delay(100);
}

// ==================== DOOR CONTROL ====================
void openDoor() {
  doorOpen = true;
  doorOpenTime = millis();
  doorServo.write(DOOR_OPEN_ANGLE);
  displayHappy();
  playSound(2);  // Door opening sound
  Serial.println(F("Door opened"));
  delay(500);
}

void closeDoor() {
  doorServo.write(DOOR_CLOSE_ANGLE);
  doorOpen = false;
  resetSortingServos();
  displayWaiting();
  playSound(3);  // Door closing sound
  Serial.println(F("Door closed"));
}

// ==================== WASTE DETECTION ====================
WasteType detectWasteType() {
  int moistureValue = analogRead(MOISTURE_SENSOR);
  int capacitiveValue = analogRead(CAPACITIVE_SENSOR);
  int inductiveValue = analogRead(INDUCTIVE_SENSOR);
  
  Serial.print(F("Moisture: ")); Serial.println(moistureValue);
  Serial.print(F("Capacitive: ")); Serial.println(capacitiveValue);
  Serial.print(F("Inductive: ")); Serial.println(inductiveValue);
  
  // Decision logic
  if (moistureValue > MOISTURE_THRESHOLD) {
    Serial.println(F("Detected: WET waste"));
    return WET;
  } else if (capacitiveValue > CAPACITIVE_THRESHOLD) {
    Serial.println(F("Detected: PAPER waste"));
    return PAPER;
  } else if (inductiveValue > 500) {
    Serial.println(F("Detected: METAL/COVERS waste"));
    return COVERS;
  } else {
    Serial.println(F("Detected: DRY waste"));
    return DRY;
  }
}

// ==================== WASTE SORTING ====================
void sortWaste(WasteType type) {
  displayProcessing();
  
  switch(type) {
    case WET:
      sortServoWet.write(SORT_ANGLE_WET);
      Serial.println(F("Sorting to WET compartment"));
      break;
    case DRY:
      sortServoDry.write(SORT_ANGLE_DRY);
      Serial.println(F("Sorting to DRY compartment"));
      break;
    case PAPER:
      sortServoPaper.write(SORT_ANGLE_PAPER);
      Serial.println(F("Sorting to PAPER compartment"));
      break;
    case COVERS:
      sortServoCovers.write(SORT_ANGLE_COVERS);
      Serial.println(F("Sorting to COVERS compartment"));
      break;
    default:
      Serial.println(F("Unknown waste type"));
  }
  
  delay(2000);  // Allow sorting
}

void resetSortingServos() {
  sortServoWet.write(90);
  sortServoDry.write(90);
  sortServoPaper.write(90);
  sortServoCovers.write(90);
}

// ==================== REWARD SYSTEM ====================
void dispenseReward() {
  digitalWrite(CHOCOLATE_RELAY, HIGH);
  delay(1000);  // Dispense duration
  digitalWrite(CHOCOLATE_RELAY, LOW);
  playSound(4);  // Reward sound
  Serial.println(F("Chocolate dispensed"));
}

// ==================== SANITIZER ====================
void dispenseSanitizer() {
  digitalWrite(SANITIZER_RELAY, HIGH);
  delay(500);  // Pump duration
  digitalWrite(SANITIZER_RELAY, LOW);
  displaySanitizer();
  playSound(5);  // Sanitizer sound
  Serial.println(F("Sanitizer dispensed"));
  delay(2000);  // Prevent multiple triggers
}

// ==================== ULTRASONIC DISTANCE ====================
float getDistance() {
  digitalWrite(ULTRASONIC_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIG, LOW);
  
  long duration = pulseIn(ULTRASONIC_ECHO, HIGH);
  float distance = duration * 0.034 / 2;
  
  return distance;
}

// ==================== DISPLAY FUNCTIONS ====================
void displayWelcome() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 20);
  display.println(F("Welcome!"));
  display.setTextSize(1);
  display.setCursor(5, 45);
  display.println(F("I'm here to help"));
  display.display();
}

void displayHappy() {
  display.clearDisplay();
  // Draw happy face
  display.fillCircle(64, 32, 20, SSD1306_WHITE);
  display.fillCircle(55, 27, 3, SSD1306_BLACK);  // Left eye
  display.fillCircle(73, 27, 3, SSD1306_BLACK);  // Right eye
  display.drawLine(55, 38, 73, 38, SSD1306_BLACK);  // Smile
  display.display();
}

void displayThankYou() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 20);
  display.println(F("Thank"));
  display.println(F("  You!"));
  display.display();
}

void displayProcessing() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(20, 28);
  display.println(F("Processing..."));
  display.display();
}

void displayWaiting() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(25, 28);
  display.println(F("Waiting..."));
  display.display();
}

void displaySanitizer() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(15, 28);
  display.println(F("Stay Clean!"));
  display.display();
}

void displayIdleAnimation() {
  static int animFrame = 0;
  if (millis() % 1000 == 0) {
    display.clearDisplay();
    display.fillCircle(64, 32, 20, SSD1306_WHITE);
    
    // Blinking eyes
    if (animFrame % 2 == 0) {
      display.fillCircle(55, 27, 3, SSD1306_BLACK);
      display.fillCircle(73, 27, 3, SSD1306_BLACK);
    } else {
      display.drawLine(50, 27, 60, 27, SSD1306_BLACK);
      display.drawLine(68, 27, 78, 27, SSD1306_BLACK);
    }
    
    display.drawCircle(64, 38, 8, SSD1306_BLACK);  // Neutral mouth
    display.display();
    animFrame++;
  }
}

// ==================== AUDIO FUNCTIONS ====================
void playSound(int trackNumber) {
  mp3Player.play(trackNumber);
  delay(100);
}

void playQuote() {
  // Select and speak a quote
  Serial.println(quotes[quoteIndex]);
  // Send to Raspberry Pi via Serial for TTS
  Serial.print(F("QUOTE:"));
  Serial.println(quotes[quoteIndex]);
  
  quoteIndex = (quoteIndex + 1) % 10;
  delay(3000);
}

// ==================== END ====================
