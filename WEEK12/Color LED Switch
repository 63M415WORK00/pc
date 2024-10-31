const int BTN_RED = 4;
const int BTN_GREEN = 5;
const int BTN_BLUE = 6;

const int PIN_RED = 8;
const int PIN_GREEN = 9;
const int PIN_BLUE = 10;

bool is_red_on = false;
bool is_green_on = false; 
bool is_blue_on = false;

bool last_red_state = HIGH;
bool last_green_state = HIGH;
bool last_blue_state = HIGH;

void setup() {
  pinMode(BTN_RED, INPUT_PULLUP);
  pinMode(BTN_GREEN, INPUT_PULLUP);
  pinMode(BTN_BLUE, INPUT_PULLUP);
  
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
}

void loop() {
  change_stat(BTN_RED, PIN_RED, &is_red_on, &last_red_state);
  change_stat(BTN_GREEN, PIN_GREEN, &is_green_on, &last_green_state);
  change_stat(BTN_BLUE, PIN_BLUE, &is_blue_on, &last_blue_state);
  delay(5);
}

void change_stat(int btn_pin, int led_pin, bool* status, bool* last_state) {
  bool current_state = digitalRead(btn_pin);
  
  if (current_state == LOW && *last_state == HIGH) {
    // Detects the press and release of the button
    *status = !(*status);
    digitalWrite(led_pin, *status ? HIGH : LOW);
  }
  
  *last_state = current_state; // Update the last state
}
