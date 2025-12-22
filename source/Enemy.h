#pragma once
#include "ImageObject.h"
#include "RenderManager.h"
#include "Spawner.h"
#include "TimeManager.h"

enum State
{
    STAY,
    SIMPLE_MOVE,
    CIRCLE_MOVE,
    CHASE,
    RETURN
};

class Enemy : public ImageObject
{
protected:
    int health;
    State currentState;
public:
    Enemy()
        : ImageObject("resources/boss1.png", Vector2(0.f, 0.f), Vector2(50.f, 50.f))
    {


    }

    int GetHealth() const { return health; }
    void OnCollisionEnter(Object* other) override;
    virtual void Behaviour() = 0;
};