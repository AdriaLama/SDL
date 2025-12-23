#include "HorizontalMedusa.h"
#include "Bullet.h"
#include "ScoreManager.h"
#include "WaveManager.h"

void HorizontalMedusa::Behaviour()
{
	_physics->AddForce(Vector2(-velocityX, 0.f));
	_physics->SetLinearDrag(10.f);

}

void HorizontalMedusa::OnCollisionEnter(Object* object)
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

void HorizontalMedusa::Update()
{
	Enemy::Update();
	Behaviour();

    if (_transform->position.x < -100.f)
    {
        WAVE_MANAGER.OnEnemyDestroyed();
        Destroy();
    }
}

