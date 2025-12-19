#pragma once
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Bubble.h"
#include "KillerWhale.h"
#include "BackgroundGameplay.h"
#include "GameManager.h"
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
		Player* player = new Player();
		GAME_MANAGER.SetPlayer(player); 
		SPAWNER.SpawnObjects((Object*)player);  

		
		
		SPAWNER.SpawnObjects(new KillerWhale(Vector2(RM->WINDOW_WIDTH - 700.f , RM->WINDOW_HEIGHT - 50.f)));
		SPAWNER.SpawnObjects(new KillerWhale(Vector2(RM->WINDOW_WIDTH - 300.f ,  50.f)));
		AM->PlaySound("resources/audio/sfx/defeat.wav");
		AM->PlaySound("resources/audio/music/froggerSong.wav");
		
		
	}
	
		void OnExit() override { Scene::OnExit(); }
	
	    void Update() override { Scene::Update(); }
	
		void Render() override { Scene::Render(); }
};