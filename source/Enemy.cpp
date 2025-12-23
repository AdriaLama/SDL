#include "Enemy.h"
#include "Bullet.h"
#include "GameManager.h"
#include "ScoreManager.h"

void Enemy::OnCollisionEnter(Object* other)
{
    Bullet* bullet = dynamic_cast<Bullet*>(other);
    if (bullet)
    {
        health--;

        if (health <= 0)
        {  
            isDying = true;
            int points = 100;
            HUD_MANAGER.AddScore(points);
            this->Destroy();
        }       
        bullet->Destroy();
    }
}
