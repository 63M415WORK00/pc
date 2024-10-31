void setup() {
    pinMode(2, INPUT_PULLUP);
    pinMode(3, OUTPUT);
}
void loop(){
    int sw = digitalRead(2);
    if (sw == 0) {
        digitalWrite(3, 1);
    } else {
        digitalWrite(3, 0);
    }
}
