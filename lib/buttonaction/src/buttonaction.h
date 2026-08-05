#ifndef _BUTTONACTION_H_
#define _BUTTONACTION_H_

typedef void (*CallbackEvent)(int);

typedef struct Button Button;
struct Button
{
    Button *previousButton;
    CallbackEvent callback;
    int buttonPin;
    bool buttonActionMade;
};

void AddButton(int ledPin, CallbackEvent callback);
void ButtonTick(unsigned long deltaMillis);
void FreeMemory();
#endif