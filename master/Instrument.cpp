#include "Instrument.hh"

Instrument::Instrument()
{
    for(int i = 0; i < (int)Tuning::TOTAL; ++i)
    {
        _notes[i] = nullptr;
    }
}

void Instrument::addNote(Instrument::Tuning chord, NoteController* controller)
{
    Serial.print((int)chord);
    _notes[(int)chord] = controller; //try with std::move?
}

void Instrument::run()
{
    for(auto& note: _notes)
    {
        note->run();
    }
}

void Instrument::tuneTo(int altNb, NoteController::NotePosition alterationType)
{
    int i = alterationType == NoteController::NotePosition::FLAT ? 0 : (int)(Chord::FA);
    bool condition {true};
    while(condition)
    {
        if(_notes[(int)chordToTune((Chord)i)] != nullptr)
        {
            if((Chord)i == Chord::DO)
            {
                _notes[(int)Tuning::DO2]->setNote(alterationType);
            }
            Serial.print("Setting note to alteration ");
            Serial.print((int)alterationType);
            Serial.print("\nFor note : ");
            Serial.print((int)chordToTune((Chord)i));
            _notes[(int)chordToTune((Chord)i)]->setNote(alterationType);
        }
        i = alterationType == NoteController::NotePosition::FLAT ? i+1 : i - 1;
        
        condition = alterationType == NoteController::NotePosition::FLAT ? i < altNb : i >= ((int)Chord::TOTAL - altNb);
    }

}

bool Instrument::isTuned() const
{
    for(auto& note :_notes)
    {
        if(!note->reachedTarget())
            return false;
    }
    return true;
}

Instrument::Tuning Instrument::chordToTune(Chord c)
{
    switch (c)
    {
    case Chord::SI:
        return Tuning::SI;
        break;

    case Chord::MI:
        return Tuning::MI;
        break;

    case Chord::LA:
        return Tuning::LA;
        break;

    case Chord::RE:
        return Tuning::RE;
        break;

    case Chord::SOL:
        return Tuning::SOL;
        break;
    
    case Chord::DO:
        return Tuning::DO;
        break;

    case Chord::FA:
        return Tuning::FA;
        break;
    default:
        return Tuning::DO2;
        break;
    }
}