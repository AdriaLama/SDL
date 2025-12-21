#pragma once
#include "ImageObject.h"
#include "RenderManager.h"
#include "InputManager.h"

enum class BulletType
{
    NORMAL,
    CANNON,
    LASER
};

class Bullet : public ImageObject
{
private:
    Vector2 _spawnOffset = Vector2(50.f, 0.f);
    BulletType _bulletType;

public:
    Bullet(Vector2 playerPosition, BulletType type = BulletType::NORMAL)
        : ImageObject(GetBulletSprite(type), Vector2(0.f, 0.f), Vector2(250.f, 250.f)),
        _bulletType(type)
    {
        _transform->position = playerPosition + _spawnOffset;
        _transform->scale = GetBulletScale(type);
        _physics->SetLinearDrag(10.f);
        _physics->SetAngularDrag(0.5f);
        Vector2 colliderSize = Vector2(_transform->size);
        AABB* bulletCollider = new AABB(_transform->position, colliderSize);
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

    BulletType GetBulletType() const { return _bulletType; }

private:
    static const char* GetBulletSprite(BulletType type)
    {
        switch (type)
        {
        case BulletType::CANNON:
            return "resources/cannon.png";
        case BulletType::LASER:
            return "resources/laser.png";
        case BulletType::NORMAL:
        default:
            return "resources/bullet.png";
        }
    }

    static Vector2 GetBulletScale(BulletType type)
    {
        switch (type)
        {
        case BulletType::CANNON:
            return Vector2(0.2f, 0.2f);
        case BulletType::LASER:
            return Vector2(0.3f, 0.3f);
        case BulletType::NORMAL:
        default:
            return Vector2(0.5f, 0.5f);
        }
    }
};