#include <Arduino.h>
#include "morzeblink.h"
#include "buttonaction.h"

unsigned long currentMillis;

const unsigned long ASS_WORD[MB_WORD_LENGTH][MB_LETTER_LENGTH] = {{200, 600}, {200, 200, 200}, {200, 200, 200}};                // ASS
const unsigned long SOS_WORD[MB_WORD_LENGTH][MB_LETTER_LENGTH] = {{200, 200, 200}, {600, 600, 600}, {200, 200, 200}};           // SOS
const unsigned long LOL_WORD[MB_WORD_LENGTH][MB_LETTER_LENGTH] = {{200, 600, 200, 200}, {600, 600, 600}, {200, 600, 200, 200}}; // LOL

const int _ledPin = 2;
const int _buttonPin = 3;

// need to refactor it so the list of words are updated automatically
int _wordId;

void buttonCallback();

void setup()
{
    currentMillis = millis();
    buttonCallback();
    InitButton(_buttonPin, &buttonCallback);
}

void loop()
{
    unsigned long newMillis = millis();
    unsigned long deltaMillis = newMillis - currentMillis;
    currentMillis = newMillis;
    MorzeBlinkTick(deltaMillis);
    ButtonTick(deltaMillis);
}

void buttonCallback()
{
    unsigned long *word;
    switch (_wordId)
    {
    case 1:
        word = &ASS_WORD;
        break;
    case 2:
        word = &LOL_WORD;
        break;
    default:
        word = &SOS_WORD;
        break;
    }

    _wordId++;
    if (_wordId == 3)
        _wordId = 0;

    MorzeBlinkStart(_ledPin, word);
}