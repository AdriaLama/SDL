#pragma once
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Bubble.h"
#include "Circler.h"
#include "KillerWhale.h"
#include "BackgroundGameplay.h"
#include "GameManager.h"
#include "TestObject.h"
#include "TextObject.h"
#include "AudioManager.h"
#include "HorizontalMedusa.h"

class Gameplay : public Scene
{
public:
	Gameplay() = default;
	
	void OnEnter() override
	{
		srand(time(nullptr));

		BackgroundGameplay* background1 = new BackgroundGameplay(0.f);  
		BackgroundGameplay* background2 = new BackgroundGameplay(680.f); 
		_objects.push_back(background1);
		_objects.push_back(background2);
		Player* player = new Player();
		GAME_MANAGER.SetPlayer(player); 
		SPAWNER.SpawnObjects((Object*)player);  

		
		

		for (int i = 1; i <= 6; i++) 
		{ 
			if (i == 1) {
				SPAWNER.SpawnObjects(new Circler(Vector2(500.f, 0.f), Vector2(100.f, 100.f)));
			}
		
			SPAWNER.SpawnObjects(new Circler(Vector2(500.f, 0.f - (i * 60.f)), Vector2(50.f, 50.f)));
		}
	

		AM->PlaySound("resources/audio/sfx/defeat.wav");
		AM->PlaySound("resources/audio/music/froggerSong.wav");
		
		
	}
	
		void OnExit() override { Scene::OnExit(); }
	
	    void Update() override { Scene::Update(); }
	
		void Render() override { Scene::Render(); }
};