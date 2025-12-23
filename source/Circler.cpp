#include "Circler.h"
#include "Bullet.h"
#include "ScoreManager.h"
#include "WaveManager.h"

bool Circler::circlerAlive = false;

void Circler::Behaviour()
{
    if (currentState == SIMPLE_MOVE)
    {
        if (!isDiagonal && !isStraight && _transform->position.y < RM->WINDOW_HEIGHT / 2.f - 150.f)
        {
            _physics->AddForce(Vector2(50.f, 150.f));
        }

        else if (isDiagonal)
        {
            _physics->AddForce(Vector2(1000.f, 1200.f));
            _physics->SetLinearDrag(8.f);
            diagonalDistance += 150.f * TM.GetDeltaTime();

            if (diagonalDistance >= 50.f)
            {
                isDiagonal = false;
                isStraight = true;
                straightDistance = 0.f;
            }
        }
       
        else if (isStraight)
        {
            _physics->AddForce(Vector2(1800.f, 0.f));
            _physics->SetLinearDrag(8.f);
            straightDistance += 150.f * TM.GetDeltaTime();

            if (straightDistance >= 50.f)
            {
                Vector2 currentPos = _transform->position;
                circleCenter.x = currentPos.x - radius;
                circleCenter.y = currentPos.y + 150.f;
                angle = 0.f;
                radius -= 50.f;
               

                isStraight = false;
                currentState = CIRCLE_MOVE;
            }
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
        float speed = 2.f;
        angle += speed * TM.GetDeltaTime();
        Vector2 targetPos;
        targetPos.x = circleCenter.x + cos(angle) * radius;
        targetPos.y = circleCenter.y + sin(angle) * radius;
        Vector2 toTarget = targetPos - _transform->position;
        float distance = sqrt(pow(toTarget.x + toTarget.y , 2));
        float forceMagnitude = distance * 50.f; 

        if (distance > 1.f) 
        {
            Vector2 direction = toTarget;
            direction.x /= distance; 
            direction.y /= distance;

            _physics->AddForce(direction * forceMagnitude);
        }

        _physics->SetLinearDrag(12.f);

        if (angle >= 5.23f)
        {
            loopCount++;

            if (loopCount >= 4)
            {
                currentState = RETURN;
            }
            else
            {
                currentState = SIMPLE_MOVE;
                isDiagonal = true;
                isStraight = false;
                diagonalDistance = 0.f;
            }
        }
    }

    else if (currentState == RETURN)
    {
        _physics->AddForce(Vector2(0.f, -800.f));
        _physics->SetLinearDrag(5.f);
    }
}

void Circler::OnCollisionEnter(Object* object)
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
            circlerAlive = false; 
            WAVE_MANAGER.OnEnemyDestroyed(_transform->position);
            HUD_MANAGER.AddScore(150);
            this->Destroy();
        }
        bullet->Destroy();
    }
}

void Circler::Update()
{
    Enemy::Update();
    Behaviour();

    if (_transform->position.y < -300.f)
    {
        WAVE_MANAGER.OnEnemyDestroyed();
        Destroy();
    }
}