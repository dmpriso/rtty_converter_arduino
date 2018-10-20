#ifndef UNIT_TEST

#include <Arduino.h>

#include "baudot_repeater.h"

HardwareInputPin repeater1InPin(2);
HardwareInputPin repeater2InPin(3);
HardwareOutputPin repeater1OutPin(4);
HardwareOutputPin repeater2OutPin(5);

HardwareInputPin repeater1InvertInPin(6, true, true);
HardwareInputPin repeater2InvertInPin(7, true, true);
HardwareInputPin repeater1InvertOutPin(8, true, true);
HardwareInputPin repeater2InvertOutPin(9, true, true);

BaudotRepeater<128> repeater1(repeater1InPin, 45.45f, repeater1OutPin, 50.f);
BaudotRepeater<128> repeater2(repeater2InPin, 50.f, repeater2OutPin, 45.45f);

void setup() 
{
    Serial.begin(115200);
    delay(500);

    repeater1InPin.Inverted(repeater1InvertInPin.read());
    repeater1OutPin.Inverted(repeater1InvertOutPin.read());
    repeater2InPin.Inverted(repeater2InvertInPin.read());
    repeater2OutPin.Inverted(repeater2InvertOutPin.read());
}

int32_t lastMsg = millis();

void loop() 
{
    repeater1.loop();
    repeater2.loop();
}

#endif