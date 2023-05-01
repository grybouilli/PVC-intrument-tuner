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

    static Chord getMinorFrom(Chord);

    void addNote(Tuning chord, NoteController* controller);

    void run();

    void tuneTo(int, NoteController::NotePosition);
private:
    std::array<NoteController*, (int)Tuning::TOTAL> _notes;

};
