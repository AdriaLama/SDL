#include "Missiles.h"

void Missiles::Behaviour()
{
	_physics->AddForce(Vector2(-velocityX, 0.f));
	_physics->SetLinearDrag(10.f);

}


void Missiles::Update()
{
	Enemy::Update();
	Behaviour();
}

