#include "Bubble.h"
#include "TimeManager.h"
#include "Bullet.h"
#include "ScoreManager.h"
#include "WaveManager.h"

void Bubble::Behaviour()
{
   
    if (currentState == SIMPLE_MOVE)
    {
        if (_transform->position.x > RM->WINDOW_WIDTH / 3.f)
        {
            _physics->AddForce(Vector2(-400.f, 0.f));
            _physics->SetLinearDrag(1.f);
        }
        else
        {
            currentState = CIRCLE_MOVE;
            circleCenter = _transform->position; 
            angle = 0.f; 
        }
    }

    
    else if (currentState == CIRCLE_MOVE)
    {
        float radius = 100.f; 
        float speed = 3.f;  

        angle += speed * TM.GetDeltaTime();

        
        _transform->position.x = circleCenter.x + cos(angle) * radius;
        _transform->position.y = circleCenter.y + sin(angle) * radius;
        _physics->SetAngularDrag(10.f);

        
        if (angle >= 5.23f) 
        {
            currentState = RETURN;
        }
    }

 
    else if (currentState == RETURN)
    {
       
        if (spawnedUpBubbles && _transform->position.y < RM->WINDOW_HEIGHT - 200.f) 
        {
            _physics->AddForce(Vector2(1300.f, 1300.f));
            _physics->SetLinearDrag(5.f);
        }
        else if (!spawnedUpBubbles && _transform->position.y > 200.f) 
        {
            _physics->AddForce(Vector2(1300.f, -1300.f));
            _physics->SetLinearDrag(5.f);
        }
        else 
        {
            _physics->AddForce(Vector2(1300.f, 0.f));
            _physics->SetLinearDrag(5.f);
        }
    }
}

void Bubble::OnCollisionEnter(Object* object)
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

void Bubble::Update() {

    Enemy::Update(); 
    Behaviour();

    if (_transform->position.x < -200 || _transform->position.x > RM->WINDOW_WIDTH + 200 || _transform->position.y < -200 || _transform->position.y > RM->WINDOW_HEIGHT + 200)
    {
        WAVE_MANAGER.OnEnemyDestroyed();
        Destroy();
    }
}
