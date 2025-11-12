# Assembly Guide - Smart Robotic Dustbin

## Table of Contents
1. [Tools Required](#tools-required)
2. [Step-by-Step Assembly](#step-by-step-assembly)
3. [Circuit Connections](#circuit-connections)
4. [Mechanical Assembly](#mechanical-assembly)
5. [Testing](#testing)

## Tools Required

### Hardware Tools
- Soldering iron and solder
- Wire strippers
- Screwdriver set (Phillips and flathead)
- Hot glue gun
- Drill with bits
- Multimeter
- Breadboard (for testing)
- 3D printer (optional, for custom parts)

### Software Tools
- Arduino IDE
- Python 3.7+
- Serial monitor
- Fritzing (for circuit design)

## Step-by-Step Assembly

### Phase 1: Prepare the Components

#### 1.1 Check All Components
- [ ] Verify all components from the [items_used.md](../items_used.md) list
- [ ] Test individual components before assembly
- [ ] Organize components by category

#### 1.2 Prepare the Enclosure
- [ ] Cut acrylic sheets to dimensions:
  - Front panel: 30cm x 40cm
  - Side panels: 25cm x 40cm (x2)
  - Back panel: 30cm x 40cm
  - Top panel: 30cm x 25cm
  - Bottom panel: 30cm x 25cm
- [ ] Drill holes for:
  - Sensors (6mm diameter)
  - Display (rectangular cutout)
  - Servo motor shafts (8mm diameter)
  - Wire pass-throughs (10mm diameter)

### Phase 2: Electronics Assembly

#### 2.1 Arduino Mega Setup

**Power Connections:**
```
Arduino Mega:
  5V  → Common 5V rail (breadboard)
  GND → Common GND rail (breadboard)
  VIN → 12V power supply (with voltage regulator)
```

#### 2.2 Sensor Connections

**IR Sensors:**
```
IR Sensor 1 (Door Trigger):
  VCC → 5V
  GND → GND
  OUT → Digital Pin 2

IR Sensor 2 (Waste Detection):
  VCC → 5V
  GND → GND
  OUT → Digital Pin 3
```

**Ultrasonic Sensor (HC-SR04):**
```
Ultrasonic Sensor:
  VCC  → 5V
  GND  → GND
  TRIG → Digital Pin 4
  ECHO → Digital Pin 5
```

**Moisture Sensor:**
```
Moisture Sensor:
  VCC → 5V
  GND → GND
  AO  → Analog Pin A0
```

**Capacitive Sensor:**
```
Capacitive Sensor:
  VCC → 5V
  GND → GND
  OUT → Analog Pin A1
```

**Inductive Sensor:**
```
Inductive Sensor:
  VCC → 12V (through relay if needed)
  GND → GND
  OUT → Analog Pin A2
```

#### 2.3 Servo Motor Connections

```
Door Servo:
  Red (VCC)    → 5V (external power recommended)
  Brown (GND)  → GND
  Orange (PWM) → Digital Pin 6

Sorting Servo 1 (Wet):
  VCC → 5V
  GND → GND
  PWM → Digital Pin 7

Sorting Servo 2 (Dry):
  VCC → 5V
  GND → GND
  PWM → Digital Pin 8

Sorting Servo 3 (Paper):
  VCC → 5V
  GND → GND
  PWM → Digital Pin 9

Sorting Servo 4 (Covers):
  VCC → 5V
  GND → GND
  PWM → Digital Pin 10
```

**Important:** Use external 5V power supply for servos to avoid overloading Arduino.

#### 2.4 Relay Module Connections

```
Relay Module 1 (Sanitizer Pump):
  VCC → 5V
  GND → GND
  IN  → Digital Pin 11
  COM → 12V power supply +ve
  NO  → DC Pump +ve
  Pump -ve → 12V power supply GND

Relay Module 2 (Chocolate Dispenser):
  VCC → 5V
  GND → GND
  IN  → Digital Pin 12
  COM → 12V power supply +ve
  NO  → Dispenser Motor +ve
  Motor -ve → 12V power supply GND
```

#### 2.5 Display Connection

**OLED Display (I2C):**
```
OLED Display:
  VCC → 5V
  GND → GND
  SCL → Arduino SCL (Pin 21)
  SDA → Arduino SDA (Pin 20)
```

#### 2.6 Audio Module

**DFPlayer Mini:**
```
DFPlayer Mini:
  VCC    → 5V
  GND    → GND
  RX     → Digital Pin 14 (through 1kΩ resistor)
  TX     → Digital Pin 15
  SPK+ } → Speaker (3W, 8Ω)
  SPK- }
  
Note: Insert micro SD card with MP3 files
```

#### 2.7 Raspberry Pi Connection (Optional)

```
Raspberry Pi ↔ Arduino:
  Pi TX (GPIO 14)  → Arduino RX1 (Pin 19)
  Pi RX (GPIO 15)  → Arduino TX1 (Pin 18)
  Pi GND           → Arduino GND
```

### Phase 3: Mechanical Assembly

#### 3.1 Door Mechanism

1. **Mount Door Servo:**
   - Attach servo to top of enclosure
   - Connect servo arm to door panel using linkage
   - Ensure smooth 90° rotation

2. **Install Door:**
   - Use hinges or servo arm directly
   - Test opening/closing motion
   - Add soft stoppers to prevent damage

#### 3.2 Sorting Mechanism

1. **Create Compartments:**
   - Divide interior into 4 sections
   - Label: WET, DRY, PAPER, COVERS
   - Install separator walls

2. **Install Sorting Servos:**
   - Mount servos above waste entry point
   - Attach sorting flaps/gates to servo arms
   - Test each servo independently

3. **Sorting Flap Design:**
   ```
   Entry Point
       |
       v
   [Servo-controlled flap]
       |
   +---+---+---+---+
   |WET|DRY|PAP|COV|
   +---+---+---+---+
   ```

#### 3.3 Reward Dispenser

1. **Build Dispenser:**
   - Create a chute/tube for chocolates
   - Install servo or relay-controlled gate
   - Load with paper-wrapped seeded chocolates

2. **Positioning:**
   - Place at front of dustbin
   - Accessible to users
   - Protected from weather

#### 3.4 Sanitizer System

1. **Install Pump:**
   - Mount DC pump inside enclosure
   - Connect tubing from sanitizer reservoir
   - Output nozzle at hand height

2. **Reservoir:**
   - Use leak-proof container
   - Capacity: 500ml minimum
   - Easy refill access

#### 3.5 Display & Interface

1. **OLED Display:**
   - Mount on front panel
   - Viewing angle: eye level
   - Weather protection (optional acrylic cover)

2. **LED Lighting:**
   - Install LED strip around display
   - Use for status indication
   - Connect to Pin 13

### Phase 4: Final Assembly

#### 4.1 Wire Management

- [ ] Group wires by function
- [ ] Use cable ties and clips
- [ ] Label all connections
- [ ] Ensure no loose wires
- [ ] Check for potential shorts

#### 4.2 Power Supply

- [ ] Install 12V 5A power adapter
- [ ] Add voltage regulators for 5V components
- [ ] Include power switch
- [ ] Add fuse for protection
- [ ] Optional: backup battery

#### 4.3 Enclosure Closing

- [ ] Verify all components fit properly
- [ ] Ensure adequate ventilation
- [ ] Secure all panels with screws
- [ ] Apply weatherproofing (if outdoor use)
- [ ] Add rubber feet for stability

## Testing

### System Tests

#### Test 1: Power Supply
```
1. Connect power supply
2. Measure voltages:
   - 5V rail: 4.8-5.2V
   - 12V rail: 11.5-12.5V
3. Check for overheating
```

#### Test 2: Sensors
```
1. IR sensors: Wave hand, check Serial output
2. Ultrasonic: Measure distance accuracy
3. Moisture: Test with wet/dry materials
4. Capacitive: Test with paper
```

#### Test 3: Motors
```
1. Door servo: Open/close smoothly
2. Sorting servos: Each moves to correct position
3. Pumps: Flow rate adequate
```

#### Test 4: Display & Audio
```
1. OLED: Shows all expressions
2. Speaker: Clear audio output
3. LEDs: Proper brightness
```

#### Test 5: Complete Workflow
```
1. User approaches → Door opens
2. Drop waste → Sorting works
3. Chocolate dispensed → Received
4. Quote played → Heard clearly
5. Hand placed → Sanitizer dispensed
6. Door closes → After timeout
```

## Troubleshooting

| Issue | Possible Cause | Solution |
|-------|----------------|----------|
| Door won't open | Servo power issue | Check power supply, servo connection |
| Wrong sorting | Sensor calibration | Adjust thresholds in config.h |
| No audio | SD card issue | Reformat SD, check MP3 files |
| Display blank | I2C connection | Check SDA/SCL wires, I2C address |
| Sanitizer not dispensing | Pump or relay | Test relay, check pump voltage |

## Safety Notes

⚠️ **Important Safety Guidelines:**

1. **Electrical Safety:**
   - Always disconnect power before working
   - Use proper wire gauges
   - Insulate all connections
   - Add fuses for protection

2. **Mechanical Safety:**
   - Ensure servo arms won't pinch users
   - Smooth all sharp edges
   - Secure heavy components

3. **Chemical Safety:**
   - Use food-grade sanitizer only
   - Prevent leaks with proper sealing
   - Label all reservoirs

## Maintenance Schedule

### Daily
- Check sanitizer level
- Refill chocolate dispenser
- Empty waste compartments

### Weekly
- Clean sensors
- Test all functions
- Check wire connections

### Monthly
- Lubricate servo motors
- Clean display
- Update software if needed

---

**Assembly Time Estimate:** 8-12 hours

**Difficulty Level:** Intermediate

**Support:** For questions, open an issue on GitHub or email ranjithvessam111@gmail.com
