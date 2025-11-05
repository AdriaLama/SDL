#include "ImageObject.h"
#include "RenderManager.h"

class TestObject : public ImageObject
{
public:
	TestObject()
		: ImageObject("resources/image.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f))
	{

		Vector2 randomPosition = Vector2(rand() % RM->WINDOW_WIDTH, rand() % RM->WINDOW_HEIGHT);
		_transform->position = randomPosition;
		_transform->scale = Vector2(0.5f, 0.5f);
		_transform->rotation = 30.f;
	}
};