#pragma once
#include "Enemy.h"

class SpaceBoss : public Enemy
{
private:
    float shootTimer = 0.f;
    float shootCooldown;
    int bulletsShot = 0;
    int bulletsPerBurst = 5;
    float bulletDelay = 0.15f;
    float burstTimer = 0.f;

public:
    SpaceBoss(Vector2 spawnPosition) : Enemy()
    {
        _renderer = new ImageRenderer(_transform, "resources/boss2.png", Vector2(0.f, 0.f), Vector2(0.f, 0.f));
        _transform->size = Vector2(300.f, 300.f);
        _transform->position = spawnPosition;
        _physics->AddCollider(new AABB(_transform->position, _transform->size));
        currentState = SIMPLE_MOVE;
        health = 25;
        shootCooldown = 2.f;
        bulletsPerBurst = 3 + (rand() % 5);
    }

    void Update() override;
    void Behaviour();
    void ShootBullet();
    void OnCollisionEnter(Object* object) override;
};