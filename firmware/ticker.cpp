#include "ticker.h"

/****************
 * Ticker Class *
 ****************/

/*
 * Constructor:
 * Ticker(tick_func, num_targets, speed_adjust, offset)
 *
 * Create a Ticker object whose behavior is defined by the tick function passed
 * in. Allocates an array of TickerRgbs on the heap for the target colors; the number
 * of targets required depends on tick_func, so be careful to match it to what
 * the tick function expects.
 *
 * INPUTS:
 *   tick_func: a pointer to a function that takes a Ticker object and a 16
 *     bit unsigned int. The function will be called on Ticker.Tick(tick)
 *     and "tick" is intended to be used as a counter for timing and for
 *     synchronization across Tickers.
 *   num_targets: the number of TickerRgbs the tick function expects to use
 *     as "target" colors
 *   speed_adjust: a value the tick function can use to adjust its speed
 *   offset: a value the tick function can use to adjust its speed or phase
 */
Ticker::Ticker(void (*tick_func)(Ticker *t, unsigned long tick), int num_targets, int speed_adjust, int offset) :
  num_targets(num_targets), speed_adjust(speed_adjust),
  offset(offset), targets(NULL), tick_func(tick_func)
{
	targets = new TickerRgb[num_targets];
}

Ticker::Ticker(const Ticker& other) :
  num_targets(other.num_targets), speed_adjust(other.speed_adjust),
  offset(other.offset), targets(NULL), tick_func(other.tick_func)
{
	targets = new TickerRgb[num_targets];
	for (int i = 0; i < other.num_targets; ++i) {
		targets[i] = other.targets[i];
	}
}

Ticker::~Ticker()
{
  delete [] targets;
}

Ticker& Ticker::operator=(const Ticker &other)
{
	if (this != &other) {
		TickerRgb *new_targets = new TickerRgb[other.num_targets];
		for (int i = 0; i < other.num_targets; ++i) {
			new_targets[i] = other.targets[i];
		}
		delete [] targets;

		targets = new_targets;
		num_targets = other.num_targets;
		speed_adjust = other.speed_adjust;
		current = other.current;
		tick_func = other.tick_func;
	}

	return *this;
}

/*
 * Ticker.Tick(tick)
 * Calls the tick function and passes a pointer to the Ticker object as well as
 * the "tick" counter.
 *
 * You'll most likely want to call Tick from your firmware's loop() function
 */
void Ticker::Tick(unsigned long tick)
{
  this->tick_func(this, tick);
}
