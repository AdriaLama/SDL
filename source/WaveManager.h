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
        activeEnemiesInWave(0),
        isWaveActive(false),
        waitingForNextWave(false),
        lastEnemyPosition(Vector2(0.0f, 0.0f)),
        levelCompleted(false),
        currentLevel("lvl1.xml")
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
    int activeEnemiesInWave;
    bool isWaveActive;
    bool waitingForNextWave;
    float spawnYTimer;
    bool levelCompleted;
    std::string currentLevel;

    Vector2 lastEnemyPosition;
    int totalEnemiesInWave;
    int enemiesKilledInWave;

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
            activeEnemiesInWave = 0;
            isWaveActive = false;
            waitingForNextWave = false;
            spawnTimer = 0.0f;
            totalEnemiesInWave = 0;
            enemiesKilledInWave = 0;
            levelCompleted = false;
            currentLevel = levelPath;
        }
    }

    int GetCurrentWave() const { return currentWave; }
    bool IsWaveActive() const { return isWaveActive; }
    bool IsLevelCompleted() const { return levelCompleted; }
    std::string GetCurrentLevel() const { return currentLevel; }

    void OnEnemySpawned()
    {
        activeEnemiesInWave++;
        totalEnemiesInWave++;
    }

    void OnEnemyDestroyed(const Vector2& position)
    {
        if (activeEnemiesInWave > 0)
        {
            activeEnemiesInWave--;
            enemiesKilledInWave++;
            lastEnemyPosition = position;

            
            if (activeEnemiesInWave == 0 && currentWave >= maxWaves - 1 && isWaveActive)
            {
                levelCompleted = true;
            }
        }
    }

    void OnEnemyDestroyed()
    {
        if (activeEnemiesInWave > 0)
        {
            activeEnemiesInWave--;
        }
    }

    void ResetLevelCompletion()
    {
        levelCompleted = false;
    }

    int GetActiveEnemies() const { return activeEnemiesInWave; }

    void Update();

private:
    void SpawnCurrentWave();
    void WaitForNextWave();
    void SpawnPowerUpAtLastEnemy();
    void SpawnWaveBubble();
    void SpawnKillerWhale();
    void SpawnHorizontalMedusas();
    void SpawnVerticalMedusas();
    void SpawnCircler();
    void SpawnBeholder();
    void SpawnComper();
    void SpawnAmoeba();
    void SpawnBoss();
    void SpawnTorpedo();
    void SpawnChainsaw();
    void SpawnRoboKrabs();
    void SpawnNuke();
    void SpawnMissile();
    void SpawnDaniels();
    void SpawnUfo();
    void SpawnAnnoyer();
    void SpawnAngrygons();
    void SpawnSpaceBoss();
};