# RTTY baud rate converter for arduino instead of raspberry

## Converters:

Converter 1: Converts 45.45 baud to 50 baud
Converter 2: Converts 50 baud to 45.45 baud

## Default PIN assignments

### RTTY Pins
Input pins configured as pull-down.

**D2**: Converter 1 45.45 baud input
**D3**: Converter 2 50 baud input
**D4**: Converter 1 50 baud output (converted from 45.45 baud)
**D5**: Converter 2 45.45 baud output (converted from 50 baud)

### Configuration pins
Configured as pull-up. Set to ground to activate inverting

**D6**: Invert 45.45 baud input (D2)
**D7**: Invert 50 baud input (D3)
**D8**: Invert 50 baud output (D4)
**D9**: Invert 45.45 baud output (D5)
