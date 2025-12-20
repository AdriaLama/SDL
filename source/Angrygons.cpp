#include "Angrygons.h"
#include "RenderManager.h"
#include <cmath>

Angrygons::Angrygons(Vector2 startPos)
    : Enemy()
{
    _renderer = new ImageRenderer(_transform, "resources/enemy.png", Vector2(0.f, 0.f), Vector2(0.f, 0.f));
    _transform->size = Vector2(50.f, 50.f);
    _transform->position = startPos;
    _physics->AddCollider(new AABB(_transform->position, _transform->size));

    currentState = SIMPLE_MOVE;
    stateTimer = 0.0f;
    spinAngle = 0.0f;
    spinRadius = 155.0f;
    health = 3;
}

void Angrygons::InitializeSpin()
{
    spinCenter.x = _transform->position.x + spinRadius;
    spinCenter.y = _transform->position.y;
    spinAngle = 180.0f;
}

void Angrygons::Behaviour()
{
    switch (currentState)
    {
    case STAY:
        StayBehaviour();
        break;

    case SIMPLE_MOVE:
        
        if (stateTimer < DOWN_DURATION)
        {
            SimpleMoveDown();
        }
        else if (stateTimer < DOWN_DURATION + RIGHT_1_DURATION)
        {
            SimpleMoveRight1();
        }
        else if (stateTimer < DOWN_DURATION + RIGHT_1_DURATION + UP_DURATION)
        {
            SimpleMoveUp();
        }
        else if (stateTimer < DOWN_DURATION + RIGHT_1_DURATION + UP_DURATION + RIGHT_SPIN_DURATION)
        {
            SimpleMoveRightSpin1();
        }
        else
        {
            
            InitializeSpin();
            currentState = CIRCLE_MOVE;
            stateTimer = 0.0f;
        }
        break;

    case CIRCLE_MOVE:
        
        if (spinAngle < 540.0f)
        {
            CircleMove1();
        }
        else
        {
            currentState = RETURN;
            stateTimer = 0.0f;
            _physics->SetVelocity(Vector2(MOVE_SPEED, 0.0f));
        }
        break;

    case RETURN:
       
        if (stateTimer < RIGHT_SPIN_DURATION)
        {
            SimpleMoveRightSpin2();
        }
        else if (spinAngle < 540.0f || stateTimer < RIGHT_SPIN_DURATION + SPIN_DURATION)
        {         
            if (stateTimer >= RIGHT_SPIN_DURATION && spinAngle >= 540.0f)
            {
                InitializeSpin();
            }
            CircleMove2();
        }
        else
        {
            SimpleMoveExit();
        }
        break;
    }
}

void Angrygons::StayBehaviour()
{
    _physics->SetVelocity(Vector2(0.0f, 0.0f));
}

void Angrygons::SimpleMoveDown()
{
    _physics->SetVelocity(Vector2(0.0f, MOVE_SPEED));
}

void Angrygons::SimpleMoveRight1()
{
    _physics->SetVelocity(Vector2(MOVE_SPEED, 0.0f));
}

void Angrygons::SimpleMoveUp()
{
    _physics->SetVelocity(Vector2(0.0f, -MOVE_SPEED));
}

void Angrygons::SimpleMoveRightSpin1()
{
    _physics->SetVelocity(Vector2(MOVE_SPEED, 0.0f));
}

void Angrygons::CircleMove1()
{
    PerformSpin(TM.GetDeltaTime());
}

void Angrygons::SimpleMoveRightSpin2()
{
    _physics->SetVelocity(Vector2(MOVE_SPEED, 0.0f));
}

void Angrygons::CircleMove2()
{
    PerformSpin(TM.GetDeltaTime());
}

void Angrygons::SimpleMoveExit()
{
    _physics->SetVelocity(Vector2(MOVE_SPEED, 0.0f));

    if (_transform->position.x > RM->WINDOW_WIDTH + 50.0f)
    {
        Destroy();
    }
}

void Angrygons::Update()
{
    stateTimer += TM.GetDeltaTime();
    Behaviour();
    Object::Update();
}

void Angrygons::PerformSpin(float deltaTime)
{
    spinAngle += SPIN_SPEED * deltaTime;
    float radians = spinAngle * (3.14159265f / 180.0f);
    spinCenter.x += 50.0f * deltaTime;
    _transform->position.x = spinCenter.x + spinRadius * cosf(radians);
    _transform->position.y = spinCenter.y + spinRadius * sinf(radians);
    _physics->SetVelocity(Vector2(0.0f, 0.0f));
}