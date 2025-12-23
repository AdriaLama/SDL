#include "Ufo.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Bullet.h"
#include "ScoreManager.h"
#include "WaveManager.h"

UFO::UFO(int index)
    : Enemy()
{
    _renderer = new ImageRenderer(_transform, "resources/ufo.png", Vector2(0.f, 0.f), Vector2(60.f, 40.f));
    health = 2;
    currentState = SIMPLE_MOVE;
    moveTimer = 0.0f;
    cycleCount = 0;

   
    fastSpeed = (rand() % 301) + 200.0f;  

    initialX = RM->WINDOW_WIDTH + 50.0f;
    centerX = RM->WINDOW_WIDTH / 2;

   
    float verticalSpacing = 80.0f;  
    float startY = 100.0f; 

    _transform->position = Vector2(initialX, startY + (index * verticalSpacing));

    _physics->AddCollider(new AABB(_transform->position, _transform->size));
    _physics->SetVelocity(Vector2(-fastSpeed, 0.0f));
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
            _physics->SetVelocity(Vector2(fastSpeed, 0.0f));
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
                WAVE_MANAGER.OnEnemyDestroyed();
                Destroy();
            }
            else
            {
                currentState = SIMPLE_MOVE;
                _physics->SetVelocity(Vector2(-fastSpeed, 0.0f));
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

    if (_transform->position.x > RM->WINDOW_WIDTH + 500.f) {
        WAVE_MANAGER.OnEnemyDestroyed();
        Destroy();

    }
}

void UFO::OnCollisionEnter(Object* other)
{
    if (isDying) return;

    Bullet* bullet = dynamic_cast<Bullet*>(other);
    if (bullet)
    {
        health--;
        AM->PlaySound("resources/501104__evretro__8-bit-damage-sound.wav");

        if (health <= 0)
        {
            isDying = true;
            WAVE_MANAGER.OnEnemyDestroyed(_transform->position);
            HUD_MANAGER.AddScore(150);
            this->Destroy();
        }
        bullet->Destroy();
    }
}