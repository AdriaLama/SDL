#pragma once
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Bubble.h"
#include "BackgroundGameplay.h"
#include "TestObject.h"
#include "TextObject.h"
#include "AudioManager.h"

class Gameplay : public Scene
{
public:
	Gameplay() = default;
	
	void OnEnter() override
	{
		BackgroundGameplay* background1 = new BackgroundGameplay(0.f);  
		BackgroundGameplay* background2 = new BackgroundGameplay(680.f); 
		_objects.push_back(background1);
		_objects.push_back(background2);
		SPAWNER.SpawnObjects(new Player());
		
		for (int i = 0; i < 4; i++)
		{
			float delaySpawn = i * 0.5f; 
			SPAWNER.SpawnObjects(new Bubble(Vector2(RM->WINDOW_WIDTH - 100 + (i * 80.f), 200.f)));
		}

		for (int i = 0; i < 4; i++)
		{
			float delay = i * 0.5f;
			SPAWNER.SpawnObjects(new Bubble(Vector2(RM->WINDOW_WIDTH - 100 + (i * 80.f), RM->WINDOW_HEIGHT - 200.f)));
		}

		AM->PlaySound("resources/audio/sfx/defeat.wav");
		AM->PlaySound("resources/audio/music/froggerSong.wav");
		
		
	}
	
		void OnExit() override { Scene::OnExit(); }
	
	    void Update() override { Scene::Update(); }
	
		void Render() override { Scene::Render(); }
};