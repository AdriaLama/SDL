#include "Angrygons.h"
#include "RenderManager.h"
#include <cmath>
#include "Bullet.h"
#include "ScoreManager.h"
#include "WaveManager.h"

Angrygons::Angrygons(Vector2 startPos, int index)
    : Enemy(), globalTimer(0.0f), startDelay(index * 0.3f)
{
    _renderer = new ImageRenderer(_transform, "resources/angrygons.png", Vector2(0.f, 0.f), Vector2(0.f, 0.f));
    _transform->size = Vector2(50.f, 50.f);
    _transform->position = startPos;
    _physics->AddCollider(new AABB(_transform->position, _transform->size));

    currentState = STAY;
    stateTimer = 0.0f;
    spinAngle = 0.0f;
    spinRadius = 155.0f;
    health = 2;
}

Angrygons::~Angrygons()
{
}

void Angrygons::InitializeSpin()
{
    spinCenter.x = _transform->position.x + spinRadius;
    spinCenter.y = _transform->position.y;
    spinAngle = 180.0f;
}

void Angrygons::Behaviour()
{
    
    if (globalTimer < startDelay)
    {
        StayBehaviour();
        return;
    }

    float adjustedTimer = stateTimer - startDelay;

    switch (currentState)
    {
    case STAY:
       
        if (globalTimer >= startDelay)
        {
            currentState = SIMPLE_MOVE;
            stateTimer = startDelay; 
        }
        else
        {
            StayBehaviour();
        }
        break;

    case SIMPLE_MOVE:
        if (adjustedTimer < DOWN_DURATION)
        {
            SimpleMoveDown();
        }
        else if (adjustedTimer < DOWN_DURATION + RIGHT_1_DURATION)
        {
            SimpleMoveRight1();
        }
        else if (adjustedTimer < DOWN_DURATION + RIGHT_1_DURATION + UP_DURATION)
        {
            SimpleMoveUp();
        }
        else if (adjustedTimer < DOWN_DURATION + RIGHT_1_DURATION + UP_DURATION + RIGHT_SPIN_DURATION)
        {
            SimpleMoveRightSpin1();
        }
        else
        {
            InitializeSpin();
            currentState = CIRCLE_MOVE;
        }
        break;

    case CIRCLE_MOVE:
        if (spinAngle < 540.0f)
        {
            CircleMove1();
        }
        else
        {
            currentState = RETURN;
            _physics->SetVelocity(Vector2(MOVE_SPEED, 0.0f));
        }
        break;

    case RETURN:
        if (adjustedTimer < DOWN_DURATION + RIGHT_1_DURATION + UP_DURATION + RIGHT_SPIN_DURATION + SPIN_DURATION + RIGHT_SPIN_DURATION)
        {
            SimpleMoveRightSpin2();
        }
        else if (spinAngle < 540.0f || adjustedTimer < DOWN_DURATION + RIGHT_1_DURATION + UP_DURATION + RIGHT_SPIN_DURATION + SPIN_DURATION + RIGHT_SPIN_DURATION + SPIN_DURATION)
        {
            if (adjustedTimer >= DOWN_DURATION + RIGHT_1_DURATION + UP_DURATION + RIGHT_SPIN_DURATION + SPIN_DURATION + RIGHT_SPIN_DURATION && spinAngle >= 540.0f)
            {
                InitializeSpin();
            }
            CircleMove2();
        }
        else
        {
            SimpleMoveExit();
        }
        break;
    }
}

void Angrygons::StayBehaviour()
{
    _physics->SetVelocity(Vector2(0.0f, 0.0f));
}

void Angrygons::SimpleMoveDown()
{
    _physics->SetVelocity(Vector2(0.0f, MOVE_SPEED));
}

void Angrygons::SimpleMoveRight1()
{
    _physics->SetVelocity(Vector2(MOVE_SPEED, 0.0f));
}

void Angrygons::SimpleMoveUp()
{
    _physics->SetVelocity(Vector2(0.0f, -MOVE_SPEED));
}

void Angrygons::SimpleMoveRightSpin1()
{
    _physics->SetVelocity(Vector2(MOVE_SPEED, 0.0f));
}

void Angrygons::CircleMove1()
{
    PerformSpin(TM.GetDeltaTime());
}

void Angrygons::SimpleMoveRightSpin2()
{
    _physics->SetVelocity(Vector2(MOVE_SPEED, 0.0f));
}

void Angrygons::CircleMove2()
{
    PerformSpin(TM.GetDeltaTime());
}

void Angrygons::SimpleMoveExit()
{
    _physics->SetVelocity(Vector2(MOVE_SPEED, 0.0f));
}

void Angrygons::Update()
{
    float deltaTime = TM.GetDeltaTime();
    stateTimer += deltaTime;
    globalTimer += deltaTime;

    Behaviour();
    Object::Update();

    if (_transform->position.x > RM->WINDOW_WIDTH + 100.f)
    {
        WAVE_MANAGER.OnEnemyDestroyed();
        Destroy();
    }
}

void Angrygons::OnCollisionEnter(Object* object)
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

void Angrygons::PerformSpin(float deltaTime)
{
    spinAngle += SPIN_SPEED * deltaTime;
    float radians = spinAngle * (3.14159265f / 180.0f);
    spinCenter.x += 50.0f * deltaTime;
    _transform->position.x = spinCenter.x + spinRadius * cosf(radians);
    _transform->position.y = spinCenter.y + spinRadius * sinf(radians);
    _physics->SetVelocity(Vector2(0.0f, 0.0f));
}