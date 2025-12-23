#pragma once
#include "Enemy.h"

class UFO : public Enemy
{
private:
    float moveTimer;
    int cycleCount;
    float initialX;
    float centerX;
    float fastSpeed;  
    const float DECELERATION = 800.0f;
    const float STOP_THRESHOLD = 5.0f;

public:
    UFO(int index = 0);
    void Behaviour() override;
    void Update() override;
    void OnCollisionEnter(Object* other);
};