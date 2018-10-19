#include <Arduino.h>

#include "baudot_repeater.h"

BaudotRepeater<64> repeater1(2, 45.45f, 3, 50.f);
BaudotRepeater<64> repeater2(4, 50.f, 5, 45.45f);

void setup() 
{
}

void loop() 
{
    repeater1.loop();
    repeater2.loop();
}