#include "KillerWhale.h"
#include "GameManager.h"
#include "ScoreManager.h"

void KillerWhale::Behaviour()
{

    Player* player = GAME_MANAGER.GetPlayer();

    if (player != nullptr)
    {
        Vector2 playerPos = player->GetTransform()->position;
        float distance = sqrt(pow(playerPos.x - _transform->position.x, 2));

        if (distance < 400.f && currentState == STAY)
        {
            currentState = SIMPLE_MOVE;
        }
    }

    if (currentState == SIMPLE_MOVE)
    {
     
        if (spawnedUpWhale) {
            _physics->AddForce(Vector2(250.f, 2000.f));
            _physics->SetLinearDrag(10.f);
        }  
        else {
            _physics->AddForce(Vector2(-250.f, -2000.f));
            _physics->SetLinearDrag(10.f);
        }
           
    }
}

void KillerWhale::OnCollisionEnter(Object* object)
{
    Bullet* bullet = dynamic_cast<Bullet*>(object);
    if (bullet)
    {
        health--;
        if (health <= 0)
        {
            HUD_MANAGER.AddScore(750);
            this->Destroy();
        }
        bullet->Destroy();
    }
}



void KillerWhale::Update()
{
	Enemy::Update();
	Behaviour();
}