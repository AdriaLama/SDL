#pragma once
#include "GameState.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "WaveManager.h"

class GameplayState : public GameState
{
public:
    GameplayState() = default;

    void Start() override
    {
        _nextState = GameStates::NONE;
    }

    void Update(float elapsedTime) override
    {
        if (IM->GetEvent(SDLK_ESCAPE, DOWN) || IM->GetEvent(SDLK_P, DOWN))
        {
            _nextState = GameStates::PAUSED;
            return;
        }

        Player* player = GAME_MANAGER.GetPlayer();

        if (player && player->GetShields() <= 0)
        {
            _nextState = GameStates::DEATH;
            return;
        }

        if (WAVE_MANAGER.IsLevelCompleted())
        {
            _nextState = GameStates::FINISH_STAGE;
            return;
        }

        SM.GetCurrentScene()->Update();
    }

    void Render() const override
    {
        SM.GetCurrentScene()->Render();
    }

    void End() override {}
};