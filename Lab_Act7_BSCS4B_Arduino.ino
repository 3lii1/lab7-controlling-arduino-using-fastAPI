#include <Arduino.h>
#include "LedController.h"

// ================= LED PINS =================
const int RED_LED   = 7;
const int GREEN_LED = 6;
const int BLUE_LED  = 5;

// ================= LED CONTROLLER =================
LedController leds(RED_LED, GREEN_LED, BLUE_LED);

void setup() {
    Serial.begin(9600);
    leds.begin();
}

void loop() {
    // ================= READ SERIAL COMMAND =================
    if (Serial.available() > 0) {
        String cmd = Serial.readStringUntil('\n');
        cmd.trim();
        cmd.toUpperCase();

        if (cmd == "1") leds.toggleRed();
        else if (cmd == "2") leds.toggleGreen();
        else if (cmd == "3") leds.toggleBlue();
        else if (cmd == "ON") leds.allOn();
        else if (cmd == "OFF") leds.allOff();
    }

    delay(50);
}
