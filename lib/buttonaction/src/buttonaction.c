#include <Arduino.h>
#include "buttonaction.h"

static Button *_lastButton;

void AddButton(int buttonPin, CallbackEvent callback)
{
    Button *newButton = malloc(sizeof(*newButton));
    if (newButton == NULL)
        return;
    newButton->buttonPin = buttonPin;
    newButton->buttonActionMade = false;
    newButton->previousButton = _lastButton;
    newButton->callback = callback;
    _lastButton = newButton;
    pinMode(buttonPin, INPUT);
}

void ButtonTick(unsigned long deltaMillis)
{
    (void)deltaMillis; // no debouncing yet, the button is evaluated on every tick
    for (Button *button = _lastButton; button != NULL; button = button->previousButton)
    {
        int buttonState = digitalRead(button->buttonPin);
        if (buttonState == LOW)
        {
            button->buttonActionMade = false;
            continue;
        }

        if (button->buttonActionMade)
            continue;

        button->buttonActionMade = true;
        button->callback(button->buttonPin);
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
