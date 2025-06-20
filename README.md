# F1 Tire Health and Speed Simulator
This project is best viewed using this link to tinkercad, a controlled virtual simulation that was used to test components. https://www.tinkercad.com/things/hPNPCqyd4Wd-frantic-densor-hango/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard%2Fdesigns%2Fcircuits
## Overview
This project simulates an F1 car's tire health, speed, and lap timing using an Arduino with a NeoPixel LED strip and an I2C LCD display. It provides a realistic simulation where tire degradation impacts maximum speed, and the user receives visual alerts when tires are worn or when speed exceeds safe limits.

The simulation adjusts speed based on tire type and prevents exceeding the tires' RPM limits, providing a warning light when limits are breached. This helps users understand tire management in racing scenarios.

![image](https://github.com/user-attachments/assets/a60696d8-e0a7-4054-b2b1-1aff0bde3ba8)

---

## Features
- **Speed Simulation:** Speed is controlled via a potentiometer input and capped by tire-specific max speeds.
- **Tire Types:** Supports `soft`, `medium`, and `hard` tires, each with distinct health and max speed characteristics.
- **Tire Health Monitoring:** Tire health decreases each lap, affecting speed and triggering visual alerts.
- **Visual Feedback:** Uses a 12-LED NeoPixel strip to display tire condition via colors (green, orange, red).
- **Warning System:** A warning LED blinks if the simulated speed exceeds tire capacity.
- **Lap Timing:** Calculates and displays remaining lap time on a 16x2 I2C LCD.
- **User Interaction:** Tire type can be set through the terminal (currently hardcoded in code).

---

## Hardware Components
- Arduino Uno or compatible microcontroller
- Adafruit NeoPixel LED strip (12 LEDs)
- Adafruit I2C Liquid Crystal Display (16x2)
- Potentiometer (connected to analog input A0)
- Warning LED (connected to pin 2)
- Additional LEDs for tire type indicators (pins 3, 4, 5, 6)

---

## Wiring Summary
- NeoPixel data line → Arduino pin 2
- LCD I2C pins → SDA, SCL on Arduino
- Potentiometer wiper → Analog input A0
- Warning LED → Digital pin 2
- Tire type LEDs → Digital pins 3, 4, 5, 6

*Refer to component datasheets and Arduino pinout for detailed wiring.*

---

## How It Works
1. **Setup:** Initializes LCD, LEDs, NeoPixels, and sets initial lap timer.
2. **Tire Selection:** Based on the tire type string (`soft`, `medium`, or `hard`), the program sets tire health and max speed.
3. **Speed Control:** Reads potentiometer input, maps it to speed while respecting max speed limits per tire type.
4. **Tire Health:** Decreases with each lap completed; tire health affects NeoPixel color to warn the user.
5. **Warning Light:** If speed exceeds tire max speed, a warning LED blinks.
6. **Lap Timer:** Calculates lap time based on track length and current speed, displaying countdown on the LCD.
7. **NeoPixel Visualization:** Displays tire condition color and a blinking effect to indicate current status.

---

## Code Structure
- **`setup()`**: Initializes peripherals and starts lap timer.
- **`loop()`**: Main control loop handling tire type logic, speed control, LED updates, and lap timing.
- **`softTyres()`, `mediumTyres()`, `hardTyres()`**: Functions that simulate behavior for each tire type, including speed capping and warning signals.
- **`setColor()`**: Sets NeoPixel LED colors based on tire health.
- **`lapTimeCalculator()`**: Calculates lap progress and updates lap counters, tire health, and LCD output.

---

## Usage
1. Connect all hardware components as per the wiring summary.
2. Upload the Arduino sketch to your board.
3. Adjust the potentiometer to simulate throttle input.
4. Watch the LCD for speed and lap timing updates.
5. Observe NeoPixel LED colors reflecting tire health status.
6. When the warning LED blinks, it indicates the tire speed limit has been reached or exceeded.
7. Complete laps and observe tire degradation over time.

---

## Notes
- The tire type (`soft`, `medium`, `hard`) is currently set via the code in the `tyres` string variable.
- The simulation is designed to run for 52 laps on a 5.891 km track, simulating Silverstone F1 race conditions.
- Maximum speeds and tire health values are based on realistic F1 data and assumptions.
- The environment also lags a lot due to the large amount of data being processed, this can be fixed by relying less on the unisigned long time variable

