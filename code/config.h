/*
 * Configuration file for Smart Robotic Dustbin
 * Contains all pin definitions and constants
 */

#ifndef CONFIG_H
#define CONFIG_H

// ==================== HARDWARE VERSION ====================
#define HARDWARE_VERSION "1.0"
#define SOFTWARE_VERSION "1.0"

// ==================== PIN ASSIGNMENTS ====================
// Sensors
#define IR_DOOR_SENSOR 2
#define IR_WASTE_SENSOR 3
#define ULTRASONIC_TRIG 4
#define ULTRASONIC_ECHO 5
#define MOISTURE_SENSOR A0
#define CAPACITIVE_SENSOR A1
#define INDUCTIVE_SENSOR A2

// Motors
#define DOOR_SERVO_PIN 6
#define SORT_SERVO_WET 7
#define SORT_SERVO_DRY 8
#define SORT_SERVO_PAPER 9
#define SORT_SERVO_COVERS 10

// Relays
#define SANITIZER_RELAY 11
#define CHOCOLATE_RELAY 12
#define LED_STRIP_PIN 13

// Communication
#define MP3_RX 14
#define MP3_TX 15

// ==================== SERVO ANGLES ====================
#define DOOR_OPEN_ANGLE 90
#define DOOR_CLOSE_ANGLE 0
#define SORT_ANGLE_WET 0
#define SORT_ANGLE_DRY 45
#define SORT_ANGLE_PAPER 90
#define SORT_ANGLE_COVERS 135
#define SORT_SERVO_NEUTRAL 90

// ==================== SENSOR THRESHOLDS ====================
#define MOISTURE_THRESHOLD 500
#define CAPACITIVE_THRESHOLD 300
#define INDUCTIVE_THRESHOLD 500
#define DISTANCE_THRESHOLD 10  // cm

// ==================== TIMING CONSTANTS ====================
#define DOOR_TIMEOUT 5000      // ms
#define SORTING_DELAY 2000     // ms
#define SANITIZER_PUMP_TIME 500 // ms
#define CHOCOLATE_DISPENSE_TIME 1000 // ms
#define DEBOUNCE_DELAY 50      // ms

// ==================== DISPLAY SETTINGS ====================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

// ==================== AUDIO SETTINGS ====================
#define MP3_VOLUME 25  // 0-30
#define SOUND_WELCOME 1
#define SOUND_DOOR_OPEN 2
#define SOUND_DOOR_CLOSE 3
#define SOUND_REWARD 4
#define SOUND_SANITIZER 5

// ==================== DEBUG SETTINGS ====================
#define DEBUG_MODE true
#define SERIAL_BAUD 9600

#endif