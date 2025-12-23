#pragma once
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Bubble.h"
#include "Circler.h"
#include "KillerWhale.h"
#include "Chainsaw.h"
#include "BackgroundGameplay.h"
#include "GameManager.h"
#include "TestObject.h"
#include "TextObject.h"
#include "Torpedo.h"
#include "AudioManager.h"
#include "HorizontalMedusa.h"
#include "ScoreManager.h"
#include "Ufo.h"  
#include "PowerUp.h"
#include "WaveManager.h"

class Gameplay : public Scene
{
public:
	Gameplay() = default;

	void OnEnter() override
	{
		srand(time(nullptr));

		// Setup backgrounds
		BackgroundGameplay* bg1 = new BackgroundGameplay(0.f);      
		BackgroundGameplay* bg2 = new BackgroundGameplay(1360.f);
		_objects.push_back(bg1);
		_objects.push_back(bg2);

		// Setup player
		Player* player = new Player();
		GAME_MANAGER.SetPlayer(player);
		SPAWNER.SpawnObjects((Object*)player);

		// Setup HUD
		HUD_MANAGER.Initialize();
		_objects.push_back(HUD_MANAGER.GetScoreText());
		_objects.push_back(HUD_MANAGER.GetHighScoreText());
		_objects.push_back(HUD_MANAGER.GetShieldText());
		/*_objects.push_back(HUD_MANAGER.GetLivesText());*/
		_objects.push_back(HUD_MANAGER.GetCannonText());
		_objects.push_back(HUD_MANAGER.GetLaserText());

		// Load level with WaveManager
		WAVE_MANAGER.LoadLevel("lvl1.xml");

		AM->LoadSoundsData("resources/455911__bolkmar__machine-gun-shoot-only.wav");
		
		// Audio
		AM->Init();
		
	}

	void OnExit() override
	{
		Scene::OnExit();
	}

	void Update() override
	{
		HUD_MANAGER.Update();
		WAVE_MANAGER.Update();  // Update wave spawning system
		Scene::Update();
	}

	void Render() override
	{
		Scene::Render();
	}
};