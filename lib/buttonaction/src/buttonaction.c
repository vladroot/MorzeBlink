#include <Arduino.h>
#include "buttonaction.h"

int _buttonPin;
bool _buttonActionMade;

CallbackEvent _callback;

void InitButton(int buttonPin, CallbackEvent callback)
{
    _buttonPin = buttonPin;
    _buttonActionMade = false;
    _callback = callback;
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
    _callback(_buttonPin);
}