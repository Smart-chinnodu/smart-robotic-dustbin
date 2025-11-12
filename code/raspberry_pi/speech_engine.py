#!/usr/bin/env python3
"""
Speech Engine for Smart Robotic Dustbin
Handles text-to-speech functionality using pyttsx3 or gTTS
Author: Ranjith Kumar Veesam
"""

import serial
import time
import pyttsx3
import threading
import logging

# Configure logging
logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(levelname)s - %(message)s'
)

class SpeechEngine:
    def __init__(self, serial_port='/dev/ttyUSB0', baud_rate=9600):
        """
        Initialize the speech engine and serial communication
        
        Args:
            serial_port: Serial port for Arduino communication
            baud_rate: Serial communication speed
        """
        # Initialize TTS engine
        self.tts_engine = pyttsx3.init()
        self.configure_voice()
        
        # Initialize serial communication
        try:
            self.serial = serial.Serial(serial_port, baud_rate, timeout=1)
            time.sleep(2)  # Wait for connection
            logging.info(f"Serial connection established on {serial_port}")
        except Exception as e:
            logging.error(f"Failed to establish serial connection: {e}")
            self.serial = None
        
        # Thread control
        self.running = True
        
    def configure_voice(self):
        """Configure TTS voice properties"""
        voices = self.tts_engine.getProperty('voices')
        
        # Select a friendly voice (usually index 1 is female)
        if len(voices) > 1:
            self.tts_engine.setProperty('voice', voices[1].id)
        
        # Set speech rate (words per minute)
        self.tts_engine.setProperty('rate', 150)
        
        # Set volume (0.0 to 1.0)
        self.tts_engine.setProperty('volume', 0.9)
        
        logging.info("TTS engine configured")
    
    def speak(self, text):
        """
        Convert text to speech
        
        Args:
            text: String to be spoken
        """
        logging.info(f"Speaking: {text}")
        self.tts_engine.say(text)
        self.tts_engine.runAndWait()
    
    def speak_async(self, text):
        """
        Speak text in a separate thread to avoid blocking
        
        Args:
            text: String to be spoken
        """
        thread = threading.Thread(target=self.speak, args=(text,))
        thread.daemon = True
        thread.start()
    
    def listen_to_arduino(self):
        """
        Listen for commands from Arduino and respond with speech
        """
        if not self.serial:
            logging.warning("Serial connection not available")
            return
        
        logging.info("Listening for Arduino commands...")
        
        while self.running:
            try:
                if self.serial.in_waiting > 0:
                    line = self.serial.readline().decode('utf-8').strip()
                    
                    if line.startswith("QUOTE:"):
                        quote = line.replace("QUOTE:", "").strip()
                        self.speak_async(quote)
                    
                    elif line.startswith("SPEAK:"):
                        message = line.replace("SPEAK:", "").strip()
                        self.speak_async(message)
                    
                    elif line == "WELCOME":
                        self.speak_async("Hello! I am your smart dustbin. Please dispose your waste properly.")
                    
                    elif line == "THANKYOU":
                        self.speak_async("Thank you for keeping the environment clean!")
                    
                    elif line == "SANITIZE":
                        self.speak_async("Please sanitize your hands. Stay healthy!")
                    
                    logging.info(f"Received from Arduino: {line}")
                
                time.sleep(0.1)
                
            except KeyboardInterrupt:
                logging.info("Stopping speech engine...")
                self.running = False
                break
            except Exception as e:
                logging.error(f"Error: {e}")
                time.sleep(1)
    
    def send_to_arduino(self, message):
        """
        Send a message to Arduino
        
        Args:
            message: String to send
        """
        if self.serial:
            self.serial.write(f"{message}\n".encode())
            logging.info(f"Sent to Arduino: {message}")
    
    def close(self):
        """Clean up resources"""
        self.running = False
        if self.serial:
            self.serial.close()
        logging.info("Speech engine closed")

def main():
    """Main function"""
    # Create speech engine instance
    engine = SpeechEngine(serial_port='/dev/ttyUSB0', baud_rate=9600)
    
    try:
        # Start listening to Arduino
        engine.listen_to_arduino()
    except KeyboardInterrupt:
        print("\nShutting down...")
    finally:
        engine.close()

if __name__ == "__main__":
    main()
