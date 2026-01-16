#pragma once
#include "GameState.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "RenderManager.h"
#include "ScoreManager.h"
#include "RankingNameScene.h"
#include "RankingManager.h"
#include "Spawner.h"
#include "AudioManager.h"

class DeathState : public GameState
{
private:
    enum class DeathPhase
    {
        DEATH_ANIMATION,
        BLACK_SCREEN
    };

    DeathPhase _currentPhase;
    float _phaseTimer;

public:
    DeathState()
        : _currentPhase(DeathPhase::DEATH_ANIMATION)
        , _phaseTimer(0.f)
    {
    }

    void Start() override
    {
        _nextState = GameStates::NONE;
        _currentPhase = DeathPhase::DEATH_ANIMATION;
        _phaseTimer = 0.f;

        AM->PlaySound("resources/audio/538151__fupicat__8bit-fall.wav");
    }

    void Update(float elapsedTime) override
    {
        _phaseTimer += elapsedTime;

        switch (_currentPhase)
        {
        case DeathPhase::DEATH_ANIMATION:

            if (_phaseTimer >= 1.0f)
            {
                _currentPhase = DeathPhase::BLACK_SCREEN;
                _phaseTimer = 0.f;
            }
            break;

        case DeathPhase::BLACK_SCREEN:

            if (_phaseTimer >= 2.0f)
            {
                SPAWNER.ClearSpawner();

                int finalScore = HUD_MANAGER.GetCurrentScore();

                RankingNameScene* rankingNameScene = dynamic_cast<RankingNameScene*>(SM.GetScene("RankingNameScene"));
                if (rankingNameScene)
                {
                    rankingNameScene->SetFinalScore(finalScore);
                }

                HUD_MANAGER.ResetScore();
                SM.SetNextScene("RankingNameScene");
                _nextState = GameStates::NONE;
            }
            break;
        }
    }

    void Render() const override
    {
        switch (_currentPhase)
        {
        case DeathPhase::DEATH_ANIMATION:
            SM.GetCurrentScene()->Render();
            break;

        case DeathPhase::BLACK_SCREEN:
            SDL_SetRenderDrawColor(RM->GetRenderer(), 0, 0, 0, 255);
            SDL_RenderClear(RM->GetRenderer());
            break;
        }
    }

    void End() override {}
};