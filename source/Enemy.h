#include "ImageObject.h"
#include "RenderManager.h"
#include "InputManager.h"

class Enemy : public ImageObject
{
public:
	Enemy()
		: ImageObject("resources/enemy.png", Vector2(0.f, 0.f), Vector2(500.f, 500.f))
	{

		Vector2 beginPosition = Vector2(RM->WINDOW_WIDTH / 1.3f, RM->WINDOW_HEIGHT / 2.f);
		_transform->position = beginPosition;
		_transform->scale = Vector2(3.5f, 3.5f);

		_physics->SetLinearDrag(10.f);
		_physics->SetAngularDrag(0.5f);
	}

	void Update() override
	{
		
		Object::Update();
	}

	
};