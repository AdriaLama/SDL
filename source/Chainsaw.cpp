#include "Chainsaw.h"

void Chainsaw::Behaviour()
{
	if (currentState == SIMPLE_MOVE) {
		if (spawnedLeftChainsaw) {
			if (_transform->position.x < RM->WINDOW_WIDTH / 2.f - 100.f) {
				_physics->AddForce(Vector2(1300.f, 0.f));
				_physics->SetLinearDrag(10.f);
			}
			else {
				_physics->SetVelocity(Vector2(0.f, 0.f));
				currentState = CIRCLE_MOVE;
				circleCenter = Vector2(_transform->position.x + 200.f, _transform->position.y);
				angle = 3.14159f; 
			}
		}
		else {
			if (_transform->position.x > RM->WINDOW_WIDTH / 2.f + 100.f) {
				_physics->AddForce(Vector2(-1300.f, 0.f));
				_physics->SetLinearDrag(10.f);
			}
			else {
				_physics->SetVelocity(Vector2(0.f, 0.f));
				currentState = CIRCLE_MOVE;
				circleCenter = Vector2(_transform->position.x - 200.f, _transform->position.y);
				angle = 0.f; 
			}
		}
	}

	if (currentState == CIRCLE_MOVE) {
		float radius = 200.f;

		if (spawnedLeftChainsaw) {
			float speed = 1.5f;
			angle += speed * TM.GetDeltaTime();
			_transform->position.x = circleCenter.x + cos(angle) * radius;
			_transform->position.y = circleCenter.y + sin(angle) * radius;

			if (angle >= 3.14159f + 6.28f) 
			{
				
				currentState = RETURN;
			}
		}
		else {
			float speed = 1.5f;
			angle += speed * TM.GetDeltaTime();
			_transform->position.x = circleCenter.x + cos(angle) * radius;
			_transform->position.y = circleCenter.y + sin(angle) * radius;

			if (angle >= 6.28f) 
			{
				
				currentState = RETURN;
			}
		}
	}

	if (currentState == RETURN) {
		if (spawnedLeftChainsaw) {
			_physics->AddForce(Vector2(-1300.f, 0.f));
			_physics->SetLinearDrag(10.f);
		}
		else {
			_physics->AddForce(Vector2(1300.f, 0.f));
			_physics->SetLinearDrag(10.f);
		}
	}
}

void Chainsaw::Update()
{
	Enemy::Update();
	Behaviour();
}