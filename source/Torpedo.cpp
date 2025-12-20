#include "Torpedo.h"
#include "GameManager.h"

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


void Torpedo::Update()
{
	Enemy::Update();
	Behaviour();
}

