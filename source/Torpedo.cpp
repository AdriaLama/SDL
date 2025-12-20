#include "Torpedo.h"

void Torpedo::Behaviour()
{
	_physics->AddForce(Vector2(-velocityX, 0.f));
	_physics->SetLinearDrag(10.f);

}


void Torpedo::Update()
{
	Enemy::Update();
	Behaviour();
}

