#pragma once

#include "NoteController.hh"
#include "array.hh"

class Instrument
{
public:
    // corresponds to major Tuning
    enum class Chord
    {
        SI,
        MI,
        LA,
        RE,
        SOL,
        DO,
        FA,
        TOTAL
    };

    enum class Tuning
    {
        DO,
        RE, 
        MI,
        FA,
        SOL,
        LA,
        SI,
        DO2,
        TOTAL
    };

    Instrument();

    void addNote(Tuning chord, NoteController* controller);

    void run();

    void tuneTo(int, NoteController::NotePosition);

    bool isTuned() const;
private:

    Tuning chordToTune(Chord);
    
    std::array<NoteController*, (int)Tuning::TOTAL> _notes;

};
