# Ben Eater 6502 8-bit Computer
This project contains the code I used to follow along [Ben Eater's 6502
8-bit computer videos](https://eater.net/6502). I am using a Teensy 2.0++
as the monitor.

## Monitor
The monitor reads the address and data buses and the RWB pin for every
clock pulse of the 6502 and reports it to the terminal using
[hid_listen](https://www.pjrc.com/teensy/hid_listen.html).

The output shows each address and data bus bit, whether the 6502 is
reading (r) or writing (w), followed by the address and data bus hex
values. For example:

```
/--- address bits
|                /--- data bits
|                |         /--- read/write
|                |         | /--- address hex
|                |         | |    /--- data hex
|                |         | |    |
1111111111001010 11101010  r FFCA EA
1111111111001010 11101010  r FFCA EA
1111111111001011 11101010  r FFCB EA
1111111111001011 11101010  r FFCB EA
1111111111001100 11101010  r FFCC EA
1111111111001100 11101010  r FFCC EA
1111111111001101 11101010  r FFCD EA
1111111111001101 11101010  r FFCD EA
```

### Hardware Setup
- W65C02S A0-A15 (pins 9-20, 22-25) are connected to Teensy PINC and PINF.
  The pin mapping is:
  - `A0`-`A7` to `C0`-`C7` respectively
  - `A8`-`A15` to `F0`-`F7` respectively
- W65C02S D7-D0 (pins 26-33) are connected to Teensy PIND. The pin mapping
  is:
  - `D0`-`D7` to `D0`-`D7` respectively
- W65C02S RWB (pin 34) is connected to Teensy B0
- W65C02S PHI2 (pin 37) is connected to Teensy E7

![Monitor setup](/static/monitor_setup.png)
