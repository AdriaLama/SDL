// BioTitan.cpp
#include "BioTitan.h"
#include "BioTitanBullets.h"
#include "GameManager.h"

void BioTitan::Behaviour()
{

    if (currentState == STAY)
    {
        shootTimer += TM.GetDeltaTime();

        if (shootTimer >= shootCooldown)
        {
            currentState = CHASE;
            bulletsShot = 0;
            burstTimer = 0.f;
            bulletsPerBurst = 3 + (rand() % 5); 
        }
    }

    if (currentState == CHASE)
    {
        burstTimer += TM.GetDeltaTime();

        if (burstTimer >= bulletDelay)
        {
            ShootBullet();
            bulletsShot++;
            burstTimer = 0.f;

            if (bulletsShot >= bulletsPerBurst)
            {
                currentState = STAY;
                shootTimer = 0.f;
                shootCooldown = 3.f + (rand() % 5); 
            }
        }
    }
}

void BioTitan::ShootBullet()
{
    float minY = _transform->position.y - (_transform->size.y / 2.f);
    float maxY = _transform->position.y + (_transform->size.y / 2.f);
    float randomY = minY + (rand() % (int)(maxY - minY));
    SPAWNER.SpawnObjects(new BioTitanBullets(Vector2(_transform->position.x, randomY)));
}

void BioTitan::Update()
{
    Enemy::Update();
    Behaviour();
}