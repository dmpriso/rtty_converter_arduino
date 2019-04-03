#ifndef UNIT_TEST

#include <Arduino.h>

#include "baudot_converter.h"
#include "blink.h"

HardwareInputPin converter1InPin(2);
HardwareInputPin converter2InPin(3);
HardwareOutputPin converter1OutPin(4);
HardwareOutputPin converter2OutPin(5);

HardwareInputPin converter1InvertInPin(6, true, true);
HardwareInputPin converter2InvertInPin(7, true, true);
HardwareInputPin converter1InvertOutPin(8, true, true);
HardwareInputPin converter2InvertOutPin(9, true, true);

HardwareInputPin autocompleteCrlfPin(10, true, true);

HardwareOutputPin ledPin(13);

BaudotConverter<128> converter1(converter1InPin, 45.45f, converter1OutPin, 50.f);
BaudotConverter<128> converter2(converter2InPin, 50.f, converter2OutPin, 45.45f);

Blink blink(ledPin);

void setup() 
{
    Serial.begin(115200);

    converter1InPin.Inverted(converter1InvertInPin.read());
    converter1OutPin.Inverted(converter1InvertOutPin.read());
    converter2InPin.Inverted(converter2InvertInPin.read());
    converter2OutPin.Inverted(converter2InvertOutPin.read());

    converter1.AutocompleteCRLF(autocompleteCrlfPin.read());
    converter2.AutocompleteCRLF(autocompleteCrlfPin.read());
}

int32_t lastMsg = millis();

void setBlinking()
{
    bool r1 = converter1.isActive();
    bool r2 = converter2.isActive();
    if (r1 && r2)
        blink.setInterval(200);
    else if (r2)
        blink.setInterval(500);
    else if (r1)
        blink.setInterval(1000);
    else
        blink.stop();
}


void loop() 
{
    setBlinking();

    converter1.loop();
    converter2.loop();
    blink.loop();
}

#endif
