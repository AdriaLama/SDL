#pragma once
#include "TimeManager.h"

enum class GameStates
{
    NONE,
    GAMEPLAY,      
    PAUSED,        
    FINISH_STAGE, 
    DEATH          
};

class GameState
{
protected:
    GameStates _nextState;

public:
    GameState() : _nextState(GameStates::NONE) {}
    virtual ~GameState() = default;

    virtual void Start() = 0;
    virtual void Update(float elapsedTime) = 0;
    virtual void Render() const = 0;
    virtual void End() = 0;

    GameStates GetNextState() const { return _nextState; }
};