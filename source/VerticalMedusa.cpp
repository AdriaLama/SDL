#include "VerticalMedusa.h"
#include "TimeManager.h"
#include "ScoreManager.h"
#include "WaveManager.h"

VerticalMedusa::VerticalMedusa(Vector2 spawnPosition)
    : Enemy()
{
    _renderer = new ImageRenderer(_transform, "resources/verticalMedusa.png", Vector2(0.f, 0.f), Vector2(0.f, 0.f));
    _transform->size = Vector2(90.f, 90.f);
    _transform->position = spawnPosition;

    stopTimer = 0.f;
    stopDuration = 1.5f; 
    isMoving = true;
    moveSpeed = 100.f;

    _physics->AddCollider(new AABB(_transform->position, _transform->size));
    currentState = SIMPLE_MOVE;
    health = 2;
}

void VerticalMedusa::Behaviour()
{
    if (currentState == SIMPLE_MOVE)
    {
        if (isMoving)
        {
            _physics->SetVelocity(Vector2(0.f, -moveSpeed)); 

            stopTimer += TM.GetDeltaTime();
            if (stopTimer >= stopDuration)
            {
                isMoving = false;
                stopTimer = 0.f;
            }
        }
        else
        {
            _physics->SetVelocity(Vector2(0.f, 0.f)); 

            stopTimer += TM.GetDeltaTime();
            if (stopTimer >= stopDuration)
            {
                isMoving = true;
                stopTimer = 0.f;
            }
        }
    }
}

void VerticalMedusa::OnCollisionEnter(Object* object)
{
    if (isDying) return;
    Bullet* bullet = dynamic_cast<Bullet*>(object);
    if (bullet)
    {
        health--;
        AM->PlaySound("resources/501104__evretro__8-bit-damage-sound.wav");
        if (health <= 0)
        {
            AM->PlaySound("resources/450616__breviceps__8-bit-error.wav");
            isDying = true;
            WAVE_MANAGER.OnEnemyDestroyed(_transform->position);
            HUD_MANAGER.AddScore(150);
            this->Destroy();
        }
        bullet->Destroy();
    }
}

void VerticalMedusa::Update()
{
    Enemy::Update();
    Behaviour();

    if (_transform->position.y < -100.f)
    {
        WAVE_MANAGER.OnEnemyDestroyed();
        Destroy();
    }
}