#pragma once
#include "Scene.h"
#include "Button.h"
#include "TextObject.h"
#include "SceneManager.h"
#include "AudioManager.h"

class MenuScene : public Scene
{
private:
    bool _audioEnabled;
    TextObject* _audioText;

public:
    MenuScene() : _audioEnabled(true), _audioText(nullptr) {}

    void OnEnter() override
    {
        _audioEnabled = true;
        AM->Init();

        TextObject* titleText = new TextObject("MENACE-PC");
        titleText->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2.0f - 100.f, 275.f);
        titleText->GetTransform()->scale = Vector2(4.f, 4.f);
        titleText->GetRenderer()->SetColor({ 255, 255, 255, 255 });
        _ui.push_back(titleText);

        float buttonStartY = 300.f;
        float buttonSpacing = 80.f;
        float buttonWidth = 300.f;
        float buttonHeight = 60.f;
        float centerX = RM->WINDOW_WIDTH / 2.0f - buttonWidth / 2.0f;

        Button* playButton = new Button(
            []() { SM.SetNextScene("LevelSelector"); },
            Vector2(centerX + 100.f, buttonStartY - 50.f),
            Vector2(buttonWidth, buttonHeight)
        );
        _ui.push_back(playButton);

        TextObject* playText = new TextObject("PLAY");
        playText->GetTransform()->position = Vector2(centerX + 150.f, buttonStartY + 15.f);
        playText->GetTransform()->scale = Vector2(2.f, 2.f);
        _ui.push_back(playText);

        Button* rankingButton = new Button(
            []() { SM.SetNextScene("Ranking"); },
            Vector2(centerX + 100.f, buttonStartY + buttonSpacing - 50.f),
            Vector2(buttonWidth, buttonHeight)
        );
        _ui.push_back(rankingButton);

        TextObject* rankingText = new TextObject("RANKING");
        rankingText->GetTransform()->position = Vector2(centerX + 100.f, buttonStartY + buttonSpacing + 15.f);
        rankingText->GetTransform()->scale = Vector2(2.f, 2.f);
        _ui.push_back(rankingText);

        Button* audioButton = new Button(
            [this]() { ToggleAudio(); },
            Vector2(centerX + 100.f, buttonStartY + buttonSpacing + 25.f),
            Vector2(buttonWidth, buttonHeight)
        );
        _ui.push_back(audioButton);

        _audioText = new TextObject("AUDIO:ON");
        _audioText->GetTransform()->position = Vector2(centerX + 70.f, buttonStartY + buttonSpacing + 95.f);
        _audioText->GetTransform()->scale = Vector2(2.f, 2.f);
        _ui.push_back(_audioText);

        Button* exitButton = new Button(
            []() { SDL_Quit(); exit(0); },
            Vector2(centerX + 100.f, buttonStartY + buttonSpacing + 100.f),
            Vector2(buttonWidth, buttonHeight)
        );
        _ui.push_back(exitButton);

        TextObject* exitText = new TextObject("EXIT");
        exitText->GetTransform()->position = Vector2(centerX + 150.f, buttonStartY + buttonSpacing + 165.f);
        exitText->GetTransform()->scale = Vector2(2.f, 2.f);
        _ui.push_back(exitText);

    }

    void ToggleAudio()
    {
        _audioEnabled = !_audioEnabled;

        if (_audioEnabled)
        {
            AM->Unmute();
            if (_audioText)
                _audioText->SetText("AUDIO:ON");
        }
        else
        {
            AM->Mute();
            if (_audioText)
                _audioText->SetText("AUDIO:OFF");
        }
    }

    void OnExit() override
    {
        _audioText = nullptr;
        AM->HaltAudio();
        Scene::OnExit();
    }

    void Update() override { Scene::Update(); }
    void Render() override
    {
        
        SDL_SetRenderDrawColor(RM->GetRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(RM->GetRenderer());

        Scene::Render();
    }
};