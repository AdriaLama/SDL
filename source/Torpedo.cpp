#include "Torpedo.h"
#include "GameManager.h"
#include "ScoreManager.h"

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
    Bullet* bullet = dynamic_cast<Bullet*>(object);
    if (bullet)
    {
        health--;
        health--;
        if (health <= 0)
        {
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
}

