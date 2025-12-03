#pragma once
#include "Scene.h"
#include "Player.h"
#include "TestObject.h"
#include "TextObject.h"

class Gameplay : public Scene
{
public:
	Gameplay() = default;
	
	void OnEnter() override
	{
		SPAWNER.SpawnObjects(new Player());
	}
	
		void OnExit() override { Scene::OnExit(); }
	
	    void Update() override { Scene::Update(); }
	
		void Render() override { Scene::Render(); }
};