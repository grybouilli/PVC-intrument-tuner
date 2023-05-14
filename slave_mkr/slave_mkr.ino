#include <Wire.h>
#include "Instrument.hh"
#include "NoteController.hh"

NoteController si   { 8, 9, 10, 11, 7, 80.f };
NoteController do_  { 2, 3, 5,  6,  4, 85.f };

Instrument higherController {};
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
    Wire.begin(SLAVES::Higher);
    Wire.onReceive(checkWireInput());

    si.setNoteDepth(NoteController::NotePosition::FLAT, 46.);
    si.setNoteDepth(NoteController::NotePosition::NATURAL, 43.);
    si.setNoteDepth(NoteController::NotePosition::SHARP, 41.);

    do_.setNoteDepth(NoteController::NotePosition::FLAT, 43.);
    do_.setNoteDepth(NoteController::NotePosition::NATURAL, 41.);
    do_.setNoteDepth(NoteController::NotePosition::SHARP, 38.);
    
    si.setZero();
    do_.setZero();
    
    higherController.addNote(Instrument::Tuning::SI,     &si);
    higherController.addNote(Instrument::Tuning::DO2,    &do_);

}

void loop()
{
    if(!higherController.isTuned())
    {
        higherController.run();
    }
    else if(noteAlteration != -1)
    {
        higherController.tuneTo(numberAlteration, (NoteController::NotePosition)noteAlteration);
        noteAlteration = -1;
        numberAlteration = -1;
    }
}

void checkWireInput(int bytes)
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