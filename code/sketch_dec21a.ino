#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define WHITE SH110X_WHITE
#define BLACK SH110X_BLACK


// ================= OLED =================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ================= IR INPUTS AND BUZZER =================
// Player 1
#define P1_UP    A0
#define P1_DOWN  A1

// Player 2
#define P2_UP    A2
#define P2_DOWN  A3 

//BUZZER 
#define BUZZER_PIN 6

//RESET BTN
#define RESET_BTN 7


// ================= SHIFT REGISTER PINS =================
int stcp_Pin = 4;  // LATCH
int shcp_Pin = 3;  // CLOCK
int ds_Pin   = 2;  // DATA-

// ================= GAME SETTINGS =================
const unsigned long PADDLE_RATE = 45;
const unsigned long BALL_RATE = 25;
const uint8_t PADDLE_HEIGHT = 12;
int player1Score = 0;
int player2Score = 0;
int maxScore = 9;
bool resetBall = false;

// ================= BALL =================
uint8_t ball_x = 64, ball_y = 32;
int8_t ball_dir_x = 1, ball_dir_y = 1;
unsigned long ball_update;

// ================= PADDLES =================
unsigned long paddle_update;
const uint8_t PLAYER2_X = 22;
uint8_t player2_y = 26;

const uint8_t PLAYER1_X = 105;
uint8_t player1_y = 26;

// ================= 7-SEGMENT (COMMON CATHODE) =================
const byte segDigits[10] = {
 0b11000000, // 0
  0b11111001, // 1
  0b10100100, // 2
  0b10110000, // 3
  0b10011001, // 4
  0b10010010, // 5
  0b10000010, // 6
  0b11111000, // 7
  0b10000000, // 8
  0b10010000  // 9
};

// ================= FUNCTION DECLARATIONS =================
void drawCourt();
void updateScoreDisplay();
void scorePlayer1();
void scorePlayer2();
void gameOver();
void soundBounce();
void soundScore() ;
void victoryMelody();
void resetSound();
void resetGame();
void waitBeforeStart();

// ================= SETUP =================
void setup() {
  Wire.begin();
  display.begin(0x3C, true);
  display.clearDisplay();

  pinMode(stcp_Pin, OUTPUT);
  pinMode(shcp_Pin, OUTPUT);
  pinMode(ds_Pin, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RESET_BTN, INPUT_PULLUP);


  updateScoreDisplay();

  drawCourt();
  display.display();

  delay(2000);

  ball_update = millis();
  paddle_update = ball_update;
}

