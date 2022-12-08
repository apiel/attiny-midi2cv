// NOTE Need to comment out usbFunctionWriteOut in DigiMIDI.h
#define DIGIMIDI_WRITEOUT 1

#include <DigiMIDI.h>

DigiMIDIDevice midi;
void setup()
{
    pinMode(0, OUTPUT); // Gate is output
    pinMode(1, OUTPUT); // Pitch is output
    pinMode(2, OUTPUT); // Clock
    // Setup Timer1 to do PWM DAC for Pitch
    TCCR1 = _BV(PWM1A) | _BV(COM1A1) | _BV(CS10);
    GTCCR = 0;
    OCR1C = 239;          // Set CV PWM range to 240
    OCR1A = 0;            // Set initial Pitch to C2
    digitalWrite(5, LOW); // Set initial Gate to LOW;
    //*/
}
void loop()
{
    midi.update(); // Check if any MIDI data is received
}

uint8_t midiClockState = LOW;
void usbFunctionWriteOut(uchar *data, uchar len)
{
    uint8_t note = data[2]; // Get note for key on/off
    if (note < 36)
        note = 36;    // If note is lower than C2 set it to C2
    note = note - 36; // Subtract 36 to get into CV range
    if (note > 60)
        note = 60; // If note is higher than C7 set it to C7
    if (data[1] == 0x90)
    {                          // If note on
        digitalWrite(0, HIGH); // Set Gate HIGH
        OCR1A = note << 2;     // Multiply note by 4 to set the voltage (1v/octave)
    }
    if (data[1] == 0x80)
    {                         // If note off
        digitalWrite(0, LOW); // Set Gate LOW
        OCR1A = note << 2;    // Multiply note by 4 to set the voltage (1v/octave)
    }
    if (data[1] == 0xF8)
    {
        midiClockState = midiClockState == LOW ? HIGH : LOW;
        digitalWrite(2, midiClockState);
    }
}
