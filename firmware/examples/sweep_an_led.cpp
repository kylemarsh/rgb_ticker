// This sketch uses the Ticker class to sweep an LED connected to pin 9
// (Arduino) or D0 (Particle Core) up from off to full brightness and back
// down.

#include "ticker/ticker.h"

#if defined(ARDUINO)
int ledpin = 9;
#elif defined(SPARK)
int ledpin = D0;
#endif

void sweep(Ticker *t, unsigned long tick);

Ticker MyTicker(&sweep, 1, 0, 0);

void setup()
{
  pinMode(ledpin, OUTPUT);

  // Assuming 8-bit PWM as available on the Arduino and Particle boards
  MyTicker.targets[0] = {red: 255, green: 0, blue: 0};
}

void loop()
{
	// Just use millis() here for 1-millisecond ticks. If you want to do
	// something fancier go right ahead!
	MyTicker.Tick(millis());

	// Set the brightness of the LED to the value of the Ticker's "red" channel
	analogWrite(ledpin, MyTicker.current.red);
}

// Sweeps the brightness of an LED from 0 (off) to 255 (full) and back
// repeatedly. Uses a target TickerRgb value to determine if we're sweeping up
// or down.
void sweep(Ticker *t, unsigned long tick)
{
#if defined(ARDUINO)
	// I found that the loop in this firmware iterates *much* faster on my
	// Arduino Duemilanove than on the Particle core. I assume this has to do
	// with the Particle's wifi / cloud connection routines, but whatever the
	// cause only ticking on one cycle in 100 on Arduino makes this example
	// visible.
	if (tick % 100 != 0) {
		return;
	}
#endif
	// We're only using one (red) right now, but the targets actually store
	// three different values: red, green, and blue!
	TickerRgb target_color = t->targets[0];
	int16_t target_value = target_color.red;
	int16_t current_value = t->current.red;

	if (current_value == target_value) {
		// We've reached our target! Time to turn around
		t->targets[0].red = 255 - target_value;
	} else if (current_value < target_value) {
		// We're climbing towards our target...add 1!
		t->current.red = t->current.red + 1;
	} else {
		// We're descending towards our target...subtract 1!
		t->current.red = t->current.red - 1;
	}
}
