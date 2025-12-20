#pragma once
#include "ImageObject.h"
#include "Player.h"
#include "TimeManager.h"

enum class PowerUpType {
    SCORE_BONUS,      
    CANNON_ENERGY,    
    LASER_ENERGY,     
    ENGINE_BOOST,     
    TWIN_TURRETS,     
    SHIELD_ENERGY     
};

class PowerUp : public ImageObject {
private:
    PowerUpType _type;
    int _chargeLevel;
    int _maxCharges;
    bool _isFullyCharged;
    float _despawnTimer;
    const float _maxDespawnTime = 10.0f; 
    float _pulseTimer;
    float _originalScale;

public:
    PowerUp(Vector2 position, PowerUpType type);

    void Update() override;
    void OnHit(); 
    void ApplyPowerUp(Player* player);
    bool IsFullyCharged() const { return _isFullyCharged; }
    PowerUpType GetType() const { return _type; }

private:

    std::string GetTexturePathForType(PowerUpType type);
    Vector2 GetSourceOffsetForType(PowerUpType type);
    int GetMaxChargesForType(PowerUpType type);
};