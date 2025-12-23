#pragma once
#include "Enemy.h"
class Chomper : public Enemy
{
private:
    Vector2 lineCenter;
    float angle;
    float radius;
    float angularSpeed;
    float leftDrift;
public:
    Chomper(Vector2 spawnPosition, int indexInLine);
    void Update() override;
    void Behaviour() override;
    void OnCollisionEnter(Object* object) override;
};