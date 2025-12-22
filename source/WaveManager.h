#pragma once
#include "Spawner.h"
#include "LevelLoad.h"
#include <vector>
#include <string>

#define WAVE_MANAGER WaveManager::Instance()

class WaveManager
{
private:
    WaveManager()
        : currentWave(0),
        maxWaves(0),
        spawnTimer(0.0f),
        timeBetweenWaves(5.0f),
        offsetCircular(30.0f),
        offsetChomper(50.0f),
        offsetDaniels(70.0f),
        offsetMissile(80.0f),
        spawnYTimer(0.0f),
        enemiesSpawnedInCurrentWave(0),
        isWaveActive(false)
    {
    }

    WaveManager(const WaveManager&) = delete;
    WaveManager& operator=(const WaveManager&) = delete;

    int currentWave;
    float offsetCircular;
    float offsetChomper;
    float offsetDaniels;
    float offsetMissile;
    float spawnTimer;
    float timeBetweenWaves;
    std::vector<int> waveOrder;       
    std::vector<int> amountEnemies;    
    int enemiesSpawnedInCurrentWave;
    bool isWaveActive;
    float spawnYTimer;

public:
    static WaveManager& Instance()
    {
        static WaveManager instance;
        return instance;
    }

    int maxWaves;

    std::vector<int>& GetWaveOrder()
    {
        return waveOrder;
    }

    std::vector<int>& GetAmountEnemies()
    {
        return amountEnemies;
    }

    void LoadLevel(const std::string& levelPath)
    {
        LevelLoader loader;
        if (loader.LoadLevel(levelPath, waveOrder, amountEnemies))
        {
            maxWaves = waveOrder.size();
            currentWave = 0;
            enemiesSpawnedInCurrentWave = 0;
            isWaveActive = false;
            spawnTimer = 0.0f;
        }
    }

    int GetCurrentWave() const { return currentWave; }
    bool IsWaveActive() const { return isWaveActive; }

    void Update();

private:
    void SpawnCurrentWave();
    void WaitForNextWave();

    
    void SpawnWaveBubble();
    void SpawnKillerWhale();
    void SpawnHorizontalMedusas();
    void SpawnVerticalMedusas();
    void SpawnCircler();
    void SpawnBeholder();
    void SpawnComper();
    void SpawnAmoeba();
    void SpawnUfo();
};