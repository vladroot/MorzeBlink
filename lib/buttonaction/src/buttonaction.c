#include <Arduino.h>
#include "buttonaction.h"

int _buttonPin;
bool _buttonActionMade;

void (*_eventAction)(int);

void InitButton(int buttonPin, void (*eventAction)(int))
{
    _buttonPin = buttonPin;
    _buttonActionMade = false;
    _eventAction = eventAction;
    pinMode(buttonPin, INPUT);
}

void ButtonTick(unsigned long deltaMillis)
{
    int buttonState = digitalRead(_buttonPin);
    if (buttonState == LOW)
    {
        _buttonActionMade = false;
        return;
    }

    if (_buttonActionMade)
        return;

    _buttonActionMade = true;
    _eventAction(_buttonPin);
}