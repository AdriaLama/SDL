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
    UpdateSpriteForType();
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

    _transform->rotation += _rotationSpeed * TM.GetDeltaTime();
    if (_transform->rotation >= 360.f)
        _transform->rotation -= 360.f;

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

        UpdateSpriteForType();
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

// Método GetRandomType() ELIMINADO - ya no es necesario

std::string PowerUp::GetTexturePathForType(PowerUpType type)
{
    return "resources/image.png";
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

void PowerUp::UpdateSpriteForType()
{
    if (_renderer)
    {
        switch (_type)
        {
        case PowerUpType::SCORE_BONUS:
            _renderer->SetColor({ 255, 215, 0, 255 });
            break;
        case PowerUpType::CANNON_ENERGY:
            _renderer->SetColor({ 255, 100, 100, 255 });
            break;
        case PowerUpType::LASER_ENERGY:
            _renderer->SetColor({ 100, 100, 255, 255 });
            break;
        case PowerUpType::ENGINE_BOOST:
            _renderer->SetColor({ 255, 165, 0, 255 });
            break;
        case PowerUpType::TWIN_TURRETS:
            _renderer->SetColor({ 200, 100, 255, 255 });
            break;
        case PowerUpType::SHIELD_ENERGY:
            _renderer->SetColor({ 100, 255, 100, 255 });
            break;
        }
    }
}