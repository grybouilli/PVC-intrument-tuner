#include <Wire.h>
#include "Instrument.hh"
#include "NoteController.hh"

NoteController mi   { 25, 2,  3,  4,   26, 75.f };
NoteController fa   { 27, 5,  6,  7,   28, 70.f };
NoteController sol  { 29, 8,  9,  10,  30, 65.f };
NoteController la   { 31, 11, 12, 13,  32, 60.f };

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
    Serial.begin(115200);
    Wire.begin();

    mi.setNoteDepth(NoteController::NotePosition::FLAT, 68.);
    mi.setNoteDepth(NoteController::NotePosition::NATURAL, 64.);
    mi.setNoteDepth(NoteController::NotePosition::SHARP, 61.);

    fa.setNoteDepth(NoteController::NotePosition::FLAT, 64.);
    fa.setNoteDepth(NoteController::NotePosition::NATURAL, 61.);
    fa.setNoteDepth(NoteController::NotePosition::SHARP, 57.);

    sol.setNoteDepth(NoteController::NotePosition::FLAT, 57.);
    sol.setNoteDepth(NoteController::NotePosition::NATURAL, 54.);
    sol.setNoteDepth(NoteController::NotePosition::SHARP, 51.);

    la.setNoteDepth(NoteController::NotePosition::FLAT, 51.);
    la.setNoteDepth(NoteController::NotePosition::NATURAL, 48.);
    la.setNoteDepth(NoteController::NotePosition::SHARP, 46.);

    mi.setZero();
    fa.setZero();
    sol.setZero();
    la.setZero();
    middleController.addNote(Instrument::Tuning::MI,    &mi);
    middleController.addNote(Instrument::Tuning::FA,    &fa);
    middleController.addNote(Instrument::Tuning::SOL,   &sol);
    middleController.addNote(Instrument::Tuning::LA,    &la);

}

void loop()
{

    while (Serial.available() == 0) {
        if(!middleController.isTuned())
        {
            middleController.run();
        }
        else if(noteAlteration != -1)
        {
            middleController.tuneTo(numberAlteration, (NoteController::NotePosition)noteAlteration);
            noteAlteration = -1;
            numberAlteration = -1;
        }
    }
    checkSerialInput();   
}

void sendToSlave(SLAVES slaveID, char message[])
{
    Wire.beginTransmission(slaveID);                                                                              
    Wire.write(message);                                                    
    Wire.endTransmission();     
}

void checkSerialInput()
{
    String inputString = Serial.readString();
    char inputArray [inputString.length()+1];
    inputString.toCharArray(inputArray, inputString.length()+1);

    sendToSlave(SLAVES::Lower, inputArray);
    sendToSlave(SLAVES::Higher, inputArray);
    
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