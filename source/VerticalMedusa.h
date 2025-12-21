#pragma once
#include "Enemy.h"

class VerticalMedusa : public Enemy
{
private:
    float stopTimer;
    float stopDuration;
    bool isMoving;
    float moveSpeed;

public:
    VerticalMedusa(Vector2 spawnPosition);
    void Update() override;
    void Behaviour() override;
    void OnCollisionEnter(Object* object) override;
};