#include "NoteController.hpp"
#include <cmath>

/**
 * @brief NoteController constructor
 * 
 * Initialize the controller with default target to find zero position.
 * 
 *
 * @param mpin1         IN1 on the ULN2003 driver
 * @param mpin2         IN2 on the ULN2003 driver 
 * @param mpin3         IN3 on the ULN2003 driver 
 * @param mpin4         IN4 on the ULN2003 driver 
 * @param bpin          Stop Button pin
 * @param tubeLength    PVC tube length below sound hole
 * */

NoteController::NoteController(int mpin1, int mpin2, int mpin3, int mpin4, int bpin, float tubeLength)
: _stopButton { bpin }
, _lastButtonState { LOW }
, _notesDepth {-1, -1, -1}
, _tubeLength { tubeLength } 
, _motorInterface { MotorInterfaceType, mpin1, mpin3, mpin2, mpin4 }
, _currentDirection { -1 }
, _currentNote { ZERO }
, _targetReached { false }
{
    // Set the maximum steps per second:
    _motorInterface.setMaxSpeed(1000.0);
    _motorInterface.setAcceleration(50.0);
    _motorInterface.setCurrentPosition(0);
    // initialize the pushbutton pin as an input:
    pinMode(bpin, INPUT_PULLUP);
    _lastButtonState = digitalRead(_stopButton);
}


/**
 * @brief Run motor until target is reached.
 * 
 */
void NoteController::run()
{
    if(!_targetReached)
    {
        runToNote(_currentNote);
        _motorInterface.run();
    }
}

/**
 * @brief Assign tube depth associated with note.
 * 
 *
 * @param note  The associated note.
 * @param depth The tube depth (below sound hole) producing the note.
 */
void NoteController::setNoteDepth(NotePosition note, float depth)
{
    if(pos == NotePosition::ZERO)
    {
        throw std::logic_error("NoteController::setNoteDepth : cannot set a depth for note ZERO.");
    }
    _notesDepth[(int)note] = depth;
}

/**
 * @brief Set note target.
 * 
 * The targeted position can only be put as target once the note deth has been set-up. Make sure to make a call to setNoteDepth at least once prior to calling setNote. If you want to run to zero position, call setZero.
 *
 * @param pos The note to target.
 */
void NoteController::setNote(NotePosition pos)
{
    _currentDirection = MotorDirection::CLOCKWISE;
    if(pos == NotePosition::ZERO)
    {
        throw std::logic_error("NoteController::setNote : pos ZERO shouldn't be given. Use setZero() instead.");
        return;
    }
    if(_notesDepth[(int)pos] < 0)
    {
        throw std::logic_error("NoteController::setNote : depth of note " + std::to_string((int)pos) + " hasn't been set yet.");   
        return;
    }

    _targetPos = pos;
    _targetReached = false;

    _motorInterface.move(noteToSteps(pos));
}

/**
 * @brief Find the zero position.
 * 
 * Set zero as the target position. Zero is the longest possible tube depth. It is reached once the rack has hit the stop button.
 */
void NoteController::setZero()
{
    _currentDirection = MotorDirection::ANTICLOCKWISE;
    _targetPos = NotePosition::ZERO;
    _targetReached = false;

    _motorInterface.setCurrentPosition(0);
    _motorInterface.moveTo((int)_currentDirection * StepsPerRevolution);
}

/**
 * @brief Has the target been reached?
 * 
 *
 * @return True if the target has been reached : the motor should thus not be running anymore (i.e call to run() has no effect) ; returns false otherwise :the motor should thus be running until target is reached.
 */
bool NoteController::reachedTarget() const
{
    return _targetReached;
}

/**
 * @brief Keeps the motor running until zero position is found.
 * 
 * Check that the motor keeps running until the zero position is found. It also checks whether the stop button was hit in which case it notifies the Controller that target has been reached.
 */
void NoteController::runToZero()
{
    // if run is stopping and zero hasn't been reached yet
    if(_motorInterface.distanceToGo() == 0)
    {
        _motorInterface.setCurrentPosition(0);
        _motorInterface.moveTo((int)_currentDirection * StepsPerRevolution);
    }

    // Check if button was hit
    int currentStopButtonState = digitalRead(stopButtonPin); // read new state
    if (_lastButtonState == HIGH && currentStopButtonState == LOW) {
        //Stop motor 
        _motorInterface.setCurrentPosition(0);
        _targetReached = true;
    } 
    _lastButtonState    = currentStopButtonState;      // save the last state
}

/**
 * @brief Control motor as to reach target note pos.
 * 
 *
 * @param note The targeted note
 */
void NoteController::runToNote(NotePosition note)
{
    switch (note)
    {
    case ZERO:
        runToZero();
        break;
    
    default:
        if(_motorInterface.distanceToGo()==0)
        {
            _targetReached = true;
        }
        break;
    }
}

/**
 * @brief Converts distance to go into steps to run.
 * 
 * @param note The note to reach.
 * @return The number of steps to run from current position to reach note.
 */
long NoteController::noteToSteps(NotePosition note)
{

    // StepsPerRevolution -> 2 * M_PI * SPUR_RADIUS
    float toTravel{};
    if(_currentNote == NotePosition::ZERO)
    {
        toTravel = _tubeLength - _notesDepth[note];
    } else
    {
        toTravel = _notesDepth[_currentNote] - _notesDepth[note];
    }

    float angle = toTravel / (2 * M_PI * _tubeLength);
    long steps = std::round(angle * StepsPerRevolution / (2*M_PI));

    return steps;
}
