#include "Bullet.h"
#include "Enemy.h"

void Bullet::OnCollisionEnter(Object* object)
{
	Enemy* enemy = dynamic_cast<Enemy*>(object);

	if (enemy != nullptr) {
			Destroy();
	}
}
