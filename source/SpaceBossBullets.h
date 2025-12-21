#pragma once
#include "TimeManager.h"
#include "RenderManager.h"
#include "Enemy.h"

class SpaceBossBullets : public Enemy
{
public:
    SpaceBossBullets(Vector2 spawnPosition) : Enemy()
    {
        _renderer = new ImageRenderer(_transform, "resources/image.png", Vector2(0.f, 0.f), Vector2(0.f, 0.f));
        _transform->position = spawnPosition;
        _transform->size = Vector2(75.f, 75.f);
    }

    void Update() override
    {
        Enemy::Update();

        _physics->AddForce(Vector2(-3500.f, 0.f));
        _physics->SetLinearDrag(10.f);

        if (_transform->position.x < -100.f || _transform->position.x > RM->WINDOW_WIDTH + 100.f || _transform->position.y < -100.f || _transform->position.y > RM->WINDOW_HEIGHT + 100.f)
        {
            Destroy();
        }
    }

    void Behaviour() override {}
};