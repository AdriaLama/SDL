#include "Bullet.h"
#include "Enemy.h"
#include "PowerUp.h"

void Bullet::Update()
{
    DestroyBullet();
 
    if (_useCustomDirection)
    {
        _physics->AddForce(_direction * 4000.f);
    }
    else
    {
        _physics->AddForce(Vector2(4000.f, 0.f));
    }
    Object::Update();
}

void Bullet::DestroyBullet()
{
   
    if (_transform->position.x >= RM->WINDOW_WIDTH ||
        _transform->position.x <= 0 ||
        _transform->position.y >= RM->WINDOW_HEIGHT ||
        _transform->position.y <= 0)
    {
        Destroy();
    }
}

void Bullet::OnCollisionEnter(Object* object)
{
    Enemy* enemy = dynamic_cast<Enemy*>(object);
    if (enemy != nullptr)
    {
        Destroy();
        return;
    }

    PowerUp* powerup = dynamic_cast<PowerUp*>(object);
    if (powerup != nullptr)
    {
        Destroy();
        return;
    }
}