#ifndef _BUTTONACTION_H_
#define _BUTTONACTION_H_

typedef void (*CallbackEvent)(int);

void InitButton(int ledPin, CallbackEvent callback);
void ButtonTick(unsigned long deltaMillis);
#endif