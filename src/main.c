#include <Arduino.h>
#include "morzeblink.h"

unsigned long currentMillis;

const unsigned long ASS_WORD[3][4] = {{200, 600}, {200, 200, 200}, {200, 200, 200}};      // ASS
const unsigned long SOS_WORD[3][4] = {{200, 200, 200}, {600, 600, 600}, {200, 200, 200}}; // SOS

void setup()
{
    currentMillis = millis();
    unsigned long *word = &SOS_WORD;
    MorzeBlinkStart(LED_BUILTIN, word);
}

void loop()
{
    unsigned long newMillis = millis();
    unsigned long deltaMillis = newMillis - currentMillis;
    currentMillis = newMillis;
    MorzeBlinkTick(deltaMillis);
}