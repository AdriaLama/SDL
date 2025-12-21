#include "Bullet.h"
#include "Enemy.h"
#include "PowerUp.h"

void Bullet::OnCollisionEnter(Object* object)
{

    Enemy* enemy = dynamic_cast<Enemy*>(object);
    if (enemy != nullptr) {
        Destroy();
        return;
    }

    PowerUp* powerup = dynamic_cast<PowerUp*>(object);
    if (powerup != nullptr) {
       
        Destroy();
        return;
    }
}