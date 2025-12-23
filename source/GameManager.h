#pragma once
#include "Player.h"

#define GAME_MANAGER GameManager::Instance()

class GameManager
{
public:
    static GameManager& Instance()
    {
        static GameManager playerManager;
        return playerManager;
    }

    void SetPlayer(Player* p) { player = p; }
    Player* GetPlayer() { return player; }

private:
    GameManager() : player(nullptr) {}
    GameManager(GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    Player* player;
};