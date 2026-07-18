#include <Arduino.h>
#include "morzeblink.h"

// 200 - dot, dash = 3 * dot
// pause between letters = dot * 3
// pause between words = dot * 7

#define DOT 200    // dot, pause between symbols in one letter
#define DASH 600   // 3 dots, pause between letters
#define PAUSE 1400 // 7 dots, pause between words
int _symbolId;
int _letterId;
unsigned long _counter;
int _ledPin;
int _ledState;
unsigned long *_word;

void MorzeBlinkStart(int ledPin, unsigned long *word)
{
    _ledState = LOW;
    _ledPin = ledPin;
    _word = word;
    pinMode(_ledPin, OUTPUT);
}

void MorzeBlinkTick(unsigned long deltaMillis)
{
    if (deltaMillis >= _counter)
        _counter = 0;
    else
        _counter -= deltaMillis;

    if (_counter != 0)
        return;

    if (_ledState == LOW)
    {
        _counter = *(_word + (_letterId * MB_LETTER_LENGTH + _symbolId));
        _ledState = HIGH;
    }
    else
    {
        _counter = DOT;
        _ledState = LOW;

        _symbolId++;
        if (_symbolId == MB_LETTER_LENGTH || *(_word + (_letterId * MB_LETTER_LENGTH + _symbolId)) == 0)
        {
            _symbolId = 0;
            _letterId++;
            _counter = DASH;

            if (_letterId == MB_WORD_LENGTH)
            {
                _letterId = 0;
                _counter = PAUSE;
            }
        }
    }

    digitalWrite(_ledPin, _ledState);
}