#pragma once
#include "ImageObject.h"
#include "Bullet.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Spawner.h"

class Player : public ImageObject
{
private:
	float _shootCooldown = 0.3f;
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
	float _movementSpeedMultiplier;	
	float _turretAngle;
	float _distanceTravelled;
	float _lastXPosition;
	bool _isImmune;
	float _immunityTimer;
	const float _immunityDuration = 0.5f;


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
		_cannonEnergy(100.f),
		_laserEnergy(100.f),
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
	}

	void Update() override
	{
		if (_currentCooldown > 0.f)
		{
			_currentCooldown -= TM.GetDeltaTime();
		}
		if (IM->GetEvent(SDLK_W, HOLD) && _transform->position.y > 0)
		{
			_physics->AddForce(Vector2(0.f, -3000.f));
		}
		if (IM->GetEvent(SDLK_A, HOLD) && _transform->position.x > 0)
		{
			_physics->AddForce(Vector2(-3000.f, 0.f));
		}
		if (IM->GetEvent(SDLK_S, HOLD) && _transform->position.y < RM->WINDOW_HEIGHT)
		{
			_physics->AddForce(Vector2(0.f, 3000.f));
		}
		if (IM->GetEvent(SDLK_D, HOLD) && _transform->position.x < RM->WINDOW_WIDTH)
		{
			_physics->AddForce(Vector2(3000.f, 0.f));
		}
		if (IM->GetEvent(SDLK_SPACE, DOWN) && _currentCooldown <= 0.f)
		{
			SPAWNER.SpawnObjects(new Bullet(_transform->position));
			_currentCooldown = _shootCooldown;
		}

		Object::Update();
		ClampPosition();
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
		SPAWNER.SpawnObjects(new Bullet(spawnPos));	

		if (_hasCannons && _cannonEnergy > 0.f)
		{
			Vector2 cannonOffset = Vector2(0.f, 20.f);
			SPAWNER.SpawnObjects(new Bullet(spawnPos + cannonOffset));
			SPAWNER.SpawnObjects(new Bullet(spawnPos - cannonOffset));
			_cannonEnergy -= 0.5f;
		}
	
		if (_hasLaser && _laserEnergy > 0.f)
		{
			Vector2 laserOffset = Vector2(0.f, 30.f);
			SPAWNER.SpawnObjects(new Bullet(spawnPos + laserOffset)); 
			_laserEnergy -= 1.0f;
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

		SPAWNER.SpawnObjects(new Bullet(turretPos1));
		SPAWNER.SpawnObjects(new Bullet(turretPos2));
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
		}
	}

};