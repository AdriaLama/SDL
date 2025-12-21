
#include "SpaceBoss.h"
#include "SpaceBossBullets.h"
#include "GameManager.h"
#include "ScoreManager.h"

void SpaceBoss::Behaviour()
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

void SpaceBoss::ShootBullet()
{
    float minY = _transform->position.y - (_transform->size.y / 2.f);
    float maxY = _transform->position.y + (_transform->size.y / 2.f);
    float randomY = minY + (rand() % (int)(maxY - minY));
    SPAWNER.SpawnObjects(new SpaceBossBullets(Vector2(_transform->position.x, randomY)));
}

void SpaceBoss::OnCollisionEnter(Object* object)
{
    Bullet* bullet = dynamic_cast<Bullet*>(object);
    if (bullet)
    {
        health--;
        if (health <= 0)
        {
            HUD_MANAGER.AddScore(1000);
            this->Destroy();
        }
        bullet->Destroy();
    }
}

void SpaceBoss::Update()
{
    Enemy::Update();
    Behaviour();
}