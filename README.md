
**Ping‑Pong Game — DLD Project**

- **Overview:** A two‑player electronic ping‑pong game built on Arduino with an SH1106 OLED, a 7‑segment score display driven by a 74HC595 shift register, IR/analog inputs for paddles, and a buzzer for sound effects. This repository contains the sketch used for the DLD course project.

**Features:**
- Two local players with independent up/down inputs.
- OLED game display with moving ball and paddles.
- External 7‑segment score display via a 74HC595 shift register.
- Buzzer sounds for bounces, scoring, victory, and reset.

**Hardware (recommended):**
- Arduino Uno (or compatible)
- SH1106 / SH110X OLED (128x64, I2C)
- 74HC595 shift register
- 2 × IR/analog sensors or potentiometers (player paddle inputs)
- 7‑segment common‑cathode display (2 digits)
- Piezo buzzer
- Momentary push button (reset)
- Jumper wires, resistors (current limiting for 7‑segment), breadboard

**Wiring (as used in the sketch):**
- OLED: I2C (SDA / SCL) to Arduino SDA / SCL (A4 / A5 on Uno). OLED I2C address used: `0x3C`.
- Shift register (74HC595):
	- LATCH (`STCP`) -> Arduino digital pin `4`
	- CLOCK (`SHCP`) -> Arduino digital pin `3`
	- DATA (`DS`)  -> Arduino digital pin `2`
	- 7‑segment is common‑cathode; ensure appropriate current‑limit resistors on each segment.
- Paddle inputs:
	- Player 1 UP -> `A0`
	- Player 1 DOWN -> `A1`
	- Player 2 UP -> `A2`
	- Player 2 DOWN -> `A3`
- Buzzer -> digital pin `6`
- Reset button -> digital pin `7` (configured as `INPUT_PULLUP` in code)

**Software / Libraries:**
- Arduino IDE (or compatible build/upload tool)
- Install libraries: `Adafruit_GFX` and `Adafruit_SH110X` (SH1106/SH110X driver used in the sketch)

**How to build & run**
1. Open the sketch file: [code/ping_pong_Code.ino](code/ping_pong_Code.ino).
2. Install required libraries in the Arduino IDE (`Adafruit_GFX`, `Adafruit_SH110X`).
3. Select your board (e.g., Arduino Uno) and correct COM port.
4. Upload the sketch to the board.
5. Power the OLED and 7‑segment and test controls. Press the reset button to restart the game.

**Sketch notes & configurable values**
- Max score is set by `maxScore` (default `9`).
- Paddle movement checks analog readings against a threshold (`>600`), adjust if your sensors behave differently.
- The 7‑segment is updated via `shiftOut()`; the sketch sends `player2Score` first, then `player1Score`.

**Files**
- [code/ping_pong_Code.ino](code/ping_pong_Code.ino) — main Arduino sketch implementing game logic, display, sound, and score handling.

**Troubleshooting**
- If the OLED stays blank: verify I2C wiring and address, try scanning I2C bus to confirm address.
- If scores don’t update: check shift register wiring, latch/clock/data pins and 7‑segment common cathode wiring/resistors.
- If paddle inputs are noisy, add smoothing or adjust thresholds in the sketch.

If you want, I can also:
- add a wiring diagram or Fritzing sketch;
- convert analog paddle inputs to button inputs for simpler testing;
- prepare a parts list with links.

