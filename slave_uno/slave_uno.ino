#include <Wire.h>
#include "Instrument.hh"
#include "NoteController.hh"

NoteController do_  { 2, 3, 5,  6,  4, 85.f };
NoteController re   { 8, 9, 10, 11, 7, 80.f };

Instrument lowerController {};
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
    Wire.begin(SLAVES::Lower);
    Wire.onReceive(checkWireInput());

    do_.setNoteDepth(NoteController::NotePosition::FLAT, 81.);
    do_.setNoteDepth(NoteController::NotePosition::NATURAL, 81.);
    do_.setNoteDepth(NoteController::NotePosition::SHARP, 77.);

    re.setNoteDepth(NoteController::NotePosition::FLAT, 77.);
    re.setNoteDepth(NoteController::NotePosition::NATURAL, 72.);
    re.setNoteDepth(NoteController::NotePosition::SHARP, 68.);

    do_.setZero();
    re.setZero();
    
    lowerController.addNote(Instrument::Tuning::DO,    &do_);
    lowerController.addNote(Instrument::Tuning::RE,    &re);

}

void loop()
{
    if(!lowerController.isTuned())
    {
        lowerController.run();
    }
    else if(noteAlteration != -1)
    {
        lowerController.tuneTo(numberAlteration, (NoteController::NotePosition)noteAlteration);
        noteAlteration = -1;
        numberAlteration = -1;
    }
}

void checkWireInput()
{
    char inputArray [256];
    
    int c = 0;
    while(Wire.available())
    {
        inputArray[c++] = Wire.read();
    }

    char * noteAlt = 0;
    char * numbAlt = 0;

    noteAlt = strtok(inputArray, ' ');
    numbAlt = strtok(NULL, ' ');

    if(!numbAlt)
    {
        noteAlteration = -1;
        numberAlteration = -1;
    } else
    {
        noteAlteration = atoi(noteAlt);
        numberAlteration = atoi(numbAlt);
    }
}