/**
 * @file NoteController.hpp
 * @author grybouilli (grybouilli@outlook.fr)
 * @brief 
 * @version 0.1
 * @date 2023-04-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <AccelStepper.h>
#include "array.hh"

// Define the AccelStepper interface type; 4 wire motor in half step mode:
#define MotorInterfaceType 8
#define StepsPerRevolution 4096

#define SPUR_RADIUS 15.f // mm

class NoteController
{
public:
    enum class MotorDirection
    {
        CLOCKWISE = 1,
        ANTICLOCKWISE = -1
    };

    enum class NotePosition
    {
        FLAT,
        NATURAL,
        SHARP,
        ZERO
    };


    explicit NoteController(int,int,int,int,int, float);

    void    run();

    void    setNoteDepth(NotePosition, float);
    void    setNote(NotePosition);
    void    setZero();
    bool    reachedTarget() const;

    NotePosition getCurrentNote() const;

private:
    void    runToZero();
    void    runToNote(NotePosition);

    long    noteToSteps(NotePosition);

private:
    int                                     _stopButton;
    int                                     _lastButtonState;

    std::array<float, (int)NotePosition::ZERO>   _notesDepth;
    float                                   _tubeLength;

    AccelStepper                            _motorInterface;
    MotorDirection                          _currentDirection;
    NotePosition                            _currentNote;

    bool                                    _targetReached;
};