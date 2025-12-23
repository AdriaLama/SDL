#pragma once
#include "Enemy.h"

class Angrygons : public Enemy
{
private:
    float stateTimer;
    float globalTimer;
    float spinAngle;
    Vector2 spinCenter;
    float spinRadius;
    float startDelay;  
    float DOWN_DURATION = 1.9f;
    float RIGHT_1_DURATION = 0.7f;
    float UP_DURATION = 0.7f;
    float RIGHT_SPIN_DURATION = 0.6f;
    float SPIN_DURATION = 2.0f;
    float MOVE_SPEED = 300.0f;
    float SPIN_SPEED = 150.0f;
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
    Angrygons(Vector2 startPos, int index = 0);
    ~Angrygons();
    void Behaviour() override;
    void Update() override;
    void OnCollisionEnter(Object* object) override;
};