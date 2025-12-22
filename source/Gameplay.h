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
		BackgroundGameplay* background1 = new BackgroundGameplay(0.f);
		BackgroundGameplay* background2 = new BackgroundGameplay(680.f);
		_objects.push_back(background1);
		_objects.push_back(background2);

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

		// Audio
		AM->PlaySound("resources/audio/sfx/defeat.wav");
		AM->PlaySound("resources/audio/music/froggerSong.wav");
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