#include "PowerUp.h"
#include "GameManager.h"
#include "Spawner.h"
#include "Bullet.h"
#include <cmath>
#include "ScoreManager.h"

PowerUp::PowerUp(Vector2 position, PowerUpType type)
    : ImageObject(GetTexturePathForType(type), GetSourceOffsetForType(type), Vector2(64.f, 64.f)),
    _type(type),
    _chargeLevel(0),
    _maxCharges(GetMaxChargesForType(type)),
    _isFullyCharged(false),
    _despawnTimer(0.f),
    _pulseTimer(0.f),
    _originalScale(1.0f),
    _rotationSpeed(50.f)
{
    _transform->position = position;
    _transform->scale = Vector2(_originalScale, _originalScale);
    AABB* collider = new AABB(_transform->position, Vector2(64.f, 64.f));
    _physics->AddCollider(collider);
    UpdateSpriteForChargeLevel();
}

void PowerUp::Update()
{
    _despawnTimer += TM.GetDeltaTime();
    if (_despawnTimer >= _maxDespawnTime && !_isFullyCharged)
    {
        Destroy();
        return;
    }

    if (_isFullyCharged)
    {
        _pulseTimer += TM.GetDeltaTime() * 3.f;
        float pulse = 1.0f + sin(_pulseTimer) * 0.15f;
        _transform->scale = Vector2(_originalScale * pulse, _originalScale * pulse);
    }

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
    if (other == player && _isFullyCharged)
    {
        ApplyPowerUp(player);
        Destroy();
    }
}

void PowerUp::OnHit()
{
    if (_isFullyCharged)
        return;

    _chargeLevel++;

    if (_chargeLevel >= _maxCharges)
    {
        _chargeLevel = _maxCharges;
        _isFullyCharged = true;
        _originalScale = 1.3f; 
    }

    UpdateSpriteForChargeLevel();
}

void PowerUp::ApplyPowerUp(Player* player)
{
    if (!player)
        return;

    switch (_type)
    {
    case PowerUpType::SCORE_BONUS:
        HUD_MANAGER.AddScore(500);
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

int PowerUp::GetMaxChargesForType(PowerUpType type)
{
    
    switch (type)
    {
    case PowerUpType::SCORE_BONUS:
        return 1; 
    case PowerUpType::CANNON_ENERGY:
        return 2; 
    case PowerUpType::LASER_ENERGY:
        return 3; 
    case PowerUpType::ENGINE_BOOST:
        return 4; 
    case PowerUpType::TWIN_TURRETS:
        return 5; 
    case PowerUpType::SHIELD_ENERGY:
        return 6; 
    default:
        return 5;
    }
}

void PowerUp::UpdateSpriteForChargeLevel()
{
    if (_renderer)
    {
        float chargePercent = (float)_chargeLevel / (float)_maxCharges;
        Uint8 brightness = (Uint8)(100 + 155 * chargePercent);

        if (_isFullyCharged)
        {
            _renderer->SetColor({ 100, 255, 100, 255 });
        }
        else
        {           
            _renderer->SetColor({ brightness, brightness, brightness, 255 });
        }
    }
}