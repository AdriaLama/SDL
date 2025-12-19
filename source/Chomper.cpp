#include "Chomper.h"
#include "TimeManager.h"
#include <cmath>
Chomper::Chomper(Vector2 spawnPosition, int indexInLine)
    : Enemy()
{
    _renderer = new ImageRenderer(_transform, "resources/image.png", Vector2(0.f, 0.f), Vector2(0.f, 0.f));
    _transform->size = Vector2(100.f, 100.f);
    _transform->position = spawnPosition;
    lineCenter = spawnPosition;
    radius = 30.f;
    angularSpeed = 2.5f;
    angle = indexInLine * 0.5f; 
    leftDrift = 50.f;
    _physics->AddCollider(new AABB(_transform->position, _transform->size));
    currentState = CIRCLE_MOVE;
    health = 2;
}
void Chomper::Behaviour()
{
    if (currentState == CIRCLE_MOVE)
    {
        angle += angularSpeed * TM.GetDeltaTime();
        lineCenter.x -= leftDrift * TM.GetDeltaTime();
        _transform->position.x = lineCenter.x + cos(angle) * radius;
        _transform->position.y = lineCenter.y + sin(angle) * radius;
    }
}
void Chomper::Update()
{
    Enemy::Update();
    Behaviour();
}