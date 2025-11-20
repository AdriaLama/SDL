#pragma once
#include "Scene.h"
#include "TestObject.h"

class Gameplay : public Scene
{
public:
	Gameplay() = default;
	
	void OnEnter() override
	{
		TestObject* test1 = new TestObject();
		_objects.push_back(test1);
		TestObject* test2 = new TestObject();
		_objects.push_back(test2);
		
	}
	
		void OnExit() override { Scene::OnExit(); }
	
	    void Update() override { Scene::Update(); }
	
		void Render() override { Scene::Render(); }
};