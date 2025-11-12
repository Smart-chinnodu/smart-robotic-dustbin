# 🤖 Smart Robotic Dustbin - Intelligent Waste Management System

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Arduino](https://img.shields.io/badge/Arduino-00979D?logo=Arduino&logoColor=white)](https://www.arduino.cc/)
[![Made with Love](https://img.shields.io/badge/Made%20with-❤-red.svg)](https://github.com/Smart-chinnodu)

> An innovative IoT-based robotic waste management system that makes waste disposal fun, rewarding, and eco-friendly!

![Project Banner](diagrams/banner.png)

## 🌟 Overview

The **Smart Robotic Dustbin** is an intelligent waste management solution that combines robotics, IoT, and environmental awareness. This interactive dustbin automatically opens to accept waste, sorts it into categories (wet, dry, paper, covers), rewards users with seeded chocolates wrapped in biodegradable paper, dispenses hand sanitizer, shares daily quotes, and interacts with users through speech and expressive displays.

## ✨ Key Features

### 🚪 Automatic Door Opening
- IR sensor-based proximity detection
- Servo motor controlled stomach door
- Smooth opening and closing mechanism

### ♻️ Intelligent Waste Sorting
- **4-category classification**: Wet, Dry, Paper, and Covers
- Automated sorting mechanism using multiple compartments
- Servo-controlled compartment doors
- Sensor-based waste type detection

### 🍫 Eco-Friendly Reward System
- Dispenses paper-wrapped seeded chocolates
- Biodegradable paper wrapping with embedded seeds
- Seeds grow into plants when discarded
- Servo-operated dispensing mechanism

### 🧴 Touchless Hand Sanitizer Dispenser
- Ultrasonic sensor for hand detection
- Automatic sanitizer pump activation
- Hygiene-promoting feature

### 💬 Interactive Communication
- **Text-to-Speech (TTS)** for friendly conversations
- Daily motivational quotes
- Voice instructions and feedback
- MP3 module integration

### 😊 Emotional Expression Display
- OLED/LCD display showing robot faces
- Different expressions: Happy, Thankful, Waiting, Processing
- Visual feedback for user interactions

### 🎯 User Engagement
- Gamified waste disposal experience
- Educational messages about waste management
- Positive reinforcement for eco-friendly behavior

## 🛠️ Hardware Components

| Component | Quantity | Purpose |
|-----------|----------|----------|
| Arduino Mega 2560 | 1 | Main controller |
| Raspberry Pi 3/4 | 1 | Speech processing & AI |
| IR Sensors | 2 | Door trigger & waste detection |
| Ultrasonic Sensor (HC-SR04) | 2 | Hand detection & distance measurement |
| Servo Motors (SG90) | 5 | Door control & sorting mechanism |
| DFPlayer Mini MP3 Module | 1 | Audio playback |
| Speaker (3W/8Ω) | 1 | Sound output |
| OLED Display (128x64) | 1 | Emotional expressions |
| Moisture Sensor | 1 | Wet waste detection |
| Capacitive/Inductive Sensors | 2 | Material type detection |
| Relay Module (5V) | 2 | Sanitizer pump & chocolate dispenser |
| DC Water Pump | 1 | Sanitizer dispensing |
| LED Strip (WS2812B) | 1m | Ambient lighting |
| 12V Power Supply | 1 | Main power |
| 5V Power Bank | 1 | Backup power |
| Jumper Wires | Set | Connections |
| Breadboard | 1 | Prototyping |

**Additional Materials:**
- Acrylic sheets / Cardboard for body structure
- 3D printed parts (hands, dispensers)
- Seeded chocolates with biodegradable paper wrapping
- Hand sanitizer liquid
- Storage compartments (4 bins)

## 📐 System Architecture

```
┌─────────────────────────────────────────────────────────┐
│              SMART ROBOTIC DUSTBIN SYSTEM               │
├─────────────────────────────────────────────────────────┤
│                                                         │
│  ┌──────────────┐      ┌───────────────────┐          │
│  │  Raspberry   │──────│   Arduino Mega    │          │
│  │     Pi       │ I2C/ │   (Controller)    │          │
│  │  (Speech AI) │ UART │                   │          │
│  └──────────────┘      └─────────┬─────────┘          │
│                                  │                      │
│         ┌────────────────────────┼────────────────┐    │
│         │                        │                │    │
│    ┌────▼────┐            ┌─────▼──────┐   ┌────▼────┐
│    │ Sensors │            │   Motors   │   │ Display │
│    ├─────────┤            ├────────────┤   ├─────────┤
│    │ IR (x2) │            │ Servo (x5) │   │  OLED   │
│    │Ultrasonic│            │  Relays    │   │  LEDs   │
│    │ Moisture│            │            │   │         │
│    │Capacitive│            └────────────┘   └─────────┘
│    └─────────┘                                         │
│                                                         │
│  ┌──────────────────────────────────────────────────┐ │
│  │           WASTE SORTING COMPARTMENTS             │ │
│  ├─────────┬──────────┬──────────┬─────────────────┤ │
│  │   WET   │   DRY    │  PAPER   │     COVERS      │ │
│  └─────────┴──────────┴──────────┴─────────────────┘ │
└─────────────────────────────────────────────────────────┘
```

## 🔌 Circuit Diagram

Detailed circuit connections are available in the [`diagrams/`](diagrams/) folder:
- `circuit_diagram.png` - Complete wiring schematic
- `block_diagram.png` - System block diagram
- `flowchart.png` - Operation flowchart

## 💻 Software Architecture

### Arduino Code Structure
```
code/
├── main_controller.ino        # Main Arduino sketch
├── sensor_handler.h           # Sensor reading functions
├── motor_controller.h         # Servo & motor control
├── display_manager.h          # OLED display functions
├── audio_player.h             # MP3 playback control
└── config.h                   # Pin definitions & constants
```

### Raspberry Pi Python Scripts
```
code/raspberry_pi/
├── speech_engine.py           # Text-to-speech processing
├── quote_generator.py         # Daily quotes database
├── waste_classifier.py        # AI-based waste classification
└── serial_communication.py    # Arduino communication
```

## 🚀 Getting Started

### Prerequisites
- Arduino IDE (v1.8.19 or later)
- Python 3.7+ (for Raspberry Pi)
- Required Arduino Libraries:
  - `Servo.h`
  - `Wire.h`
  - `Adafruit_SSD1306.h`
  - `Adafruit_GFX.h`
  - `DFRobotDFPlayerMini.h`

### Installation Steps

1. **Clone the Repository**
   ```bash
   git clone https://github.com/Smart-chinnodu/Smart-Robotic-Dustbin.git
   cd Smart-Robotic-Dustbin
   ```

2. **Install Arduino Libraries**
   - Open Arduino IDE
   - Go to Sketch → Include Library → Manage Libraries
   - Search and install required libraries

3. **Upload Arduino Code**
   ```bash
   # Open code/main_controller.ino in Arduino IDE
   # Select Board: Arduino Mega 2560
   # Select correct COM port
   # Click Upload
   ```

4. **Setup Raspberry Pi (Optional)**
   ```bash
   cd code/raspberry_pi
   pip install -r requirements.txt
   python speech_engine.py
   ```

5. **Hardware Assembly**
   - Follow the circuit diagram in `diagrams/circuit_diagram.png`
   - Refer to `docs/ASSEMBLY_GUIDE.md` for step-by-step instructions

## 📖 Documentation

- **[Assembly Guide](docs/ASSEMBLY_GUIDE.md)** - Step-by-step hardware assembly
- **[User Manual](docs/USER_MANUAL.md)** - How to use the dustbin
- **[API Reference](docs/API_REFERENCE.md)** - Code documentation
- **[Troubleshooting](docs/TROUBLESHOOTING.md)** - Common issues and solutions

## 🎬 How It Works

1. **User Approach**: IR sensor detects user proximity
2. **Door Opens**: Servo motor opens the stomach door automatically
3. **Waste Detection**: Sensors identify waste type (wet/dry/paper/covers)
4. **Sorting**: Waste is directed to appropriate compartment
5. **Reward Dispensing**: Chocolate dispenser releases seeded chocolate
6. **Sanitizer**: User places hands under sensor, sanitizer is dispensed
7. **Interaction**: Robot speaks a quote and displays happy expression
8. **Door Closes**: Door closes after 5 seconds of no activity

## 📊 Working Demonstration

**Video Demo**: [Coming Soon]

**Key Interactions:**
- 🎥 Waste disposal demonstration
- 🎥 Sorting mechanism in action
- 🎥 Reward system operation
- 🎥 Voice interaction samples

## 🌱 Environmental Impact

- **Seeded Chocolates**: Every disposed waste can grow into a plant
- **Waste Segregation**: Improves recycling efficiency
- **Behavioral Change**: Gamification encourages proper waste disposal
- **Education**: Teaches waste management importance

## 🔧 Customization

You can customize:
- **Quotes Database**: Edit `quotes.txt` for custom messages
- **Expressions**: Modify `display_manager.h` for new faces
- **Audio Files**: Add custom sound effects to SD card
- **Sorting Logic**: Adjust sensor thresholds in `config.h`

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👨‍💻 Author

**Ranjith Kumar Veesam**
- GitHub: [@Smart-chinnodu](https://github.com/Smart-chinnodu)
- Email: ranjithvessam111@gmail.com
- Location: Saitharupeta, Andhra Pradesh, India

## 🙏 Acknowledgments

- Arduino Community for excellent libraries
- Open-source contributors
- Environmental awareness organizations
- All supporters of sustainable technology

## 📸 Gallery

| Front View | Sorting Mechanism | Display |
|------------|-------------------|----------|
| ![Front](diagrams/front_view.png) | ![Sorting](diagrams/sorting.png) | ![Display](diagrams/display.png) |

## 🔮 Future Enhancements

- [ ] Mobile app integration for waste tracking
- [ ] Cloud-based analytics dashboard
- [ ] Solar panel integration
- [ ] AI-powered waste classification
- [ ] Multi-language support
- [ ] Gamification with leaderboards
- [ ] IoT connectivity for remote monitoring

## 📞 Support

If you have any questions or need help, please:
- Open an [Issue](https://github.com/Smart-chinnodu/Smart-Robotic-Dustbin/issues)
- Email: ranjithvessam111@gmail.com

---

<p align="center">
  <strong>Made with ❤️ for a cleaner, greener future</strong>
  <br>
  <sub>Star ⭐ this repository if you found it helpful!</sub>
</p>