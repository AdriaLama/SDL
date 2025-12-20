#pragma once
#include "Enemy.h"

class Daniels : public Enemy
{
private:
    Vector2 startPosition;
    Vector2 targetPosition;
    bool startedFromTop;

    float enterSpeed;
    float crossSpeed;

public:
    Daniels(bool fromTop);
    ~Daniels() = default;

    void Update() override;
    void Behaviour() override;
};