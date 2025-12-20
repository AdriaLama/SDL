#include "Annoyer.h"
#include "RenderManager.h"
#include "TimeManager.h"

Annoyer::Annoyer(Vector2 spawnPosition)
    : Enemy()
{
    _renderer = new ImageRenderer(_transform, "resources/image.png", Vector2(0.f, 0.f), Vector2(100.f, 100.f));
    _transform->size = Vector2(100.f, 100.f);
    _transform->position = spawnPosition;
    health = 3;
    currentState = SIMPLE_MOVE;
    _moveTimer = 0.0f;
    _stopTimer = 0.0f;
    _movedDistance = 0.0f;

    float screenHeight = 720.0f;
    if (spawnPosition.y < screenHeight / 2.0f) {
        _currentDirection = Vector2(0.0f, 1.0f);
    }
    else {
        _currentDirection = Vector2(0.0f, -1.0f);
    }
}

Vector2 Annoyer::GetLeftDirection()
{
    return Vector2(-1.0f, 0.0f);
}

Vector2 Annoyer::GetDirectionToPlayer()
{
    Player* player = GAME_MANAGER.GetPlayer();
    if (!player) return Vector2(1.0f, 0.0f);

    Vector2 playerPos = player->GetTransform()->position;
    Vector2 direction = playerPos - _transform->position;
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0.0f) {
        return Vector2(direction.x / length, direction.y / length);
    }
    return Vector2(1.0f, 0.0f);
}

void Annoyer::Update()
{
    Behaviour();
    Enemy::Update();
}

void Annoyer::Behaviour()
{
    float dt = TM.GetFrameTime();
    Player* player = GAME_MANAGER.GetPlayer();
    Vector2 playerPos = player->GetTransform()->position;

    switch (currentState)
    {
    case SIMPLE_MOVE:
    {
        float moveAmount = SPEED * dt;
        _movedDistance += moveAmount;
        Vector2 movement = _currentDirection * moveAmount;
        _transform->position = _transform->position + movement;

        if (_movedDistance >= INITIAL_MOVE_AMOUNT) {
            currentState = CHASE;
            _movedDistance = 0.0f;
        }
    }
    break;

    case CHASE:
    {
        _currentDirection = GetDirectionToPlayer();
        Vector2 movement = _currentDirection * SPEED * dt;
        _transform->position = _transform->position + movement;
        float yDifference = abs(_transform->position.y - playerPos.y);
        bool isRightOfPlayer = _transform->position.x > playerPos.x;

        if (yDifference <= Y_ALIGNMENT_THRESHOLD && isRightOfPlayer) {
            currentState = RETURN;
            _stopTimer = 0.0f;
            _currentDirection = GetLeftDirection();
        }
    }
    break;

    case RETURN:
    {
        _stopTimer += dt;
        Vector2 movement = _currentDirection * SLOW_SPEED * dt;
        _transform->position = _transform->position + movement;

        if (_stopTimer >= STOP_DURATION) {
            currentState = CHASE;
            _stopTimer = 0.0f;
        }
    }
    break;

    default:
        break;
    }
}