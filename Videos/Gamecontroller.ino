#include <Mouse.h>
#include <Keyboard.h>

// Left Joystick (WASD)
const int LEFT_X = A0;
const int LEFT_Y = A1;

// Right Joystick (Mouse)
const int RIGHT_X = A2;
const int RIGHT_Y = A3;

// Enter and Esc buttons
const int ENTER_BTN = PB12;
const int ESC_BTN   = PB13;

// Buttons
const int SHIFT_BTN = PB14;
const int CTRL_BTN  = PB15;

const int E_BTN = PA4;
const int TAB_BTN = PA5;
const int R_BTN = PB6;
const int F_BTN = PA7;
const int V_BTN = PA8;

const int BACKSPACE_BTN = PB0;

const int UP_BTN    = PB1;
const int DOWN_BTN  = PB10;
const int LEFT_BTN  = PB11;
const int RIGHT_BTN = PB8;

const int WIN_BTN = PA9;

const int SPACE_BTN = PB5;
const int LEFT_CLICK_BTN = PA6;
const int RIGHT_CLICK_BTN = PB7; 

// Mouse settings
const int DEADZONE = 40;
const int MAX_SPEED = 12;
const float SMOOTHING = 0.20;

// Smoothed mouse values
float filteredX = 512;
float filteredY = 512;

// Key state tracking
bool wPressed = false;
bool aPressed = false;
bool sPressed = false;
bool dPressed = false;

bool enterPressed = false;
bool escPressed = false;

bool shiftPressed = false;
bool ctrlPressed = false;

bool ePressed = false;
bool tabPressed = false;
bool rPressed = false;
bool fPressed = false;
bool vPressed = false;

bool backspacePressed = false;

bool upPressed = false;
bool downPressed = false;
bool leftPressed = false;
bool rightPressed = false;

bool winPressed = false;

bool spacePressed = false;
bool leftClickPressed = false;
bool rightClickPressed = false;

void setup() {
  Mouse.begin();
  Keyboard.begin();

  pinMode(ENTER_BTN, INPUT_PULLUP);
  pinMode(ESC_BTN, INPUT_PULLUP);
  pinMode(SHIFT_BTN, INPUT_PULLUP);
  pinMode(CTRL_BTN, INPUT_PULLUP);

  pinMode(E_BTN, INPUT_PULLUP);
  pinMode(TAB_BTN, INPUT_PULLUP);
  pinMode(R_BTN, INPUT_PULLUP);
  pinMode(F_BTN, INPUT_PULLUP);
  pinMode(V_BTN, INPUT_PULLUP);

  pinMode(BACKSPACE_BTN, INPUT_PULLUP);

  pinMode(UP_BTN, INPUT_PULLUP);
  pinMode(DOWN_BTN, INPUT_PULLUP);
  pinMode(LEFT_BTN, INPUT_PULLUP);
  pinMode(RIGHT_BTN, INPUT_PULLUP);

  pinMode(WIN_BTN, INPUT_PULLUP);

  pinMode(SPACE_BTN, INPUT_PULLUP);
  pinMode(LEFT_CLICK_BTN, INPUT_PULLUP);
  pinMode(RIGHT_CLICK_BTN, INPUT_PULLUP);
}

void loop() {

  updateMouse();
  updateWASD();
  updateButtons();

  delay(1);
}

void updateMouse() {

  int rawX = analogRead(RIGHT_X);
  int rawY = analogRead(RIGHT_Y);

  // Low-pass filtering
  filteredX += (rawX - filteredX) * SMOOTHING;
  filteredY += (rawY - filteredY) * SMOOTHING;

  int dx = getMouseMovement(filteredY, true);
  int dy = getMouseMovement(filteredX, false);

  Mouse.move(dx, dy, 0);
}

int getMouseMovement(float value, bool horizontal) {

  float offset = value - 512;

  if (abs(offset) < DEADZONE)
    return 0;

  if (offset > 0)
    offset -= DEADZONE;
  else
    offset += DEADZONE;

  float normalized = offset / (512.0 - DEADZONE);

  if (normalized > 1.0) normalized = 1.0;
  if (normalized < -1.0) normalized = -1.0;

  // Cubic response curve
  float curved = normalized * normalized * normalized;

  int movement = curved * MAX_SPEED;

  // Reverse horizontal direction if needed
  if (horizontal)
    movement = -movement;

  return movement;
}

void updateWASD() {

  int x = analogRead(LEFT_X);
  int y = analogRead(LEFT_Y);

  bool w = (x < 400);
  bool s = (x > 600);

  bool d = (y < 400);
  bool a = (y > 600);

  if (w != wPressed) {
    if (w) Keyboard.press('w');
    else Keyboard.release('w');
    wPressed = w;
  }

  if (s != sPressed) {
    if (s) Keyboard.press('s');
    else Keyboard.release('s');
    sPressed = s;
  }

  if (a != aPressed) {
    if (a) Keyboard.press('a');
    else Keyboard.release('a');
    aPressed = a;
  }

  if (d != dPressed) {
    if (d) Keyboard.press('d');
    else Keyboard.release('d');
    dPressed = d;
  }
}
void handleButton(int pin, bool &state, uint8_t key)
{
  bool pressed = !digitalRead(pin);

  if (pressed && !state)
  {
    Keyboard.press(key);
    state = true;
  }
  else if (!pressed && state)
  {
    Keyboard.release(key);
    state = false;
  }
}
void updateButtons()
{
    handleButton(ENTER_BTN, enterPressed, KEY_RETURN);
    handleButton(ESC_BTN, escPressed, KEY_ESC);

    handleButton(SHIFT_BTN, shiftPressed, KEY_LEFT_SHIFT);
    handleButton(CTRL_BTN, ctrlPressed, KEY_LEFT_CTRL);

    handleButton(E_BTN, ePressed, 'e');
    handleButton(TAB_BTN, tabPressed, KEY_TAB);
    handleButton(R_BTN, rPressed, 'r');
    handleButton(F_BTN, fPressed, 'f');
    handleButton(V_BTN, vPressed, 'v');
    
    handleButton(BACKSPACE_BTN, backspacePressed, KEY_BACKSPACE);

    handleButton(UP_BTN, upPressed, KEY_UP_ARROW);
    handleButton(DOWN_BTN, downPressed, KEY_DOWN_ARROW);
    handleButton(LEFT_BTN, leftPressed, KEY_LEFT_ARROW);
    handleButton(RIGHT_BTN, rightPressed, KEY_RIGHT_ARROW);

    handleButton(WIN_BTN, winPressed, KEY_LEFT_GUI);

    // Space
    handleButton(SPACE_BTN, spacePressed, ' ');

// Left Mouse Click
bool leftState = !digitalRead(LEFT_CLICK_BTN);
if (leftState && !leftClickPressed) {
    Mouse.press(MOUSE_LEFT);
    leftClickPressed = true;
}
else if (!leftState && leftClickPressed) {
    Mouse.release(MOUSE_LEFT);
    leftClickPressed = false;
}

// Right Mouse Click
bool rightState = !digitalRead(RIGHT_CLICK_BTN);
if (rightState && !rightClickPressed) {
    Mouse.press(MOUSE_RIGHT);
    rightClickPressed = true;
}
else if (!rightState && rightClickPressed) {
    Mouse.release(MOUSE_RIGHT);
    rightClickPressed = false;
}
}