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
        lastEnemyPosition(Vector2(0.0f, 0.0f))
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

    // Variables para power-ups
    Vector2 lastEnemyPosition;
    int totalEnemiesInWave;      // Total de enemigos spawneados en la wave
    int enemiesKilledInWave;     // Enemigos eliminados (no escapados)

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
        }
    }

    int GetCurrentWave() const { return currentWave; }
    bool IsWaveActive() const { return isWaveActive; }

    void OnEnemySpawned()
    {
        activeEnemiesInWave++;
        totalEnemiesInWave++;
    }

    // Método para cuando un enemigo es DESTRUIDO (matado por el jugador)
    void OnEnemyDestroyed(const Vector2& position)
    {
        if (activeEnemiesInWave > 0)
        {
            activeEnemiesInWave--;
            enemiesKilledInWave++;
            lastEnemyPosition = position;
        }
    }

    // Sobrecarga para enemigos que salen de pantalla (NO fueron derrotados)
    void OnEnemyDestroyed()
    {
        if (activeEnemiesInWave > 0)
        {
            activeEnemiesInWave--;
            // NO incrementamos enemiesKilledInWave porque escapó
        }
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
    void SpawnUfo();
    void SpawnBoss();
};