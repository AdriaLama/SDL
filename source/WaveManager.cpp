#include "WaveManager.h"
#include "TimeManager.h"
#include "RenderManager.h"
#include "Bubble.h"
#include "KillerWhale.h"
#include "HorizontalMedusa.h"
#include "Circler.h"
#include "Beholder.h"
#include "Amoeba.h"
#include "Ufo.h"
#include <cstdlib>

void WaveManager::Update()
{   
    if (waveOrder.empty() || currentWave >= maxWaves) return;
   
    if (!isWaveActive)
    {
        WaitForNextWave();
    }
    else
    {
        if (enemiesSpawnedInCurrentWave >= amountEnemies[currentWave])
        {
            isWaveActive = false;
            spawnTimer = 0.0f;
        }
    }
}

void WaveManager::WaitForNextWave()
{
    spawnTimer += TM.GetDeltaTime();

    if (spawnTimer >= timeBetweenWaves)
    {
        
        SpawnCurrentWave();
        isWaveActive = true;
        enemiesSpawnedInCurrentWave = 0;
        spawnTimer = 0.0f;
        currentWave++;
    }
}

void WaveManager::SpawnCurrentWave()
{
    
    int enemyID = waveOrder[currentWave];

    
    switch (enemyID)
    {
    case 1:
        SpawnWaveBubble();
        break;
    case 2:
        SpawnKillerWhale();
        break;
    case 3:
        SpawnHorizontalMedusas();
        break;
    case 4:
        SpawnVerticalMedusas();
        break;
    case 5:
        SpawnCircler();
        break;
    case 6:
        SpawnBeholder();
        break;
    case 7:
        SpawnComper();
        break;
    case 8:
        SpawnAmoeba();
        break;
    default:
        break;
    }
}

void WaveManager::SpawnWaveBubble()
{
    int amount = amountEnemies[currentWave];

    for (int i = 0; i < amount / 2; i++)
    {
        float delaySpawn = i * 0.5f;
        SPAWNER.SpawnObjects(new Bubble(Vector2(RM->WINDOW_WIDTH - 100 + (i * 80.f), 200.f)));
    }

    for (int i = 0; i < amount / 2; i++)
    {
        float delay = i * 0.5f;
        SPAWNER.SpawnObjects(new Bubble(Vector2(RM->WINDOW_WIDTH - 100 + (i * 80.f), RM->WINDOW_HEIGHT - 200.f)));
    }
}

void WaveManager::SpawnKillerWhale()
{
    int amount = amountEnemies[currentWave];

    for (int i = 0; i < amount; i++)
    {
        SPAWNER.SpawnObjects(new Bubble(Vector2(RM->WINDOW_WIDTH - 100 + (i * 80.f), RM->WINDOW_HEIGHT - 200.f)));
    }
}

void WaveManager::SpawnHorizontalMedusas()
{
    int amount = amountEnemies[currentWave];

    for (int i = 0; i < amount; i++)
    {

    }
}

void WaveManager::SpawnVerticalMedusas()
{
    int amount = amountEnemies[currentWave];

    for (int i = 0; i < amount; i++)
    {
        
    }
}

void WaveManager::SpawnCircler()
{
    int amount = amountEnemies[currentWave];

    for (int i = 0; i < amount; i++)
    {

    }
}

void WaveManager::SpawnBeholder()
{
    int amount = amountEnemies[currentWave];

    for (int i = 0; i < amount; i++)
    {

    }
}

void WaveManager::SpawnComper()
{
    int amount = amountEnemies[currentWave];

    for (int i = 0; i < amount; i++)
    {

    }
}

void WaveManager::SpawnAmoeba()
{
    int amount = amountEnemies[currentWave];

    for (int i = 0; i < amount; i++)
    {

    }
}

void WaveManager::SpawnUfo()
{
    int amount = amountEnemies[currentWave];

    for (int i = 0; i < amount; i++)
    {

    }
}