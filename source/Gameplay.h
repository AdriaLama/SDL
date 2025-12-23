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
#include "SceneManager.h"

class Gameplay : public Scene
{
private:
	bool victoryMessageShown = false;
	float victoryTimer = 0.0f;
	const float victoryDelay = 3.0f; 
	TextObject* victoryText = nullptr;

public:
	Gameplay() = default;

	void OnEnter() override
	{
		srand(time(nullptr));
		AM->Init();

		
		victoryMessageShown = false;
		victoryTimer = 0.0f;
		victoryText = nullptr;

		
		BackgroundGameplay* bg1 = new BackgroundGameplay(0.f);
		BackgroundGameplay* bg2 = new BackgroundGameplay(1360.f);
		_objects.push_back(bg1);
		_objects.push_back(bg2);

		
		Player* player = new Player();
		GAME_MANAGER.SetPlayer(player);
		SPAWNER.SpawnObjects((Object*)player);

		
		HUD_MANAGER.Initialize();
		_objects.push_back(HUD_MANAGER.GetScoreText());
		_objects.push_back(HUD_MANAGER.GetHighScoreText());
		_objects.push_back(HUD_MANAGER.GetShieldText());
		_objects.push_back(HUD_MANAGER.GetCannonText());
		_objects.push_back(HUD_MANAGER.GetLaserText());

		
		std::string currentLevel = WAVE_MANAGER.GetCurrentLevel();
		if (currentLevel.empty() || currentLevel == "lvl1.xml")
		{
			WAVE_MANAGER.LoadLevel("lvl1.xml");
		}
		else if (currentLevel == "lvl2.xml")
		{
			WAVE_MANAGER.LoadLevel("lvl2.xml");
		}
		else
		{
			
			WAVE_MANAGER.LoadLevel("lvl1.xml"); 
		}

		AM->PlaySound("resources/436507__doctor_dreamchip__2018-08-02.wav");
	}

	void OnExit() override
	{
		if (victoryText)
		{
			delete victoryText;
			victoryText = nullptr;
		}
		Scene::OnExit();
	}

	void Update() override
	{
		
		if (WAVE_MANAGER.IsLevelCompleted() && !victoryMessageShown)
		{
			victoryMessageShown = true;
			AM->PlaySound("resources/270333__littlerobotsoundfactory__jingle_win_00.wav");
			
		}

		
		if (victoryMessageShown)
		{
			victoryTimer += TM.GetDeltaTime();

			if (victoryTimer >= victoryDelay)
			{
				
				std::string currentLevel = WAVE_MANAGER.GetCurrentLevel();

				if (currentLevel == "lvl1.xml")
				{					
					WAVE_MANAGER.ResetLevelCompletion();
					WAVE_MANAGER.LoadLevel("lvl2.xml");
					SM.SetNextScene("Gameplay"); 
				}
				else if (currentLevel == "lvl2.xml")
				{			
					WAVE_MANAGER.ResetLevelCompletion();
					WAVE_MANAGER.LoadLevel("lvl1.xml");
					SM.SetNextScene("Gameplay"); 
				}
			}
		}

		HUD_MANAGER.Update();
		WAVE_MANAGER.Update();
		Scene::Update();
	}

	void Render() override
	{
		Scene::Render();
	}
};