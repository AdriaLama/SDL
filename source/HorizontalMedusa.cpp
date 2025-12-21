#include "HorizontalMedusa.h"
#include "Bullet.h"
#include "ScoreManager.h"

void HorizontalMedusa::Behaviour()
{
	_physics->AddForce(Vector2(-velocityX, 0.f));
	_physics->SetLinearDrag(10.f);

}

void HorizontalMedusa::OnCollisionEnter(Object* object)
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


void HorizontalMedusa::Update()
{
	Enemy::Update();
	Enemy::Update();
	Behaviour();
}

