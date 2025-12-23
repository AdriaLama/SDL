#include "RoboKrabs.h"
#include "GameManager.h"
#include "ScoreManager.h"
#include "WaveManager.h"

void RoboKrabs::Behaviour()
{
    Player* player = GAME_MANAGER.GetPlayer();

    if (currentState == SIMPLE_MOVE) {
        if (spawnedLeftKrabs) {
            _physics->AddForce(Vector2(1300.f, 0.f));
            _physics->SetLinearDrag(10.f);
            if (_transform->position.x > RM->WINDOW_WIDTH / 2.f - 200.f) {
                currentState = STAY;
            }
        }
        else if (!spawnedLeftKrabs) {
            _physics->AddForce(Vector2(-1300.f, 0.f));
            _physics->SetLinearDrag(10.f);
            if (_transform->position.x < RM->WINDOW_WIDTH / 2.f + 200.f) {
                currentState = STAY;
            }
        }
    }

    if (currentState == STAY)
    {
        jumpTimer += TM.GetDeltaTime();

        _physics->SetVelocity(Vector2(0.f, 0.f));

        if (jumpTimer >= jumpCooldown && player != nullptr)
        {
            currentState = CHASE;
            Vector2 playerPos = player->GetTransform()->position;
            float dx = playerPos.x - _transform->position.x;
            float dy = playerPos.y - _transform->position.y;
            float length = sqrt(dx * dx + dy * dy);

            if (length > 0)
            {
                dx /= length;
                dy /= length;
            }

            _physics->SetVelocity(Vector2(dx * 500.f, dy * 500.f));
            _physics->SetLinearDrag(1.f);
            jumpTimer = 0.f;
        }
    }

    if (currentState == CHASE)
    {
        jumpTimer += TM.GetDeltaTime();

        if (jumpTimer >= jumpCooldown)
        {
            currentState = STAY;
            _physics->SetVelocity(Vector2(0.f, 0.f));
            jumpTimer = 0.f;
            jumpCooldown = (rand() % 2) + 1; 
        }
    }
}

void RoboKrabs::Update()
{
    Enemy::Update();
    Behaviour();

    if (_transform->position.y < -100.f || _transform->position.y > RM->WINDOW_HEIGHT + 100.f || _transform->position.x > RM->WINDOW_WIDTH + 100.f || _transform->position.x < -100.f)
    {
        WAVE_MANAGER.OnEnemyDestroyed();
        Destroy();
    }
}

void RoboKrabs::OnCollisionEnter(Object* object)
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
