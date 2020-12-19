#include <avr/io.h>
#include <avr/interrupt.h>
#include <Arduino.h>
#include "usb_debug_only.h"
#include "print.h"

// Clock macros provided by PJRC
#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz  0x00
// #define CPU_8MHz   0x01
// #define CPU_4MHz   0x02
// #define CPU_2MHz   0x03
// #define CPU_1MHz   0x04
// #define CPU_500kHz 0x05
// #define CPU_250kHz 0x06
// #define CPU_125kHz 0x07
// #define CPU_62kHz  0x08

#define RESET_INTF7 (EIFR &= ~(1<<7))
#define SET_IINT7 (EIMSK |= (1<<7))
#define ADDRESS ((PINF << 8) | PINC)
#define DATA (PIND)
#define RWB_HIGH (PINB & (1<<0))
#define CLOCK 19

// onClock
void onClock(void) {
	// Print each bit of the address bus
	for (int i=15; i>=0; i-=1) {
		uint8_t bit = (ADDRESS >> i) & 1;
		unsigned char bit_char = (bit) ? '1' : '0';
		pchar(bit_char);
	}
	print(" ");
	// Print each bit of the data bus
	for (int i=7; i>=0; i-=1) {
		uint8_t bit = (DATA >> i) & 1;
		unsigned char bit_char = (bit) ? '1' : '0';
		pchar(bit_char);
	}
	// Pin B0 is monitoring the 6502 RWB (Pin 34)
	unsigned char read_write = (RWB_HIGH) ? 'r' : 'w';
	print("  ");
	pchar(read_write);
	print(" ");
	phex16(ADDRESS);
	print(" ");
	phex(DATA);
	pchar('\n');
}

int main(void) {
	// Initialize the clock
	CPU_PRESCALE(CPU_16MHz);

	// Set address, data, and RWB pins to input
	DDRC = 0x00; // A0 - A7
	DDRF = 0x00; // A8 - A15
	DDRD = 0x00; // D0 - D8
	DDRB = 0x00; // RWB

	// Initialize USB debugging
	usb_init();

	// Enable 6502 clock interrupt
	attachInterrupt(digitalPinToInterrupt(CLOCK), onClock, RISING);

	while(1) {
	}
}
