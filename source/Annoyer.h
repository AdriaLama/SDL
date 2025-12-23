#pragma once
#include "Enemy.h"
#include <cstdlib>
#include <ctime>
#include "GameManager.h"

class Annoyer : public Enemy
{
private:
    float _moveTimer;
    float _stopTimer;
    bool _isMoving;
    Vector2 _currentDirection;
    bool _hasCompletedInitialMove;
    bool _isInitialMove;
    float _initialMoveDistance;
    float _movedDistance;
    bool _isInAttackSequence;  
    float MOVE_DURATION = 3.5f;
    float STOP_DURATION = 4.0f;
    float SPEED = 120.0f;
    float SLOW_SPEED = 200.0f;
    float INITIAL_MOVE_AMOUNT = 150.0f;
    float Y_ALIGNMENT_THRESHOLD = 30.0f;  
    Vector2 GetLeftDirection();
    Vector2 GetDirectionToPlayer();

public:
    Annoyer(Vector2 spawnPosition);
    void Update() override;
    void Behaviour() override;
    void OnCollisionEnter(Object* object) override;
};