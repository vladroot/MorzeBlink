#ifndef _BUTTONACTION_H_
#define _BUTTONACTION_H_

void InitButton(int ledPin, void (*EventAction)(int));
void ButtonTick(unsigned long deltaMillis);
#endif