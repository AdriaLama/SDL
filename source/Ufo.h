#pragma once
#include "Enemy.h"

class UFO : public Enemy
{
private:
    float moveTimer;
    int cycleCount;
    float initialX;
    float centerX;

    const float FAST_SPEED = 400.0f;
    const float DECELERATION = 800.0f;
    const float STOP_THRESHOLD = 5.0f;

public:
    UFO();
    void Behaviour() override;
    void Update() override;
};