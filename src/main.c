#include <Arduino.h>
#include "morzeblink.h"
#include "buttonaction.h"
#include "optoinput.h"

#define LED_PIN (2)

static unsigned long _currentMillis;

static const unsigned long ASS_WORD[MB_WORD_LENGTH][MB_LETTER_LENGTH] = {{200, 600}, {200, 200, 200}, {200, 200, 200}};                // ASS
static const unsigned long SOS_WORD[MB_WORD_LENGTH][MB_LETTER_LENGTH] = {{200, 200, 200}, {600, 600, 600}, {200, 200, 200}};           // SOS
static const unsigned long LOL_WORD[MB_WORD_LENGTH][MB_LETTER_LENGTH] = {{200, 600, 200, 200}, {600, 600, 600}, {200, 600, 200, 200}}; // LOL

static const int _buttonPin = 3;

// need to refactor it so the list of words are updated automatically
// just to  test github availability
static int _wordId;

void CodeChange();

void setup()
{
    FreeMemory();
    _currentMillis = millis();
    OptoInputInit(LED_PIN);
    CodeChange();
    AddButton(_buttonPin, &CodeChange);
}

void loop()
{
    unsigned long newMillis = millis();
    // make sure we can work indefinitely
    unsigned long deltaMillis = newMillis > _currentMillis ? newMillis - _currentMillis : newMillis;
    _currentMillis = newMillis;
    OptoInputTick(deltaMillis);
    MorzeBlinkTick(deltaMillis);
    ButtonTick(deltaMillis);
}

void CodeChange()
{
    const unsigned long *word;
    switch (_wordId)
    {
    case 1:
        word = ASS_WORD[0];
        break;
    case 2:
        word = LOL_WORD[0];
        break;
    default:
        word = SOS_WORD[0];
        break;
    }

    _wordId++;
    if (_wordId == 3)
        _wordId = 0;

    MorzeBlinkStart(LED_BUILTIN, word);
}