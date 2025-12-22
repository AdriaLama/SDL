#pragma once
#include "ImageObject.h"
#include "RenderManager.h"
#include "TimeManager.h"

class BackgroundGameplay : public ImageObject
{
private:
    float _scrollSpeed = 100.f;

public:
    BackgroundGameplay(float startX)
        : ImageObject("resources/backgroundGameplay.png", Vector2(0.f, 0.f), Vector2(0.0f, 0.0f))
    {
        _transform->position = Vector2(startX + RM->WINDOW_WIDTH / 2.f, 384.f);
        _transform->scale = Vector2(15.f, 15.f); 
        _transform->rotation = 0.f;
    }

    void Update() override
    {
        _transform->position.x -= _scrollSpeed * TM.GetDeltaTime();

        if (_transform->position.x <= -(RM->WINDOW_WIDTH / 2.f))
        {
            _transform->position.x += RM->WINDOW_WIDTH * 2.f;
        }

        Object::Update();
    }
};