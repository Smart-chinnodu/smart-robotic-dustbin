# Smart Robotic Dustbin Documentation

## Project Overview
A robotic dustbin system designed to promote eco-friendly habits. It auto-opens the lid, sorts waste, dispenses seed-wrapped chocolate rewards, offers hand sanitizer, displays expressive emotions and daily quotes, and interacts with users via speech.

## Features (Detailed)
- **Auto-opening lid**: Sensor-based detection, servo opens/closes.
- **Waste sorting**: Wet/dry/paper/covers partitioned bins, sensor-based sorting.
- **Reward mechanism**: Dispenser motor delivers eco chocolate with seed paper.
- **Sanitizer feature**: IR sensor triggers sanitizer pump.
- **Interactive display**: Shows emoji faces & quotes, audio output.
- **Speech interaction**: Friendly voice communication, daily quotes.
- **Eco-motivation**: Seed paper ensures positive environmental impact when disposed.

## Modules
- Microcontroller: Arduino/Raspberry Pi
- Sensors: Ultrasonic (lid), IR (hand/sorting), Moisture (wet bin)
- Servo motors: Lid, sorting mechanism
- Actuators: Chocolate dispenser, sanitizer pump
- Display: OLED/LCD
- Audio: TTS module, DFPlayer/minimal MP3 for speech

## Software Flow
1. Detect waste placement.
2. Open lid.
3. Sense and sort waste type.
4. Dispense reward if waste detected.
5. Sanitize hand on request.
6. Display quote and emoji, speak quote.

## Schematic Diagram
See [diagrams/block_diagram.md](../diagrams/block_diagram.md).

## Items Used
See [items_used.md](../items_used.md).

## Source Code
See [code/arduino_sketch.ino](../code/arduino_sketch.ino).

## How to Build
1. Assemble mechanical parts and body
2. Connect sensors, servos, actuators per schematic
3. Upload Arduino code
4. Prepare seed paper-wrapped chocolates
5. Test sorting and rewards

## License
MIT

