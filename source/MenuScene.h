#pragma once
#include "Scene.h"
#include "TextObject.h"

class MenuScene : public Scene
{
public:
	MenuScene() = default;

	void OnEnter() override
	{
		
		TextObject* textMenu = new TextObject("MENU");
		textMenu->GetTransform()->position = { 775.f, 500.f };
		textMenu->GetTransform()-> scale = { 5.f, 5.f };
		_ui.push_back(textMenu);
		TextObject* textPressSpace = new TextObject("Press 'Space' to continue...");
		textPressSpace->GetTransform()->position = { 550.f, 500.f };
		textPressSpace->GetTransform()->scale = { 1.f, 1.f };
		_ui.push_back(textPressSpace);
	}

	void OnExit() override { Scene::OnExit(); }

	void Update() override { 
		
		if (IM->GetEvent(SDLK_SPACE, DOWN))
		{
			SM.SetNextScene("Gameplay");
		}

		Scene::Update(); 
	}

	void Render() override { Scene::Render(); }
};