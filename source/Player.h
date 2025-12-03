#include "ImageObject.h"
#include "RenderManager.h"
#include "InputManager.h"

class Player : public ImageObject
{
public:
	Player()
		: ImageObject("resources/player.png", Vector2(0.f, 0.f), Vector2(500.f, 500.f))
	{

		Vector2 beginPosition = Vector2(RM->WINDOW_WIDTH / 5.f, RM->WINDOW_HEIGHT / 2.f );
		_transform->position = beginPosition;
		_transform->scale = Vector2(1.f, 1.f);
		_transform->rotation = 180.f;

		_physics->SetLinearDrag(10.f);
		_physics->SetAngularDrag(0.5f);
	}

	void Update() override
	{
		if (IM->GetEvent(SDLK_W, HOLD))
		{
			_physics->AddForce(Vector2(0.f, -3000.f));
		}

		if (IM->GetEvent(SDLK_A, HOLD))
		{
			_physics->AddForce(Vector2(-3000.f, 0.f));
		}

		if (IM->GetEvent(SDLK_S, HOLD))
		{
			_physics->AddForce(Vector2(0.f, 3000.f));
		}

		if (IM->GetEvent(SDLK_D, HOLD))
		{
			_physics->AddForce(Vector2(3000.f, 0.f));
		}

		
		Object::Update();
	}
};