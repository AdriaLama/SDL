#include "KillerWhale.h"
#include "GameManager.h"
#include "ScoreManager.h"
#include "WaveManager.h"

void KillerWhale::Behaviour()
{

    if (currentState == SIMPLE_MOVE) {

        _physics->SetVelocity(Vector2(-200.f, 0.f));

        if (!spawnedUpWhale && _transform->position.x < RM->WINDOW_WIDTH / 3.f)
        {
            currentState = CHASE;
            _physics->SetVelocity(Vector2(0.f, 0.f));
        }

        else if (spawnedUpWhale && _transform->position.x < RM->WINDOW_WIDTH / 1.5f)
        {
            currentState = CHASE;
            _physics->SetVelocity(Vector2(0.f, 0.f));
        }
    }

    if (currentState == CHASE)
    {
     
        if (spawnedUpWhale) {
            _physics->AddForce(Vector2(250.f, 3500.f));
            _physics->SetLinearDrag(10.f);
        }  
        else {
            _physics->AddForce(Vector2(-250.f, -3500.f));
            _physics->SetLinearDrag(10.f);
        }
           
    }

    if (spawnedUpWhale && _transform->position.y > RM->WINDOW_HEIGHT - 50.f && currentState == CHASE) {
        currentState = STAY;
    }
    else if(!spawnedUpWhale && _transform->position.y < 50.f && currentState == CHASE) {
        currentState = STAY;
    }
    
    if (currentState == STAY) {
        _physics->SetVelocity(Vector2(-200.f, 0.f));
        _physics->AddForce(Vector2(0.0f, 0.0f));


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
            WAVE_MANAGER.OnEnemyDestroyed();
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

    if (_transform->position.x < -100.f)
    {
        WAVE_MANAGER.OnEnemyDestroyed();
        Destroy();
    }
}