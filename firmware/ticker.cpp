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
  if ((targets = (TickerRgb *)malloc(num_targets * 6))) {
    memset(targets, 0, num_targets * 6);
  }
}

Ticker::~Ticker()
{
  if (targets) free(targets);
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
