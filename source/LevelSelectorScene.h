#pragma once
#include "Scene.h"
#include "Button.h"
#include "TextObject.h"
#include "SceneManager.h"
#include "WaveManager.h"
#include "AudioManager.h"

class LevelSelectorScene : public Scene
{
private:
    TextObject* _titleText;
    Button* _level1Button;
    Button* _level2Button;
    Button* _backButton;
    TextObject* _level1Text;
    TextObject* _level2Text;
    TextObject* _backText;

public:
    LevelSelectorScene()
        : _titleText(nullptr),
        _level1Button(nullptr),
        _level2Button(nullptr),
        _backButton(nullptr),
        _level1Text(nullptr),
        _level2Text(nullptr),
        _backText(nullptr)
    {
    }

    void OnEnter() override
    {
        
        _titleText = new TextObject("SELECT LEVEL");
        _titleText->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2.0f - 100.f, 300.f);
        _titleText->GetTransform()->scale = Vector2(4.f, 4.f);
        _titleText->GetRenderer()->SetColor({ 0, 255, 255, 255 });
        _ui.push_back(_titleText);

        
        float buttonWidth = 400.f;
        float buttonHeight = 80.f;
        float centerX = RM->WINDOW_WIDTH / 2.0f - buttonWidth / 2.0f;
        float startY = 250.f;
        float spacing = 120.f;

      
        _level1Button = new Button(
            []() {
                WAVE_MANAGER.LoadLevel("lvl1.xml");
                SM.SetNextScene("Gameplay");
            },
            Vector2(centerX + 190.f, startY + 25.f),
            Vector2(buttonWidth + 200.f, buttonHeight)
        );
        _ui.push_back(_level1Button);

        _level1Text = new TextObject("Sea of Karnaugh");
        _level1Text->GetTransform()->position = Vector2(centerX + 50.f, startY + 100.f);
        _level1Text->GetTransform()->scale = Vector2(2.25f, 2.25f);
        _level1Text->GetRenderer()->SetColor({ 255, 255, 255, 255 });
        _ui.push_back(_level1Text);

        _level2Button = new Button(
            []() {
                WAVE_MANAGER.LoadLevel("lvl2.xml");
                SM.SetNextScene("Gameplay");
            },
            Vector2(centerX + 190.f, startY + 125.f),
            Vector2(buttonWidth + 200.f, buttonHeight)
        );
        _ui.push_back(_level2Button);

        _level2Text = new TextObject("Vanguard Warzone");
        _level2Text->GetTransform()->position = Vector2(centerX + 50.f, startY + 200.f);
        _level2Text->GetTransform()->scale = Vector2(2.25f, 2.25f);
        _level2Text->GetRenderer()->SetColor({ 255, 255, 255, 255 });
        _ui.push_back(_level2Text);

        _backButton = new Button(
            []() {
                SM.SetNextScene("MenuScene");
            },
            Vector2(centerX + 190.f, startY + 250.f),
            Vector2(buttonWidth, buttonHeight)
        );
        _ui.push_back(_backButton);

        _backText = new TextObject("BACK TO MENU");
        _backText->GetTransform()->position = Vector2(centerX + 125.f, startY + 325.f);
        _backText->GetTransform()->scale = Vector2(2.f, 2.f);
        _backText->GetRenderer()->SetColor({ 200, 200, 200, 255 });
        _ui.push_back(_backText);
    }

    void OnExit() override
    {
        _titleText = nullptr;
        _level1Button = nullptr;
        _level2Button = nullptr;
        _backButton = nullptr;
        _level1Text = nullptr;
        _level2Text = nullptr;
        _backText = nullptr;

        Scene::OnExit();
    }

    void Update() override
    {
        Scene::Update();
    }

    void Render() override
    {
        Scene::Render();
    }
};