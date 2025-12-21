#include "VerticalMedusa.h"
#include "TimeManager.h"
#include "ScoreManager.h"

VerticalMedusa::VerticalMedusa(Vector2 spawnPosition)
    : Enemy()
{
    _renderer = new ImageRenderer(_transform, "resources/image.png", Vector2(0.f, 0.f), Vector2(0.f, 0.f));
    _transform->size = Vector2(90.f, 90.f);
    _transform->position = spawnPosition;

    stopTimer = 0.f;
    stopDuration = 1.5f; 
    isMoving = true;
    moveSpeed = 100.f;

    _physics->AddCollider(new AABB(_transform->position, _transform->size));
    currentState = SIMPLE_MOVE;
    health = 1;
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
    Bullet* bullet = dynamic_cast<Bullet*>(object);
    if (bullet)
    {
        health--;
        if (health <= 0)
        {
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
}