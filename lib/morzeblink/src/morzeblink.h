#ifndef _MORZEBLINK_H_
#define _MORZEBLINK_H_

#define MB_LETTER_LENGTH 4
#define MB_WORD_LENGTH 3

void MorzeBlinkStart(int ledPin, unsigned long *word);
void MorzeBlinkTick(unsigned long deltaMillis);
#endif