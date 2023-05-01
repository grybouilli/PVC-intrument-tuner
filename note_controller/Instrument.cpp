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
        if(_notes[i] != nullptr)
        {
            _notes[i]->setNote(alterationType);
        }
        i = alterationType == NoteController::NotePosition::FLAT ? i+1 : i - 1;
        
        condition = alterationType == NoteController::NotePosition::FLAT ? i < altNb : i >= ((int)Chord::TOTAL - altNb);
    }

}