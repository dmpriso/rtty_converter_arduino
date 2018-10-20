#include <Arduino.h>

#include "baudot_repeater.h"

HardwareInputPin repeater1InPin(2);
HardwareInputPin repeater2InPin(3);
HardwareOutputPin repeater1OutPin(4);
HardwareOutputPin repeater2OutPin(5);

HardwareInputPin repeater1ReverseInPin(6, true, true);
HardwareInputPin repeater1ReverseOutPin(7, true, true);
HardwareInputPin repeater2ReverseInPin(8, true, true);
HardwareInputPin repeater2ReverseOutPin(9, true, true);

BaudotRepeater<128> repeater1(repeater1InPin, 45.45f, repeater1OutPin, 50.f);
BaudotRepeater<128> repeater2(repeater2InPin, 50.f, repeater2OutPin, 45.45f);

void setup() 
{
    Serial.begin(115200);
    delay(500);

    repeater1InPin.Reverse(repeater1ReverseInPin.read());
    repeater1OutPin.Reverse(repeater1ReverseOutPin.read());
    repeater2InPin.Reverse(repeater2ReverseInPin.read());
    repeater2OutPin.Reverse(repeater2ReverseOutPin.read());
}

int32_t lastMsg = millis();

void loop() 
{
    repeater1.loop();
    repeater2.loop();
}
