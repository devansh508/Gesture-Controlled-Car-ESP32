##Project Title

# Gesture Controlled Car using ESP32 .

##About the Project

This project allows a robotic car to be controlled in real-time using simple hand gestures. The system consists of:

- **Transmitter ESP32**: Reads gestures via MPU6050 and sends commands wirelessly.

- **Receiver ESP32**: Receives commands and drives motors via L298N motor driver.

##Features



## Features

- Real-time gesture-based control: Forward, Backward, Left, Right, Stop

- Wireless communication using ESP-NOW (low-latency)

- MPU6050 sensor for motion detection

- PWM motor control via L298N driver

- Fully modular code for transmitter and receiver

--

## Hardware Required

| Component             | Quantity |

|----------------------|----------|

| ESP32 Dev Module       | 2        |

| MPU6050 Sensor         | 1        |

| L298N Motor Driver     | 1        |

| DC Gear Motors         | 2-4      |

| Jumper Wires           | As needed|

| Battery Pack           | 1        |

---

## Circuit / Connections

- Connect **MPU6050** to transmitter ESP32 (SDA → 21, SCL → 22, VCC → 3.3V, GND → GND)

- Connect **motors** and **L298N driver** to receiver ESP32

- Ensure correct ENA, ENB, IN1-IN4 pin mapping (as in receiver code)

- Use same ESP-NOW MAC address in transmitter and receiver

---

## How to Run

1. Upload `transmitter.ino` to transmitter ESP32.

2. Upload `receiver.ino` to receiver ESP32 (car).

3. Power both boards.

4. Move your hand to control the car:

   - Forward: Tilt forward

   - Backward: Tilt backward

   - Left: Tilt left

   - Right: Tilt right

   - Stop: Keep flat

---

## Transmitter Code (Snippet)

```cpp

#include <esp_now.h>

#include <WiFi.h>

#include <Wire.h>

#include <Adafruit_MPU6050.h>

#include <Adafruit_Sensor.h>

(Full code in transmitter code.ino)

##Receiver Code (Snippet)

#include <WiFi.h>

#include <esp_now.h>

(Full code inreceiver.ino)

## Future Improvements

- Add OLED display for gesture feedback

- Integrate obstacle avoidance using ultrasonic sensor

- Implement PID control for smoother motion

- Create a mobile app interface for control

---

## Author

- Developed by **[Devansh Chauhan]**

- GitHub Repository: https://github.com/devansh508/Gesture-Controlled-Car-ESP32.git

---

## License

This project is open-source under the **MIT License**.