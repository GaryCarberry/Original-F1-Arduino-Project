
# F1 Tire Health and Speed Simulation

## Overview
This project simulates an F1 car’s tire health, speed, and lap timing using an Arduino microcontroller, NeoPixel LED strip, and I2C LCD display. It monitors tire degradation over laps, limits speed based on RPM constraints, and provides real-time visual feedback and alerts.

---

## Features
- **Speed Control:** Simulate throttle input via potentiometer; speed is limited to max RPM.
- **Tire Health Monitoring:** Tracks tire wear per lap and updates LED status.
- **Lap Timing:** Calculates lap times based on track length and speed, displaying info on an LCD.
- **Visual Alerts:** NeoPixel LEDs indicate tire condition with colors:
  - Green: Good  
  - Orange: Moderate wear  
  - Red: Critical wear  
- **Serial Output:** Periodic data sent over serial for external monitoring.

---

## Hardware Components
- Arduino Uno (or compatible)
- Adafruit NeoPixel LED strip (12 LEDs)
- Adafruit I2C Liquid Crystal Display (16x2)
- Potentiometer (connected to analog input A0)
- Warning LED (optional)

---

## Wiring Summary
- NeoPixel data pin → Arduino pin 2
- LCD connected via I2C (SDA, SCL pins)
- Potentiometer wiper → Analog input A0
- Warning LED → Digital pin 2 (adjustable)
- Other LEDs → Pins 3, 4, 5, 6 (as configured in code)

*Refer to component datasheets for detailed wiring.*

---

## Installation & Usage
1. Connect the hardware according to the wiring summary.
2. Open the Arduino IDE and load the project code.
3. Upload the code to the Arduino board.
4. Turn the potentiometer to simulate speed changes.
5. Observe tire health and lap info on the LCD.
6. Watch NeoPixel LEDs change color based on tire condition.
7. Optionally, monitor serial output for detailed lap and vehicle status.

---

## Code Structure
- **`setup()`**: Initializes LCD, pins, NeoPixel, and serial communication.
- **`loop()`**: Reads inputs, updates tire health, controls LEDs, calculates lap time.
- **`softTyres()`**: Maps potentiometer input to speed and manages motor simulation.
- **`lapTimeCalculator()`**: Calculates lap timing, manages lap transitions, updates displays.
- **`setColor()`**: Changes NeoPixel colors based on tire health.


---


