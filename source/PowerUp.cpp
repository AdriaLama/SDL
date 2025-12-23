#include "PowerUp.h"
#include "GameManager.h"
#include "Spawner.h"
#include "Bullet.h"
#include <cmath>
#include "ScoreManager.h"
#include <cstdlib>

PowerUp::PowerUp(Vector2 position, PowerUpType type)
    : ImageObject(GetTexturePathForType(type), GetSourceOffsetForType(type), Vector2(64.f, 64.f)),
    _type(type),
    _despawnTimer(0.f),
    _pulseTimer(0.f),
    _originalScale(1.2f),
    _rotationSpeed(50.f)
{
    _transform->position = position;
    _transform->scale = Vector2(_originalScale, _originalScale);
    AABB* collider = new AABB(_transform->position, Vector2(64.f, 64.f));
    _physics->AddCollider(collider);
    UpdateSpriteForType(type);
}

void PowerUp::Update()
{
    _despawnTimer += TM.GetDeltaTime();
    if (_despawnTimer >= _maxDespawnTime)
    {
        Destroy();
        return;
    }

    _pulseTimer += TM.GetDeltaTime() * 3.f;
    float pulse = 1.0f + sin(_pulseTimer) * 0.15f;
    _transform->scale = Vector2(_originalScale * pulse, _originalScale * pulse);

    Object::Update();
}

void PowerUp::OnCollisionEnter(Object* other)
{
    Bullet* bullet = dynamic_cast<Bullet*>(other);
    if (bullet != nullptr)
    {
        OnHit();
        bullet->Destroy();
        return;
    }

    Player* player = GAME_MANAGER.GetPlayer();
    if (other == player)
    {
        ApplyPowerUp(player);
        Destroy();
    }
}

void PowerUp::OnHit()
{
    CycleToNextType();
}

void PowerUp::CycleToNextType()
{
    if (_type != PowerUpType::TWIN_TURRETS)
    {
        int currentType = static_cast<int>(_type);
        currentType = currentType + 1;
        _type = static_cast<PowerUpType>(currentType);

        UpdateSpriteForType(_type);
    }
}

void PowerUp::ApplyPowerUp(Player* player)
{
    if (!player)
        return;

    switch (_type)
    {
    case PowerUpType::SCORE_BONUS:
        HUD_MANAGER.AddScore(1000);
        break;

    case PowerUpType::CANNON_ENERGY:
        player->ReplenishCannonEnergy();
        break;

    case PowerUpType::LASER_ENERGY:
        player->ReplenishLaserEnergy();
        break;

    case PowerUpType::ENGINE_BOOST:
        player->UpgradeEngines();
        break;

    case PowerUpType::TWIN_TURRETS:
        player->EnableTwinTurrets();
        break;

    case PowerUpType::SHIELD_ENERGY:
        player->ReplenishShields();
        break;
    }
}



std::string PowerUp::GetTexturePathForType(PowerUpType type)
{
    return "resources/boss1.png";
}

Vector2 PowerUp::GetSourceOffsetForType(PowerUpType type)
{
    switch (type)
    {
    case PowerUpType::SCORE_BONUS:
        return Vector2(0.f, 0.f);
    case PowerUpType::CANNON_ENERGY:
        return Vector2(64.f, 0.f);
    case PowerUpType::LASER_ENERGY:
        return Vector2(128.f, 0.f);
    case PowerUpType::ENGINE_BOOST:
        return Vector2(192.f, 0.f);
    case PowerUpType::TWIN_TURRETS:
        return Vector2(256.f, 0.f);
    case PowerUpType::SHIELD_ENERGY:
        return Vector2(320.f, 0.f);
    default:
        return Vector2(0.f, 0.f);
    }
}

void PowerUp::UpdateSpriteForType(PowerUpType type)
{
    std::string texturePath;

    switch (type)
    {
    case PowerUpType::SCORE_BONUS:
        texturePath = "resources/powerup1.png";
        break;
    case PowerUpType::CANNON_ENERGY:
        texturePath = "resources/powerup2.png";
        break;
    case PowerUpType::LASER_ENERGY:
        texturePath = "resources/powerup3.png";
        break;
    case PowerUpType::ENGINE_BOOST:
        texturePath = "resources/powerup4.png";
        break;
    case PowerUpType::TWIN_TURRETS:
        texturePath = "resources/powerup5.png";
        break;
    case PowerUpType::SHIELD_ENERGY:
        texturePath = "resources/powerup6.png";
        break;
    default:
        break;
    }

    UpdateTexture(texturePath, Vector2(0.f, 0.f), Vector2(64.f, 64.f));
}