# Digital Table Tennis Game with IR Paddle Control

## 📌 Project Overview
This project is a hardware-based recreation of the classic Pong game, developed for the **CE-231 Digital Logic Design Lab**. It integrates a microcontroller with external digital logic circuits to create an interactive gaming experience.

Unlike traditional button controls, this system uses **Infrared (IR) Obstacle Sensors** to detect hand gestures, allowing players to move paddles intuitively. The game logic runs on an Arduino, rendering graphics on an OLED screen while offloading score management to an external 7-segment display circuit driven by shift registers.

## 🚀 Key Features
* **Gesture Control:** Non-contact paddle movement using IR sensors and analog thresholding.
* **Hybrid Display System:**
    * **Game Arena:** 128x64 OLED (SH1106) displays the ball, paddles, and physics interactions.
    * **Scoreboard:** 2-digit 7-segment display driven by a **74HC595 Shift Register**.
* **Audio Feedback:** Piezo buzzer provides sound effects for wall bounces, paddle hits, and scoring events.
* **Digital Logic Integration:** Demonstrates the interface between microcontrollers (ATmega328P) and serial-to-parallel logic chips.

## 🛠️ Hardware Requirements
To replicate this project, you will need the following components (as used in the provided Proteus simulation):

| Component | Quantity | Description |
| :--- | :---: | :--- |
| **Microcontroller** | 1 | Arduino Uno (ATmega328P) |
| **Display (Graph)** | 1 | SH1106 / SH110X OLED (128x64 I2C) |
| **Shift Register** | 1 | 74HC595 (8-bit Serial-in/Parallel-out) |
| **Sensors** | 2 | IR Obstacle Avoidance Sensors (or Potentiometers) |
| **Display (Score)** | 1 | 7-Segment Common Cathode Display (2-digit) |
| **Audio** | 1 | Piezo Buzzer |
| **Misc** | - | Resistors, Jumper Wires, Breadboard |

## 🔌 Circuit & Wiring Configuration
### 1. OLED Display (I2C)
* **SDA:** Pin A4
* **SCL:** Pin A5
* **VCC/GND:** 5V / GND

### 2. Scoreboard (74HC595 Shift Register)
The Arduino sends score data serially to the shift register, which drives the 7-segment display to save GPIO pins.
* **LATCH (STCP):** Digital Pin 4
* **CLOCK (SHCP):** Digital Pin 3
* **DATA (DS):** Digital Pin 2

### 3. Input & Audio
* **Player 1 Input:** Analog Pin A0 (or defined digital pin in code)
* **Player 2 Input:** Analog Pin A1
* **Buzzer:** Digital Pin (Defined in sketch, typically PWM enabled)

## 💻 Software & Libraries
The project is written in **C++ (Arduino)**. You must install the following libraries in your Arduino IDE before compiling:

1.  `Adafruit_GFX` (Graphics Core)
2.  `Adafruit_SH110X` (OLED Driver)

### Installation Steps
1.  Open the file `code/ping_pong_Code.ino` in Arduino IDE.
2.  Go to **Tools > Manage Libraries**.
3.  Search for and install the libraries listed above.
4.  Select your Board (Arduino Uno) and Port.
5.  Upload the code.

## 🔧 Simulation (Proteus)
A complete simulation file is included in the `simulationfinalfinal.pdsprj.zip` archive.
1.  Extract the zip file.
2.  Open `ROOT.DSN` in Proteus ISIS.
3.  Ensure the `HEX` file path in the Arduino component properties points to your compiled firmware.
4.  Run the simulation to verify logic and display drivers.

## 📄 License
This project is open-source and intended for educational purposes under the Digital Logic Design curriculum.
