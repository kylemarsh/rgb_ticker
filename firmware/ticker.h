/*
 *  Particle Core / Arduino library for controlling LED pixels.
 *  Created January 2016
 *  by Kyle Marsh
 *
 *  Defines a type named TickerRgb to facilitate passing around RGB color
 *  values, and a class named Ticker to encapsulate logic for changing a
 *  pixel's color over time. Ticker is basically just a container for a "tick
 *  function" which you pass in on construction and which does the heavy
 *  lifting.
 */

#ifndef Ticker_h
#define Ticker_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#elif defined(SPARK)
#include "application.h"
#endif

typedef struct
{
  int16_t red;
  int16_t green;
  int16_t blue;
} TickerRgb;

class Ticker
{
  public:
    Ticker(void (*tick_func)(Ticker *t, unsigned long tick), int num_targets, int speed_adjust, int offset);
    Ticker(const Ticker& other);
    ~Ticker();
	Ticker &operator=(const Ticker &other);

    int
      num_targets,
      speed_adjust,
      offset;
    TickerRgb current;
    TickerRgb *targets;

    void Tick(unsigned long tick);

  private:
    void (*tick_func)(Ticker *t, unsigned long tick);
};

#endif // Ticker_h
