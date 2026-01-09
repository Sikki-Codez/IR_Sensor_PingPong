# Digital Table Tennis (Pong) with IR Gesture Control

## 📌 Project Overview
A hybrid hardware-software implementation of the classic Pong arcade game, designed for the **CE-231 Digital Logic Design Lab**. 

This project goes beyond standard Arduino games by integrating **Digital Logic Circuits** (Shift Registers) to handle hardware tasks. Instead of buttons, it utilizes **IR Obstacle Sensors** to detect hand gestures, offering a touchless, futuristic gaming experience. The game physics runs on an OLED screen, while the score is offloaded to an external 7-segment display.

## 🚀 Key Features
* **Touchless Control:** Paddles are controlled via analog thresholds using IR Proximity/Obstacle sensors.
* **Dual-Display Architecture:**
    * **Gameplay:** Rendered on a 1.3" SH1106 OLED (128x64 pixels).
    * **Scoreboard:** Driven by a **74HC595 Shift Register** connected to a 2-digit 7-Segment display.
* **Physics Engine:** Includes ball velocity handling, wall bouncing, and paddle collision detection.
* **Sound Effects:** Piezo buzzer feedback for wall hits, paddle hits, and "Game Over" states.
* **Modular Code:** Separates display logic (I2C) from serial data transmission (Shift Register).

## 🛠️ Hardware Requirements
To replicate this project (or run the Proteus simulation), you need:

| Component | Quantity | Notes |
| :--- | :---: | :--- |
| **Arduino Uno** | 1 | ATmega328P Microcontroller |
| **OLED Display** | 1 | SH1106 or SH110X (128x64 I2C) |
| **Shift Register** | 1 | 74HC595 (8-bit Serial-in/Parallel-out) |
| **IR Sensors** | 2 | IR Obstacle Avoidance Modules (Analog Output) |
| **7-Segment Display** | 1 | 2-Digit Common Cathode |
| **Piezo Buzzer** | 1 | Active or Passive |
| **Resistors** | 8-10 | 220Ω (for 7-seg) and 1kΩ (current limiting) |
| **Jumper Wires** | - | M-M and M-F wires |

## 🔌 Wiring Configuration
This configuration matches the `simulationfinalfinal.pdsprj` file and `ping_pong_Code.ino`.

### 1. I2C OLED Display
* **VCC:** 5V
* **GND:** GND
* **SDA:** Analog Pin **A4**
* **SCL:** Analog Pin **A5**
* *Address used:* `0x3C` (Common for SH1106).

### 2. Scoreboard Logic (74HC595 Shift Register)
The Arduino sends serial data to the 74HC595, which then lights up the 7-segment display.
* **DS (Data):** Digital Pin **2**
* **SHCP (Clock):** Digital Pin **3**
* **STCP (Latch):** Digital Pin **4**
* **OE (Output Enable):** GND
* **MR (Master Reclear):** 5V

### 3. Player Inputs (Sensors)
* **Player 1 (Left):** Analog Pin **A0**
* **Player 2 (Right):** Analog Pin **A1**
* *Note:* The code reads analog values (0-1023). A threshold (e.g., `< 500`) determines if the paddle moves.

### 4. Audio
* **Buzzer +:** Digital Pin **6** (PWM capable)
* **Buzzer -:** GND

## 💻 Software & Libraries
### Prerequisites
* **Arduino IDE** (v1.8.x or 2.x)
* **Libraries:** You **must** install these via the Library Manager (*Tools -> Manage Libraries*):
    1.  `Adafruit_GFX` (Graphics Core)
    2.  `Adafruit_SH110X` (Specific driver for SH1106 displays)

### How to Build & Run
1.  **Clone the Repo:** Download this repository to your local machine.
2.  **Open the Sketch:** Navigate to `code/ping_pong_Code.ino` and open it.
3.  **Check Settings:** Ensure `maxScore` is set to your preference (Default: 9).
4.  **Select Board:** Go to *Tools -> Board -> Arduino Uno*.
5.  **Select Port:** Choose the COM port your Arduino is connected to.
6.  **Upload:** Click the Arrow icon (➡️) to flash the code.

## 📂 File Structure
* `code/ping_pong_Code.ino` - The main C++ source code containing game loop, ISRs, and display logic.
* `simulation/simulationfinalfinal.pdsprj` - Full Proteus design suite file.
* `simulation/ROOT.DSN` - The schematic design for Proteus.
* `CE_221_report.pdf` - Detailed project report explaining the logic synthesis and block diagrams.

## ❓ Troubleshooting & User Advice

**1. OLED Display is Blank or "Snowy"**
* **I2C Address:** The code assumes `0x3C`. Some displays use `0x3D`. Use an "I2C Scanner" sketch to find your display's address and update the code line `display.begin(0x3C, ...)`.
* **Driver Mismatch:** If pixels look scrambled, your display might be an SSD1306 instead of SH1106. Change `Adafruit_SH1106` to `Adafruit_SSD1306` in the include lines.

**2. Paddles Move Erratically / Jitter**
* **IR Interference:** IR sensors are sensitive to sunlight and fluorescent lights. Test in a dimmer room.
* **Threshold Tuning:** In `ping_pong_Code.ino`, look for the `analogRead` comparison. If your sensor rests at 1023 and drops to 200 when triggered, ensure your threshold is around `600`.

**3. Scoreboard Not Updating Correctly**
* **Wiring Check:** The 74HC595 is sensitive. Ensure `MR` is pulled HIGH (5V) and `OE` is pulled LOW (GND).
* **Bit Order:** The code shifts data out `MSBFIRST`. If your numbers look inverted, check if your 7-segment display pinout matches standard `A-B-C-D-E-F-G-DP` mapping.

## 👥 Authors
* **Raja Hamza Sikandar** (2024532)
* **Muhammad Ahmad Faisal** (2024335)
* **Muhammad Haider Ali** (2024385)
* **Muhammad Zaid** (2024491)

## 📜 License
This project is open-source and developed for educational purposes at **GIK Institute** (CE-231 DLD Lab).
