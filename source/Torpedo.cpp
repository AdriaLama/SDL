#include "Torpedo.h"
#include "GameManager.h"
#include "ScoreManager.h"
#include "WaveManager.h"

void Torpedo::Behaviour()
{
    Player* player = GAME_MANAGER.GetPlayer();

    _physics->AddForce(Vector2(-900.f, 0.f));
    _physics->SetLinearDrag(10.f);
    if (player != nullptr)
    {
        Vector2 playerPos = player->GetTransform()->position;
        float distance = sqrt(pow(playerPos.x - _transform->position.x, 2));

        if (distance < 1000.f)
        {
            _physics->AddForce(Vector2(-velocityX, 0.f));
            _physics->SetLinearDrag(10.f);
        }
    }


}

void Torpedo::OnCollisionEnter(Object* object)
{
    if (isDying) return;
    Bullet* bullet = dynamic_cast<Bullet*>(object);
    if (bullet)
    {
        health--;
        AM->PlaySound("resources/501104__evretro__8-bit-damage-sound.wav");
        if (health <= 0)
        {
            isDying = true;
            WAVE_MANAGER.OnEnemyDestroyed(_transform->position);
            HUD_MANAGER.AddScore(150);
            this->Destroy();
        }
        bullet->Destroy();
    }
}


void Torpedo::Update()
{
	Enemy::Update();
	Behaviour();

    if (_transform->position.x < -100.f)
    {
        WAVE_MANAGER.OnEnemyDestroyed();
        Destroy();
    }
}

