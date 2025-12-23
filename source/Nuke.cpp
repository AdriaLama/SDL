#include "Nuke.h"
#include "GameManager.h"
#include "ScoreManager.h"
#include "WaveManager.h"

void Nuke::Behaviour()
{

    Player* player = GAME_MANAGER.GetPlayer();

    if (player != nullptr)
    {
        Vector2 playerPos = player->GetTransform()->position;
        float distance = sqrt(pow(playerPos.x - _transform->position.x, 2));

        if (distance < 750.f && currentState == STAY)
        {
            currentState = SIMPLE_MOVE;
        }
    }

    if (currentState == SIMPLE_MOVE)
    {
          _physics->AddForce(Vector2(0.f, -2300.f));
          _physics->SetLinearDrag(10.f);
    }
}

void Nuke::OnCollisionEnter(Object* object)
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


void Nuke::Update()
{
	Enemy::Update();
	Behaviour();

    if (_transform->position.y < -100.f)
    {
        WAVE_MANAGER.OnEnemyDestroyed();
        Destroy();
    }
}
