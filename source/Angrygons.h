#pragma once
#include "Enemy.h"

class Angrygons : public Enemy
{
private:
    float stateTimer;
    float spinAngle;
    Vector2 spinCenter;
    float spinRadius;
    const float DOWN_DURATION = 1.7f;
    const float RIGHT_1_DURATION = 0.7f;
    const float UP_DURATION = 0.7f;
    const float RIGHT_SPIN_DURATION = 0.6f;
    const float SPIN_DURATION = 2.0f;
    const float MOVE_SPEED = 300.0f;
    const float SPIN_SPEED = 150.0f;
    void PerformSpin(float deltaTime);
    void InitializeSpin();
    void StayBehaviour();
    void SimpleMoveDown();
    void SimpleMoveRight1();
    void SimpleMoveUp();
    void SimpleMoveRightSpin1();
    void CircleMove1();
    void SimpleMoveRightSpin2();
    void CircleMove2();
    void SimpleMoveExit();

public:
    Angrygons(Vector2 startPos);
    void Behaviour() override;
    void Update() override;
};