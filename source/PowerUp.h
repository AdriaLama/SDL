#pragma once
#include "ImageObject.h"
#include "Player.h"
#include "TimeManager.h"

enum class PowerUpType {
    SCORE_BONUS,
    CANNON_ENERGY,
    LASER_ENERGY,
    ENGINE_BOOST,  
    SHIELD_ENERGY,
    TWIN_TURRETS,
    COUNT // Para saber cuántos tipos hay
};

class PowerUp : public ImageObject {
private:
    PowerUpType _type;
    float _despawnTimer;
    const float _maxDespawnTime = 15.0f;
    float _pulseTimer;
    float _originalScale;
    float _rotationSpeed;

public:
    PowerUp(Vector2 position, PowerUpType type = PowerUpType::SCORE_BONUS);
    void Update() override;
    void OnCollisionEnter(Object* other) override;
    void OnHit();
    void ApplyPowerUp(Player* player);
    void CycleToNextType();
    PowerUpType GetType() const { return _type; }

    // Ya no se usa GetRandomType() - lo elimino o lo dejo deprecado
    // static PowerUpType GetRandomType();

private:
    std::string GetTexturePathForType(PowerUpType type);
    Vector2 GetSourceOffsetForType(PowerUpType type);
    void UpdateSpriteForType();
};