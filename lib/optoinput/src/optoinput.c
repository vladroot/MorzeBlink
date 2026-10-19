#include <Arduino.h>
#include "optoinput.h"

#define PAUSE (5000)

static int _optoLedPin;

static unsigned long _counter;

void OptoInputInit(int ledPin)
{
    _optoLedPin = ledPin;
    _counter = 0;
    pinMode(ledPin, OUTPUT);
}

void OptoInputTick(unsigned long deltaMillis)
{
    if (deltaMillis < _counter)
        _counter -= deltaMillis;
    else
        _counter = 0;

    if (_counter != 0)
        return;

    _counter = PAUSE;

    int sensorValue = analogRead(A0);
    digitalWrite(_optoLedPin, sensorValue < 600 ? HIGH : LOW);
}