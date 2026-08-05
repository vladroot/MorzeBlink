#include <Arduino.h>
#include "buttonaction.h"

CallbackEvent _callback;

Button *_lastButton;

void AddButton(int buttonPin, CallbackEvent callback)
{
    Button *newButton = malloc(sizeof(*newButton));
    newButton->buttonPin = buttonPin;
    newButton->buttonActionMade = false;
    newButton->previousButton = _lastButton;
    newButton->callback = callback;
    _lastButton = newButton;
    pinMode(buttonPin, INPUT);
}

void ButtonTick(unsigned long deltaMillis)
{
    Button *button = _lastButton;
    while (button != NULL)
    {
        int buttonState = digitalRead(button->buttonPin);
        if (buttonState == LOW)
        {
            button->buttonActionMade = false;
            return;
        }

        if (button->buttonActionMade)
            return;

        button->buttonActionMade = true;
        button->callback(button->buttonPin);

        button = button->previousButton;
    }
}

void FreeMemory()
{
    while (_lastButton != NULL)
    {
        Button *button = _lastButton;
        _lastButton = _lastButton->previousButton;
        free(button);
    }
}
