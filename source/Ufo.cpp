#include "Ufo.h"
#include <iostream>

UFO::UFO()
    : Enemy()
{
    _renderer = new ImageRenderer(_transform, "resources/image.png", Vector2(0.f, 0.f), Vector2(60.f, 40.f));
    health = 1;
    currentState = SIMPLE_MOVE;
    moveTimer = 0.0f;
    cycleCount = 0;
    initialX = RM->WINDOW_WIDTH + 50.0f;
    centerX = RM->WINDOW_WIDTH / 2;
    _transform->position = Vector2(initialX, 300.0f);
    _physics->AddCollider(new AABB(_transform->position, _transform->size));
    _physics->SetVelocity(Vector2(-FAST_SPEED, 0.0f));
}

void UFO::Behaviour()
{
    Vector2 pos = _transform->position;
    Vector2 vel = _physics->GetVelocity();
    float dt = TM.GetFrameTime();

    switch (currentState)
    {
    case SIMPLE_MOVE:
    {
        
        if (pos.x <= centerX && vel.x < 0)
        {
            _transform->position.x = centerX;
            _physics->SetVelocity(Vector2(0.0f, 0.0f)); 
            currentState = STAY;
            moveTimer = 0.0f; 
        }
        break;
    }
    case STAY:
    {
       
        moveTimer += dt;

        if (moveTimer >= 2.0f) 
        {
            moveTimer = 0.0f;
            currentState = RETURN;
            _physics->SetVelocity(Vector2(FAST_SPEED, 0.0f));
        }
        break;
    }
    case RETURN:
    {
        if (pos.x >= initialX)
        {
            _transform->position.x = initialX;
            cycleCount++;
            if (cycleCount >= 2)
            {
                Destroy();
            }
            else
            {
                currentState = SIMPLE_MOVE;
                _physics->SetVelocity(Vector2(-FAST_SPEED, 0.0f));
            }
        }
        break;
    }
    default:
        break;
    }
}
void UFO::Update()
{
    Enemy::Update();
    Behaviour();
}