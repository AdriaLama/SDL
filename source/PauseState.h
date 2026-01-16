#pragma once
#include "GameState.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "RenderManager.h"
#include "TextObject.h"
#include "Button.h"

class PauseState : public GameState
{
private:
    TextObject* _pauseText;
    TextObject* _resumeText;
    Button* _resumeButton;

public:
    PauseState()
        : _pauseText(nullptr)
        , _resumeText(nullptr)
        , _resumeButton(nullptr)
    {
    }

    void Start() override
    {
        _nextState = GameStates::NONE;

  
        _pauseText = new TextObject("PAUSED");
        _pauseText->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2.0f - 150.f, 200.f);
        _pauseText->GetTransform()->scale = Vector2(3.f, 3.f);
        _pauseText->GetRenderer()->SetColor({ 255, 215, 0, 255 });

 
        float centerX = RM->WINDOW_WIDTH / 2.0f;
        float centerY = RM->WINDOW_HEIGHT / 2.0f;
        float buttonWidth = 300.f;
        float buttonHeight = 60.f;

        _resumeButton = new Button(
            [this]() { _nextState = GameStates::GAMEPLAY; },
            Vector2(centerX - buttonWidth / 2.0f, centerY - buttonHeight / 2.0f),
            Vector2(buttonWidth, buttonHeight)
        );

  
        _resumeText = new TextObject("RESUME");
        _resumeText->GetTransform()->position = Vector2(centerX - 80.f, centerY - 10.f);
        _resumeText->GetTransform()->scale = Vector2(2.f, 2.f);
        _resumeText->GetRenderer()->SetColor({ 255, 255, 255, 255 });
    }

    void Update(float elapsedTime) override
    {
        if (IM->GetEvent(SDLK_ESCAPE, DOWN) || IM->GetEvent(SDLK_P, DOWN))
        {
            _nextState = GameStates::GAMEPLAY;
            return;
        }

        if (_pauseText)
            _pauseText->Update();

        if (_resumeText)
            _resumeText->Update();

        if (_resumeButton)
            _resumeButton->Update();
    }

    void Render() const override
    {

        SM.GetCurrentScene()->Render();


        SDL_SetRenderDrawColor(RM->GetRenderer(), 0, 0, 0, 180);
        SDL_FRect overlayRect = { 0, 0, (float)RM->WINDOW_WIDTH, (float)RM->WINDOW_HEIGHT };
        SDL_RenderFillRect(RM->GetRenderer(), &overlayRect);

   
        if (_pauseText)
            _pauseText->Render();

        if (_resumeButton)
            _resumeButton->Render();

        if (_resumeText)
            _resumeText->Render();
    }

    void End() override
    {
        if (_pauseText)
        {
            delete _pauseText;
            _pauseText = nullptr;
        }

        if (_resumeText)
        {
            delete _resumeText;
            _resumeText = nullptr;
        }

        if (_resumeButton)
        {
            delete _resumeButton;
            _resumeButton = nullptr;
        }
    }
};