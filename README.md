# Automatic Hand Sensor Pump

A touchless pump controller built with an Arduino, an ultrasonic sensor, and a relay module. When a hand is placed within 10 cm of the sensor, the pump runs for exactly 5 seconds. It will not restart until the hand is removed and placed again.

Useful for touchless soap/sanitizer dispensers, water dispensers, or any hands-free liquid pump.

## How It Works

1. The HC-SR04 ultrasonic sensor continuously measures distance.
2. If an object is detected between 0 and 10 cm, the relay switches ON and the pump runs for 5 seconds.
3. After 5 seconds the pump turns OFF.
4. If the hand is still in front of the sensor, the program waits until it is removed. This prevents the pump from restarting repeatedly.
5. Once the hand is removed, the system is ready for the next cycle.

## Components

| Component | Quantity |
|-----------|----------|
| Arduino (Uno / Nano or compatible) | 1 |
| HC-SR04 ultrasonic sensor | 1 |
| Relay module (active LOW) | 1 |
| DC water pump | 1 |
| External power supply for the pump | 1 |
| Jumper wires | as needed |

## Pin Connections

| Arduino Pin | Connected To |
|-------------|--------------|
| 10 | HC-SR04 TRIG |
| 11 | HC-SR04 ECHO |
| 7 | Relay IN |
| 5V | HC-SR04 VCC, Relay VCC |
| GND | HC-SR04 GND, Relay GND |

The pump is wired through the relay's COM and NO terminals, powered by its own supply. Do not power the pump from the Arduino pins.

## Configuration

You can change these values at the top of the sketch:

```cpp
const int distanceThreshold = 10; // detection distance in cm
```

To change the pump run time, edit the `delay(5000);` line (value in milliseconds).

## Getting Started

1. Clone this repository:
   ```bash
   git clone https://github.com/YOUR-USERNAME/automatic-hand-sensor-pump.git
   ```
2. Open `hand_sensor_pump/hand_sensor_pump.ino` in the Arduino IDE.
3. Select your board and port under **Tools**.
4. Upload the sketch.
5. Open the Serial Monitor at **9600 baud** to see live distance readings.

## Notes

- The relay is **active LOW**: `LOW` turns the pump ON and `HIGH` turns it OFF. The pin is set to `HIGH` at startup so the pump stays off.
- If your relay module is active HIGH, swap the `HIGH` and `LOW` values for `relayPin`.
- Make sure the Arduino and the pump's power supply share a common ground if the relay module requires it.

## Project Structure

```
automatic-hand-sensor-pump/
├── hand_sensor_pump/
│   └── hand_sensor_pump.ino
├── images/
│   └── circuit-diagram.png
└── README.md
```

## License

This project is open source. Add a license of your choice (for example, MIT) in a `LICENSE` file.
