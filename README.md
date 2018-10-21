# RTTY baud rate converter for Arduino

## Hardware
Tested with Arduino Nano (AtMega 328)

## Building
Use VS Code & PlatformIO. For executing unit tests, you will need PIO Pro. A 30 days trial version is available.

For building and deploying, the free community edition is sufficient.

## Converters

Converter 1: Converts 45.45 baud to 50 baud
Converter 2: Converts 50 baud to 45.45 baud

## Default PIN assignments

### RTTY Pins
Input pins configured as pull-down.

**D2**: Converter 1 45.45 baud input<br>
**D3**: Converter 2 50 baud input<br>
**D4**: Converter 1 50 baud output (converted from 45.45 baud)<br>
**D5**: Converter 2 45.45 baud output (converted from 50 baud)<br>

### Configuration pins
Configured as pull-up. Set to ground to activate inverting

**D6**: Invert 45.45 baud input (D2)<br>
**D7**: Invert 50 baud input (D3)<br>
**D8**: Invert 50 baud output (D4)<br>
**D9**: Invert 45.45 baud output (D5)<br>

## LED Indicator
The Arduino LED labeled **L** (also connected to D13) indicates the state of the converters.

**Off**: No converter active
**Slow blinking (~1Hz)**: Converter 1 (45.45->50) active
**Medium blinking (~2Hz)**: Converter 2 (50->45.45) active
**Fast blinking (~5Hz)**: Both repeaters active
