#include <Arduino.h>
#include "LedController.h"

// ================= LED PINS =================
const int RED_LED   = 7;
const int GREEN_LED = 6;
const int BLUE_LED  = 5;

// ================= BUTTON PINS =================
const int BTN_RED   = 12;
const int BTN_GREEN = 11;
const int BTN_BLUE  = 10;

// ================= BUTTON STATES =================
bool lastRedBtn   = HIGH;
bool lastGreenBtn = HIGH;
bool lastBlueBtn  = HIGH;

// ================= LED CONTROLLER =================
LedController leds(RED_LED, GREEN_LED, BLUE_LED);

void setup() {
    Serial.begin(9600);
    leds.begin();

    pinMode(BTN_RED, INPUT_PULLUP);
    pinMode(BTN_GREEN, INPUT_PULLUP);
    pinMode(BTN_BLUE, INPUT_PULLUP);
}

void loop() {
    // ================= READ SERIAL COMMAND =================
    if (Serial.available() > 0) {
        String cmd = Serial.readStringUntil('\n'); // read full line
        cmd.trim();                               // remove spaces/newlines
        cmd.toUpperCase();                        // make uppercase

        if (cmd == "1") leds.toggleRed();
        else if (cmd == "2") leds.toggleGreen();
        else if (cmd == "3") leds.toggleBlue();
        else if (cmd == "ON") leds.allOn();
        else if (cmd == "OFF") leds.allOff();
    }

    // ================= BUTTONS =================
    bool currentRedBtn = digitalRead(BTN_RED);
    if (lastRedBtn == HIGH && currentRedBtn == LOW) {
        Serial.println("BUTTON_RED");
        delay(150);
    }
    lastRedBtn = currentRedBtn;

    bool currentGreenBtn = digitalRead(BTN_GREEN);
    if (lastGreenBtn == HIGH && currentGreenBtn == LOW) {
        Serial.println("BUTTON_GREEN");
        delay(150);
    }
    lastGreenBtn = currentGreenBtn;

    bool currentBlueBtn = digitalRead(BTN_BLUE);
    if (lastBlueBtn == HIGH && currentBlueBtn == LOW) {
        Serial.println("BUTTON_BLUE");
        delay(150);
    }
    lastBlueBtn = currentBlueBtn;

    delay(50);
}
