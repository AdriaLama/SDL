#include "Bullet.h"
#include "Enemy.h"

void Enemy::OnCollisionEnter(Object* object)
{
	Bullet* bullet = dynamic_cast<Bullet*>(object);

	if (bullet != nullptr) {
		Destroy();
	}
}
