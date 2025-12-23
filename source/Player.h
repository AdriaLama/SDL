#pragma once
#include "ImageObject.h"
#include "Bullet.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Spawner.h"
#include "Enemy.h"
#include "BioTitanBullets.h"
#include "AudioManager.h"


class Player : public ImageObject
{
private:
	float _shootCooldown = 0.2f;
	float _currentCooldown;
	int _shields;
	int _maxShields;
	int _score;
	bool _hasTwinTurrets;
	bool _hasCannons;
	bool _hasLaser;
	float _cannonEnergy;
	float _laserEnergy;
	float _maxCannonEnergy;
	float _maxLaserEnergy;
	const float _cannonEnergyConsumption = 2.0f;
	const float _laserEnergyConsumption = 3.0f;
	float _movementSpeedMultiplier;
	float _turretAngle;
	float _distanceTravelled;
	float _lastXPosition;
	bool _isImmune;
	float _immunityTimer;
	const float _immunityDuration = 0.2f;
	const int _damagePerHit = 5;

public:
	Player()
		: ImageObject("resources/player.png", Vector2(0.f, 0.f), Vector2(500.f, 500.f)),
		_currentCooldown(0.f),
		_shields(100),
		_maxShields(100),
		_score(0),
		_hasTwinTurrets(false),
		_hasCannons(false),
		_hasLaser(false),
		_cannonEnergy(0.f),
		_laserEnergy(0.f),
		_maxCannonEnergy(100.f),
		_maxLaserEnergy(100.f),
		_movementSpeedMultiplier(1.0f),
		_turretAngle(0.f),
		_distanceTravelled(0.f),
		_lastXPosition(0.f),
		_isImmune(false),
		_immunityTimer(0.f)
	{
		Vector2 beginPosition = Vector2(RM->WINDOW_WIDTH / 5.f, RM->WINDOW_HEIGHT / 2.f);
		_transform->position = beginPosition;
		_transform->scale = Vector2(1.f, 1.f);
		_physics->SetLinearDrag(10.f);
		_physics->SetAngularDrag(0.5f);

		Vector2 colliderSize = Vector2(_transform->size.x * 0.8f, _transform->size.y * 0.8f);
		AABB* playerCollider = new AABB(_transform->position, colliderSize);
		_physics->AddCollider(playerCollider);

		_lastXPosition = _transform->position.x;
	}

	void Update() override
	{

		if (_isImmune)
		{
			_immunityTimer += TM.GetDeltaTime();
			if (_immunityTimer >= _immunityDuration)
			{
				_isImmune = false;
				_immunityTimer = 0.f;
			}
		}

		if (_hasCannons && _cannonEnergy <= 0.f)
		{
			_hasCannons = false;
		}
		if (_hasLaser && _laserEnergy <= 0.f)
		{
			_hasLaser = false;
		}

		if (_currentCooldown > 0.f)
		{
			_currentCooldown -= TM.GetDeltaTime();
		}


		float speed = 3000.f * _movementSpeedMultiplier;

		if (IM->GetEvent(SDLK_W, HOLD) && _transform->position.y > 0)
		{
			_physics->AddForce(Vector2(0.f, -speed));
		}
		if (IM->GetEvent(SDLK_A, HOLD) && _transform->position.x > 0)
		{
			_physics->AddForce(Vector2(-speed, 0.f));
		}
		if (IM->GetEvent(SDLK_S, HOLD) && _transform->position.y < RM->WINDOW_HEIGHT)
		{
			_physics->AddForce(Vector2(0.f, speed));
		}
		if (IM->GetEvent(SDLK_D, HOLD) && _transform->position.x < RM->WINDOW_WIDTH)
		{
			_physics->AddForce(Vector2(speed, 0.f));
		}
		if (IM->GetEvent(SDLK_SPACE, DOWN) && _currentCooldown <= 0.f)
		{
			Shoot();
			AM->PlaySound("resources/455911__bolkmar__machine-gun-shoot-only.wav");
			_currentCooldown = _shootCooldown;
		}

		UpdateTurretRotation();
		Object::Update();
		ClampPosition();
	}

	void OnCollisionEnter(Object* other) override
	{
		Enemy* enemy = dynamic_cast<Enemy*>(other);
		BioTitanBullets* bioTitanBullets = dynamic_cast<BioTitanBullets*>(other);
	
		if (enemy != nullptr || bioTitanBullets != nullptr && !_isImmune)
		{
			TakeDamage(_damagePerHit);
		}
	}

