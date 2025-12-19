#include "HorizontalMedusa.h"

void HorizontalMedusa::Behaviour()
{
	_physics->AddForce(Vector2(-velocityX, 0.f));
	_physics->SetLinearDrag(10.f);

}


void HorizontalMedusa::Update()
{
	Enemy::Update();
	Enemy::Update();
	Behaviour();
}