// ================= LOOP =================
void loop() {
  bool update = false;
  unsigned long time = millis();

  // ---------- Reset Ball ----------
  if (resetBall) {
    if (player1Score == maxScore || player2Score == maxScore) {
      gameOver();
    } else {
      display.clearDisplay();
      drawCourt();

      ball_x = random(45, 50);
      ball_y = random(23, 33);

      do { ball_dir_x = random(-1, 2); } while (ball_dir_x == 0);
      do { ball_dir_y = random(-1, 2); } while (ball_dir_y == 0);

      resetBall = false;
    }
  }

  // ---------- Ball Update ----------
  if (time > ball_update) {
    uint8_t new_x = ball_x + ball_dir_x;
    uint8_t new_y = ball_y + ball_dir_y;

    // Left / Right wall → score
    if (new_x == 0) {
      scorePlayer1();
      soundScore();
    } 
    else if (new_x == 127) {
      scorePlayer2();
      soundScore();
    }

    // Top / Bottom wall
    if (new_y == 0 || new_y == 63) {
      ball_dir_y = -ball_dir_y;
      soundBounce();
    }

    // Player 2 paddle
    if (new_x == PLAYER2_X &&
        new_y >= player2_y &&
        new_y <= player2_y + PADDLE_HEIGHT) {
      ball_dir_x = -ball_dir_x;
    }

    // Player 1 paddle
    if (new_x == PLAYER1_X &&
        new_y >= player1_y &&
        new_y <= player1_y + PADDLE_HEIGHT) {
      ball_dir_x = -ball_dir_x;
    }

    display.drawPixel(ball_x, ball_y, BLACK);
    display.drawPixel(new_x, new_y, WHITE);
    ball_x = new_x;
    ball_y = new_y;

    ball_update += BALL_RATE;
    update = true;
  }

  // ---------- Paddle Update ----------
  if (time > paddle_update) {
    paddle_update += PADDLE_RATE;

    // Player 2
    display.drawFastVLine(PLAYER2_X, player2_y, PADDLE_HEIGHT, BLACK);
    if (analogRead(P2_UP) > 600 && analogRead(P2_DOWN) < 600) player2_y--;
    if (analogRead(P2_DOWN) > 600 && analogRead(P2_UP) < 600) player2_y++;
    if (player2_y < 1) player2_y = 1;
    if (player2_y + PADDLE_HEIGHT > 63) player2_y = 63 - PADDLE_HEIGHT;
    display.drawFastVLine(PLAYER2_X, player2_y, PADDLE_HEIGHT, WHITE);

    // Player 1
    display.drawFastVLine(PLAYER1_X, player1_y, PADDLE_HEIGHT, BLACK);
    if (analogRead(P1_UP) > 600 && analogRead(P1_DOWN) < 600) player1_y--;
    if (analogRead(P1_DOWN) > 600 && analogRead(P1_UP) < 600) player1_y++;
    if (player1_y < 1) player1_y = 1;
    if (player1_y + PADDLE_HEIGHT > 63) player1_y = 63 - PADDLE_HEIGHT;
    display.drawFastVLine(PLAYER1_X, player1_y, PADDLE_HEIGHT, WHITE);

    update = true;
  }

  if (update) {
    display.display();
  }
  static bool lastResetState = HIGH;
  bool resetState = digitalRead(RESET_BTN);

  if (lastResetState == HIGH && resetState == LOW) {
    resetGame();
  }

  lastResetState = resetState;
}

// ================= FUNCTIONS =================


void waitBeforeStart(unsigned long delayTime = 2000) {
  display.clearDisplay();
  drawCourt();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(20, 25);
  display.print("Get Ready");
  display.display();
  delay(delayTime);  // 2 seconds by default
}
void drawCourt() {
  display.drawRect(0, 0, 128, 64, WHITE);
}

void updateScoreDisplay() {
  digitalWrite(stcp_Pin, LOW);
  shiftOut(ds_Pin, shcp_Pin, MSBFIRST, segDigits[player2Score]);
  shiftOut(ds_Pin, shcp_Pin, MSBFIRST, segDigits[player1Score]);
  digitalWrite(stcp_Pin, HIGH);
}

void scorePlayer1() {
  player1Score++;
  updateScoreDisplay();
  resetBall = true;
}

void scorePlayer2() {
  player2Score++;
  updateScoreDisplay();
  resetBall = true;
}

void gameOver() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);

  display.setCursor(20, 25);
  if (player1Score > player2Score)
    display.print("P1 WINS");
  else
    display.print("P2 WINS");

  display.display();
  victoryMelody();
  delay(2000);

  player1Score = 0;
  player2Score = 0;
  updateScoreDisplay();
  resetBall = true;
}

void soundBounce() {
  tone(BUZZER_PIN, 800, 40);
}

void soundScore() {
  tone(BUZZER_PIN, 300, 120);
}
void victoryMelody() {
  tone(BUZZER_PIN, 784, 200);  // G5
  delay(250);
  tone(BUZZER_PIN, 988, 200);  // B5
  delay(250);
  tone(BUZZER_PIN, 1319, 400); // E6
  delay(450);
  noTone(BUZZER_PIN);
}
void resetSound() {
  tone(BUZZER_PIN, 400, 120);
  delay(150);
  tone(BUZZER_PIN, 300, 120);
  delay(150);
  noTone(BUZZER_PIN);
}
void resetGame() {
  player1Score = 0;
  player2Score = 0;
  updateScoreDisplay();

  display.clearDisplay();
  drawCourt();
  display.display();

  resetSound();        // optional reset beep
  waitBeforeStart(2000); // pause 2 seconds
  resetBall = true;
}