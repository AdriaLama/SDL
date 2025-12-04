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
		: ImageObject("resources/backgroundGameplay.png", Vector2(0.f, 0.f), Vector2(1360.f, 768.f))
	{
		_transform->position = Vector2(startX, 384.f); 
		_transform->scale = Vector2(15.f, 15.f); 
		_transform->rotation = 0.f;
	}

	void Update() override
	{
		_transform->position.x -= _scrollSpeed * TM.GetDeltaTime();

		
		if (_transform->position.x <= 0) 
		{
			_transform->position.x += 1360.f;
		}

		Object::Update();
	}
};