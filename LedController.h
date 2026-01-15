#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <Arduino.h>

class LedController {
private:
    int redPin;
    int greenPin;
    int bluePin;

    bool redState;
    bool greenState;
    bool blueState;

    // Helper function to print the LED state
    void printState(const char* color, bool state) {
        Serial.print(color);
        Serial.print(" is now ");
        Serial.println(state ? "ON" : "OFF");
    }

public:
    // Constructor: assign pins and initialize states
    LedController(int r, int g, int b) {
        redPin = r;
        greenPin = g;
        bluePin = b;
        redState = false;
        greenState = false;
        blueState = false;
    }

    void begin() {
        pinMode(redPin, OUTPUT);
        pinMode(greenPin, OUTPUT);
        pinMode(bluePin, OUTPUT);
        allOff();
    }

    // Toggle individual LEDs
    void toggleRed() {
        redState = !redState;
        digitalWrite(redPin, redState);
        Serial.println("Toggling RED LED");
        printState("RED", redState);
    }

    void toggleGreen() {
        greenState = !greenState;
        digitalWrite(greenPin, greenState);
        Serial.println("Toggling GREEN LED");
        printState("GREEN", greenState);
    }

    void toggleBlue() {
        blueState = !blueState;
        digitalWrite(bluePin, blueState);
        Serial.println("Toggling BLUE LED");
        printState("BLUE", blueState);
    }

    // Turn all LEDs on
    void allOn() {
        digitalWrite(redPin, HIGH);
        digitalWrite(greenPin, HIGH);
        digitalWrite(bluePin, HIGH);
        redState = greenState = blueState = true;
        Serial.println("ALL LEDs ON");
    }

void allOff() {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    redState = greenState = blueState = false;

    Serial.println(F(" LED Controller Ready "));
    Serial.println(F("Use the following commands via Serial:"));
    Serial.println(F("  1 Toggle RED LED"));
    Serial.println(F("  2 Toggle GREEN LED"));
    Serial.println(F("  3 Toggle BLUE LED"));
    Serial.println(F("  ON Turn ALL LEDs ON"));
    Serial.println(F("  OFF Turn ALL LEDs OFF"));
    Serial.println(F("============================"));
}

};

#endif
