#include "Nuke.h"
#include "GameManager.h"

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


void Nuke::Update()
{
	Enemy::Update();
	Behaviour();
}
