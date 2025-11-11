#include "ImageObject.h"
#include "RenderManager.h"
#include "InputManager.h"

class TestObject : public ImageObject
{
public:
	TestObject()
		: ImageObject("resources/image.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f))
	{

		Vector2 randomPosition = Vector2(rand() % RM->WINDOW_WIDTH, rand() % RM->WINDOW_HEIGHT);
		_transform->position = randomPosition;
		_transform->scale = Vector2(0.5f, 0.5f);
		_transform->rotation = 180.f;
		_physics->SetLinearDrag(0.1f);
		_physics->SetAngularDrag(1.1f);
	}

	void Update() override
	{
		if (IM->GetEvent(SDLK_S, DOWN))
		{
			_physics->AddForce(Vector2(0.f, 0.01f));
		}
		
		else if (IM->GetEvent(SDLK_R, HOLD))
		{
			_physics->AddTorque(200.f);
		}
		
		Object::Update();
	}
};