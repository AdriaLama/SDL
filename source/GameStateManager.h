#pragma once
#include "GameState.h"
#include "GameplayState.h"
#include "PauseState.h"
#include "DeathState.h"
#include "SceneManager.h"
#include <unordered_map>
#include <typeinfo>

#define GAME_STATE_MANAGER GameStateManager::Instance()

class GameStateManager
{
private:
    GameStateManager() : _currentState(nullptr), _isInGameplay(false)
    {
        _gameStates[GameStates::GAMEPLAY] = new GameplayState();
        _gameStates[GameStates::PAUSED] = new PauseState();
        _gameStates[GameStates::DEATH] = new DeathState();
    }

    ~GameStateManager()
    {
        for (auto& pair : _gameStates)
        {
            delete pair.second;
        }
        _gameStates.clear();
    }

    GameStateManager(const GameStateManager&) = delete;
    GameStateManager& operator=(const GameStateManager&) = delete;

    std::unordered_map<GameStates, GameState*> _gameStates;
    GameState* _currentState;
    bool _isInGameplay;

public:
    static GameStateManager& Instance()
    {
        static GameStateManager instance;
        return instance;
    }

    void SetInGameplay(bool inGameplay)
    {
        _isInGameplay = inGameplay;
    }

    void Init()
    {
        if (_isInGameplay)
        {
            if (_gameStates.find(GameStates::GAMEPLAY) != _gameStates.end())
            {
                _currentState = _gameStates[GameStates::GAMEPLAY];
                _currentState->Start();
            }
        }
    }

    void Update(float elapsedTime)
    {
        if (!_isInGameplay)
        {
            SM.UpdateCurrentScene();
            return;
        }

        if (!_currentState)
        {
      
            Init();
            if (!_currentState) return;
        }

        _currentState->Update(elapsedTime);

        if (SM.HasPendingSceneChange())
        {
           
            if (_currentState)
            {
                _currentState->End();
            }

            SM.UpdateCurrentScene();
            return;
        }

        GameStates nextState = _currentState->GetNextState();

        if (nextState != GameStates::NONE)
        {
            _currentState->End();

            if (_gameStates.find(nextState) != _gameStates.end())
            {
                _currentState = _gameStates[nextState];
                _currentState->Start();
            }
        }
    }

    void Render() const
    {
        if (!_isInGameplay)
        {
            SM.GetCurrentScene()->Render();
            return;
        }

        if (_currentState)
        {
            _currentState->Render();
        }
    }

    GameStates GetCurrentState() const
    {
        for (const auto& pair : _gameStates)
        {
            if (pair.second == _currentState)
                return pair.first;
        }
        return GameStates::NONE;
    }

    void ForceState(GameStates state)
    {
        if (_currentState)
            _currentState->End();

        if (_gameStates.find(state) != _gameStates.end())
        {
            _currentState = _gameStates[state];
            _currentState->Start();
        }
    }

    bool IsInState(GameStates state) const
    {
        return GetCurrentState() == state;
    }
};