#pragma once
#include "ImageObject.h"
#include "RenderManager.h"
#include "InputManager.h"

class Bullet : public ImageObject
{
private:
	Vector2 _spawnOffset = Vector2(50.f, 0.f);
public:
	Bullet(Vector2 playerPosition)
		: ImageObject("resources/bullet.png", Vector2(0.f, 0.f), Vector2(250.f, 250.f))
	{
		_transform->position = playerPosition + _spawnOffset;
		_transform->scale = Vector2(0.5f, 0.5f);

		_physics->SetLinearDrag(10.f);
		_physics->SetAngularDrag(0.5f);
		Vector2 colliderSize = Vector2(10.0f, 10.0f); 
		AABB* bulletCollider = new AABB(Vector2(0.f, 0.f), colliderSize);
		_physics->AddCollider(bulletCollider);
	}

	void Update() override
	{
		DestroyBullet();
		_physics->AddForce(Vector2(3000.f, 0.f));
		Object::Update();
	}

	void DestroyBullet() {
		if (_transform->position.x >= RM->WINDOW_WIDTH) {
			Destroy();
		}
	}

	void OnCollisionEnter(Object* object) override;
};