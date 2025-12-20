#include "Daniels.h"
#include "RenderManager.h"
#include <cmath>

Daniels::Daniels(bool fromTop)
    : Enemy()
{
    health = 1;
    currentState = State::SIMPLE_MOVE;
    startedFromTop = fromTop;
    enterSpeed = 150.0f;
    crossSpeed = 400.0f;
    float screenWidth = (float)RM->WINDOW_WIDTH;
    float screenHeight = (float)RM->WINDOW_HEIGHT;
    float centerY = screenHeight / 2.0f;
    _physics->AddCollider(new AABB(_transform->position, _transform->size));

    if (fromTop)
    {
        startPosition = Vector2(-_transform->size.x, 100.0f);
        targetPosition = Vector2(screenWidth + _transform->size.x, 100.0f);
    }
    else
    {
        startPosition = Vector2(-_transform->size.x, screenHeight - 100.0f);
        targetPosition = Vector2(screenWidth + _transform->size.x, screenHeight - 100.0f);
    }
    _transform->position = startPosition;
    delete _renderer;
    _renderer = new ImageRenderer(_transform, "resources/image.png", Vector2(0.f, 0.f), Vector2(0.f, 0.f));
}

void Daniels::Update()
{
    Behaviour();
    Enemy::Update();
}

void Daniels::Behaviour()
{
    float dt = TM.GetDeltaTime();
    float screenWidth = RM->WINDOW_WIDTH;
    float screenHeight = RM->WINDOW_HEIGHT;
    float centerY = screenHeight / 2.0f;
    float separationDistance = 150.0f; 

    switch (currentState)
    {
    case State::SIMPLE_MOVE:
    {
        _transform->position.x += crossSpeed * dt;
        if (_transform->position.x >= screenWidth - 100.0f)
        {
            _transform->position.x = screenWidth - 100;
            currentState = State::RETURN;
        }
        break;
    }
    case State::RETURN:
    {
        if (startedFromTop)
        {
            float targetY = centerY - separationDistance / 2.0f;
            if (_transform->position.y < targetY - 5.0f)
            {
                _transform->position.y += enterSpeed * dt;
            }
            else
            {
                _transform->position.y = targetY;
                currentState = State::CHASE;
            }
        }
        else
        {
            float targetY = centerY + separationDistance / 2.0f;
            if (_transform->position.y > targetY + 5.0f)
            {
                _transform->position.y -= enterSpeed * dt;
            }
            else
            {
                _transform->position.y = targetY;
                currentState = State::CHASE;
            }
        }
        break;
    }
    case State::CHASE:
    {
        _transform->position.x -= crossSpeed * dt; 

        if (_transform->position.x < -_transform->size.x) 
        {
            Destroy();
        }
        break;
    }
    default:
        break;
    }
}