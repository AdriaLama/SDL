#pragma once
#include "Scene.h"
#include "Player.h"
#include "BackgroundGameplay.h"
#include "TestObject.h"
#include "TextObject.h"

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
		
	}
	
		void OnExit() override { Scene::OnExit(); }
	
	    void Update() override { Scene::Update(); }
	
		void Render() override { Scene::Render(); }
};