	void TakeDamage(int damage)
	{
		if (_isImmune) return;

		_shields -= damage;
		_isImmune = true;
		_immunityTimer = 0.f;

		if (_shields <= 0)
		{
			_shields = 0;
			OnPlayerDeath();
		}
	}
	void OnPlayerDeath()
	{
		Destroy();
	}
	void ReplenishCannonEnergy() {
		_cannonEnergy = _maxCannonEnergy;
		_hasCannons = true;
	}
	void ReplenishLaserEnergy() {
		_laserEnergy = _maxLaserEnergy;
		_hasLaser = true;
	}
	void UpgradeEngines() {
		_movementSpeedMultiplier += 0.2f;
	
		if (_movementSpeedMultiplier > 2.5f) {
			_movementSpeedMultiplier = 2.5f;
		}
	}

	void EnableTwinTurrets() {
		_hasTwinTurrets = true;
	}

	void ReplenishShields() {
		_shields = _maxShields;
	}

	void AddScore(int amount) { _score += amount; }
	int GetScore() const { return _score; }
	int GetShields() const { return _shields; }
	int GetMaxShields() const { return _maxShields; }
	bool IsImmune() const { return _isImmune; }
	float GetCannonEnergy() const { return _cannonEnergy; }
	float GetLaserEnergy() const { return _laserEnergy; }
	float GetMaxCannonEnergy() const { return _maxCannonEnergy; }
	float GetMaxLaserEnergy() const { return _maxLaserEnergy; }
	bool HasCannons() const { return _hasCannons; }
	bool HasLaser() const { return _hasLaser; }
	bool HasTwinTurrets() const { return _hasTwinTurrets; }
	float GetMovementSpeedMultiplier() const { return _movementSpeedMultiplier; }

private:
	void ClampPosition()
	{
		if (_transform->position.x < 0)
			_transform->position.x = 0;
		else if (_transform->position.x > RM->WINDOW_WIDTH)
			_transform->position.x = RM->WINDOW_WIDTH;

		if (_transform->position.y < 0)
			_transform->position.y = 0;
		else if (_transform->position.y > RM->WINDOW_HEIGHT)
			_transform->position.y = RM->WINDOW_HEIGHT;
	}

	void Shoot()
	{
		Vector2 spawnPos = _transform->position;
		SPAWNER.SpawnObjects(new Bullet(spawnPos, BulletType::NORMAL));

		if (_hasCannons && _cannonEnergy >= _cannonEnergyConsumption)
		{
			Vector2 cannonOffset = Vector2(0.f, 20.f);
			SPAWNER.SpawnObjects(new Bullet(spawnPos + cannonOffset, BulletType::CANNON));
			_cannonEnergy -= _cannonEnergyConsumption;
		}

		if (_hasLaser && _laserEnergy >= _laserEnergyConsumption)
		{
			Vector2 laserOffset = Vector2(0.f, 30.f);
			SPAWNER.SpawnObjects(new Bullet(spawnPos - laserOffset, BulletType::LASER));
			_laserEnergy -= _laserEnergyConsumption;
		}

		if (_hasTwinTurrets)
		{
			ShootTurrets();
		}
	}

	void ShootTurrets()
	{
		Vector2 turretOffset = Vector2(-40.f, 0.f);
		Vector2 turretPos1 = _transform->position + turretOffset + Vector2(0.f, -25.f);
		Vector2 turretPos2 = _transform->position + turretOffset + Vector2(0.f, 25.f);

		float radians = _turretAngle * (3.14159f / 180.f);
		Vector2 direction = Vector2(cos(radians), sin(radians));

		Bullet* turretBullet1 = new Bullet(turretPos1);
		Bullet* turretBullet2 = new Bullet(turretPos2);

		SPAWNER.SpawnObjects(turretBullet1);
		SPAWNER.SpawnObjects(turretBullet2);
	}

	void UpdateTurretRotation()
	{
		if (!_hasTwinTurrets) return;

		float deltaX = _transform->position.x - _lastXPosition;
		_distanceTravelled += abs(deltaX);
		_lastXPosition = _transform->position.x;

		if (_distanceTravelled >= 100.f)
		{
			_turretAngle += (deltaX > 0 ? -45.f : 45.f);
			_distanceTravelled = 0.f;
			while (_turretAngle < 0.f) _turretAngle += 360.f;
			while (_turretAngle >= 360.f) _turretAngle -= 360.f;
		}
	}
};