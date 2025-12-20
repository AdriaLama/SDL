#include "PowerUp.h"
#include "RenderManager.h"
#include <cmath>

PowerUp::PowerUp(Vector2 position, PowerUpType type)
    : ImageObject(GetTexturePathForType(type), GetSourceOffsetForType(type), Vector2(64.f, 64.f)),
    _type(type),
    _chargeLevel(0),
    _maxCharges(GetMaxChargesForType(type)),
    _isFullyCharged(false),
    _despawnTimer(0.f),
    _pulseTimer(0.f),
    _originalScale(1.0f)
{
    _transform->position = position;
    _transform->scale = Vector2(_originalScale, _originalScale);
    _physics->SetLinearDrag(2.0f);
}

void PowerUp::Update() {
    Object::Update();
    _despawnTimer += TM.GetDeltaTime();
    if (_despawnTimer >= _maxDespawnTime) {
        Destroy();
        return;
    }
  
    _physics->AddForce(Vector2(-50.f, 0.f));

    if (_transform->position.x < -100.f) {
        Destroy();
    }
}

void PowerUp::OnHit() {
    _chargeLevel++;  
    _despawnTimer = 0.f;  
    _transform->scale = Vector2(_originalScale * 1.3f, _originalScale * 1.3f);

    if (_chargeLevel >= _maxCharges) {
        _isFullyCharged = true;
    }
}

void PowerUp::ApplyPowerUp(Player* player) {
    if (!_isFullyCharged || !player) return;

    switch (_type) {
    case PowerUpType::SCORE_BONUS:
        player->AddScore(1000);
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
    Destroy();
}

std::string PowerUp::GetTexturePathForType(PowerUpType type) {
    switch (type) {
    case PowerUpType::SCORE_BONUS:
        return "resources/enemy.png";
    case PowerUpType::CANNON_ENERGY:
        return "resources/enemy.png";
    case PowerUpType::LASER_ENERGY:
        return "resources/enemy.png";
    case PowerUpType::ENGINE_BOOST:
        return "resources/enemy.png";
    case PowerUpType::TWIN_TURRETS:
        return "resources/enemy.png";
    case PowerUpType::SHIELD_ENERGY:
        return "resources/enemy.png";
    default:
        
    }
}

Vector2 PowerUp::GetSourceOffsetForType(PowerUpType type) {
    return Vector2(0.f, 0.f);
}

int PowerUp::GetMaxChargesForType(PowerUpType type) {

    switch (type) {
    case PowerUpType::SCORE_BONUS:
        return 1; 
    case PowerUpType::SHIELD_ENERGY:
        return 3;
    case PowerUpType::CANNON_ENERGY:
        return 5;
    case PowerUpType::LASER_ENERGY:
        return 5;
    case PowerUpType::ENGINE_BOOST:
        return 7;
    case PowerUpType::TWIN_TURRETS:
        return 10; 
    default:
        return 5;
    }
}