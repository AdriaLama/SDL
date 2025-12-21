#include "Missiles.h"
#include "Bullet.h"
#include "ScoreManager.h"

void Missiles::Behaviour()
{
	_physics->AddForce(Vector2(-velocityX, 0.f));
	_physics->SetLinearDrag(10.f);

}

void Missiles::OnCollisionEnter(Object* object)
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


void Missiles::Update()
{
	Enemy::Update();
	Behaviour();
}

