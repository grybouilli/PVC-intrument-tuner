#include <Wire.h>
#include "Instrument.hh"
#include "NoteController.hh"

NoteController re   { 8, 9,  10, 11,   7, 90.f };

Instrument middleController {};
int noteAlteration = -1;
int numberAlteration = -1;

enum SLAVES
{
    Lower = 0,
    Higher = 1,
    Total
};

void setup()
{
    Serial.begin(9600);

    re.setNoteDepth(NoteController::NotePosition::FLAT, 67.);
    re.setNoteDepth(NoteController::NotePosition::NATURAL, 62.);
    re.setNoteDepth(NoteController::NotePosition::SHARP, 58.);

    re.setZero();
    middleController.addNote(Instrument::Tuning::RE,    &re);

}

void loop()
{

    if(!middleController.isTuned())
    {
        middleController.run();
    }
    else if(numberAlteration != -1)
    {
        middleController.tuneTo(numberAlteration, (NoteController::NotePosition)noteAlteration);
        noteAlteration = -1;
        numberAlteration = -1;
    }
    if(Serial.available())
    {
        // checkSerialInput();   
        noteAlteration = Serial.parseInt();
        Serial.print("Alteration: ");
        Serial.print(noteAlteration);
        Serial.print("\n");
        while(!Serial.available())
        {

        }
        numberAlteration = Serial.parseInt();
        Serial.print("Amount: ");
        Serial.print(numberAlteration);
        Serial.print("\n");

    }

}
