#pragma once
#include "Enemy.h"
#include "Player.h"

class RoboKrabs : public Enemy
{
private:

    float jumpTimer = 0.f;
    float jumpCooldown = 3.f;
    bool spawnedLeftKrabs;

public:
    RoboKrabs(Vector2 spawnPosition) : Enemy()
    {
        _renderer = new ImageRenderer(_transform, "resources/roboKrabs.png", Vector2(0.f, 0.f), Vector2(0.f, 0.f));

        _transform->size = Vector2(100.f, 100.f);
        if (spawnPosition.x < RM->WINDOW_WIDTH / 2.f)
            spawnedLeftKrabs = true;
        else
            spawnedLeftKrabs = false;
        _transform->position = spawnPosition;
        currentState = SIMPLE_MOVE;
        jumpCooldown = (rand() % 3) + 1;
        health = 2;
        _physics->AddCollider(new AABB(_transform->position, _transform->size));

    }

    void Behaviour();
    void Update() override;
    void OnCollisionEnter(Object* object) override;
};