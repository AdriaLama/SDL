#include "WaveManager.h"
#include "TimeManager.h"
#include "RenderManager.h"
#include "Bubble.h"
#include "KillerWhale.h"
#include "HorizontalMedusa.h"
#include "VerticalMedusa.h"
#include "Circler.h"
#include "CircleChild.h"
#include "Chomper.h"
#include "Beholder.h"
#include "Amoeba.h"
#include "BioTitan.h"
#include "PowerUp.h"
#include "Torpedo.h"
#include "Chainsaw.h"
#include "Nuke.h"
#include "Missiles.h"
#include "Daniels.h"
#include "Annoyer.h"
#include "Angrygons.h"
#include "SpaceBoss.h"
#include "Ufo.h"
#include "RoboKrabs.h"
#include <cstdlib>

void WaveManager::Update()
{
    if (waveOrder.empty() || currentWave >= maxWaves) return;

    if (isWaveActive)
    {
        if (activeEnemiesInWave <= 0)
        {
            if (enemiesKilledInWave == totalEnemiesInWave && totalEnemiesInWave > 0)
            {
                SpawnPowerUpAtLastEnemy();
            }

            totalEnemiesInWave = 0;
            enemiesKilledInWave = 0;
            isWaveActive = false;
            waitingForNextWave = true;
            spawnTimer = 0.0f;
            currentWave++;

            if (currentWave >= maxWaves)
            {
                levelCompleted = true;
            }
        }
    }
    else if (waitingForNextWave)
    {
        WaitForNextWave();
    }
    else
    {
        if (currentWave < maxWaves)
        {
            SpawnCurrentWave();
            isWaveActive = true;
            enemiesSpawnedInCurrentWave = 0;
            spawnTimer = 0.0f;
        }
    }
}

void WaveManager::WaitForNextWave()
{
    spawnTimer += TM.GetDeltaTime();

    if (spawnTimer >= timeBetweenWaves)
    {
        waitingForNextWave = false;

        if (currentWave < maxWaves)
        {
            SpawnCurrentWave();
            isWaveActive = true;
            enemiesSpawnedInCurrentWave = 0;
            spawnTimer = 0.0f;
        }
    }
}

void WaveManager::SpawnPowerUpAtLastEnemy()
{
    SPAWNER.SpawnObjects(new PowerUp(lastEnemyPosition));
}

void WaveManager::SpawnCurrentWave()
{
    totalEnemiesInWave = 0;
    enemiesKilledInWave = 0;

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
    case 9:
        SpawnBoss();
        break;
    case 10:
        SpawnTorpedo();
        break;
    case 11:
        SpawnChainsaw();
        break;
    case 12:
        SpawnRoboKrabs();
        break;
    case 13:
        SpawnNuke();
        break;
    case 14:
        SpawnMissile();
        break;
    case 15:
        SpawnDaniels();
        break;
    case 16:
        SpawnUfo();
        break;
    case 17:
        SpawnAnnoyer();
        break;
    case 18:
        SpawnAngrygons();
        break;
    case 19:
        SpawnSpaceBoss();
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
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }

    for (int i = 0; i < amount / 2; i++)
    {
        float delay = i * 0.5f;
        SPAWNER.SpawnObjects(new Bubble(Vector2(RM->WINDOW_WIDTH - 100 + (i * 80.f), RM->WINDOW_HEIGHT - 200.f)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }
}

void WaveManager::SpawnKillerWhale()
{
    int amount = amountEnemies[currentWave];

    for (int i = 0; i < amount / 2; i++)
    {
        SPAWNER.SpawnObjects(new KillerWhale(Vector2(RM->WINDOW_WIDTH + 100.f, RM->WINDOW_HEIGHT - 50.f)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }
    for (int i = 0; i < amount / 2; i++)
    {
        SPAWNER.SpawnObjects(new KillerWhale(Vector2(RM->WINDOW_WIDTH + 700.f, 50.f)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }
}

void WaveManager::SpawnHorizontalMedusas()
{
    int amount = amountEnemies[currentWave];

    for (int i = 0; i < amount; i++)
    {
        float randomY = (rand() % RM->WINDOW_HEIGHT - 200) + 200;
        SPAWNER.SpawnObjects(new HorizontalMedusa(Vector2(RM->WINDOW_WIDTH + 100.f, randomY)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }
}

void WaveManager::SpawnVerticalMedusas()
{
    int amount = amountEnemies[currentWave];

    for (int i = 0; i < amount; i++)
    {
        float randomX = (rand() % RM->WINDOW_WIDTH - 200) + 200;
        SPAWNER.SpawnObjects(new VerticalMedusa(Vector2(randomX, RM->WINDOW_HEIGHT + 100.f)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }
}

void WaveManager::SpawnCircler()
{
    int amount = amountEnemies[currentWave];

    for (int i = 1; i <= amount; i++)
    {
        if (i == 1) {
            SPAWNER.SpawnObjects(new Circler(Vector2(500.f, 0.f), Vector2(100.f, 100.f)));
            enemiesSpawnedInCurrentWave++;
            OnEnemySpawned();
        }

        SPAWNER.SpawnObjects(new CircleChild(Vector2(500.f, 0.f - (i * 60.f)), Vector2(50.f, 50.f)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }
}

void WaveManager::SpawnBeholder()
{
    int amount = amountEnemies[currentWave];

    for (int i = 0; i < amount / 4; i++)
    {
        SPAWNER.SpawnObjects(new Beholder(Vector2(100.f + (i * 80.f), 100.f)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }

    for (int i = 0; i < amount / 4; i++)
    {
        SPAWNER.SpawnObjects(new Beholder(Vector2(RM->WINDOW_WIDTH - 300.f + (i * 80.f), 100.f)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }

    for (int i = 0; i < amount / 4; i++)
    {
        SPAWNER.SpawnObjects(new Beholder(Vector2(100.f + (i * 80.f), RM->WINDOW_HEIGHT - 100.f)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }

    for (int i = 0; i < amount / 4; i++)
    {
        SPAWNER.SpawnObjects(new Beholder(Vector2(RM->WINDOW_WIDTH - 300.f + (i * 80.f), RM->WINDOW_HEIGHT - 100.f)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }
}

void WaveManager::SpawnComper()
{
    int amount = amountEnemies[currentWave];

    for (int i = 0; i < amount; i++)
    {
        SPAWNER.SpawnObjects(new Chomper(Vector2(RM->WINDOW_WIDTH + 100.f, RM->WINDOW_HEIGHT - (i * 60.f) - 200.f), i));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }
}

void WaveManager::SpawnAmoeba()
{
    int amount = amountEnemies[currentWave];

    for (int i = 0; i < amount; i++)
    {
        SPAWNER.SpawnObjects(new Amoeba(Vector2(-100.f, RM->WINDOW_HEIGHT / 2.f)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }
}

void WaveManager::SpawnBoss()
{
    int amount = amountEnemies[currentWave];

    for (int i = 0; i < amount; i++)
    {
        SPAWNER.SpawnObjects(new BioTitan(Vector2(RM->WINDOW_WIDTH + 100.f, RM->WINDOW_HEIGHT / 2.f)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }
}


void WaveManager::SpawnTorpedo()
{
    int amount = amountEnemies[currentWave];
    for (int i = 0; i < amount; i++)
    {
        float randomY = (rand() % RM->WINDOW_HEIGHT - 200) + 200;
        SPAWNER.SpawnObjects(new Torpedo(Vector2(RM->WINDOW_WIDTH + 100.f, randomY)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }
}


void WaveManager::SpawnChainsaw()
{
    int amount = amountEnemies[currentWave];
    for (int i = 0; i < amount / 2; i++)
    {
        float delaySpawn = i * 0.5f;
        SPAWNER.SpawnObjects(new Chainsaw(Vector2(-50.f - (i * 80.f), RM->WINDOW_HEIGHT / 2.f)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();

    }
    for (int i = 0; i < amount / 2; i++)
    {
        float delaySpawn = i * 0.5f;
        SPAWNER.SpawnObjects(new Chainsaw(Vector2(RM->WINDOW_WIDTH + 50.f + (i * 80.f), RM->WINDOW_HEIGHT / 2.f)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }
}

void WaveManager::SpawnRoboKrabs()
{
    int amount = amountEnemies[currentWave];


    for (int i = 0; i < amount / 4; i++)
    {
        SPAWNER.SpawnObjects(new RoboKrabs(Vector2(100.f + (i * 80.f), 100.f)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }

    for (int i = 0; i < amount / 4; i++)
    {
        SPAWNER.SpawnObjects(new RoboKrabs(Vector2(RM->WINDOW_WIDTH - 300.f + (i * 80.f), 100.f)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }

    for (int i = 0; i < amount / 4; i++)
    {
        SPAWNER.SpawnObjects(new RoboKrabs(Vector2(100.f + (i * 80.f), RM->WINDOW_HEIGHT - 100.f)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }

    for (int i = 0; i < amount / 4; i++)
    {
        SPAWNER.SpawnObjects(new RoboKrabs(Vector2(RM->WINDOW_WIDTH - 300.f + (i * 80.f), RM->WINDOW_HEIGHT - 100.f)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }
}

void WaveManager::SpawnNuke()
{
    int amount = amountEnemies[currentWave];

    for (int i = 0; i < amount; i++) {
        SPAWNER.SpawnObjects(new Nuke(Vector2(500.f + (i * 150), RM->WINDOW_HEIGHT + 100.f)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }
}

void WaveManager::SpawnMissile()
{
    int amount = amountEnemies[currentWave];

    for (int i = 0; i < amount; i++)
    {
        float randomY = (rand() % RM->WINDOW_HEIGHT - 200) + 200;
        SPAWNER.SpawnObjects(new Missiles(Vector2(RM->WINDOW_WIDTH + 100.f, randomY)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }
}

void WaveManager::SpawnDaniels()
{
    int amount = amountEnemies[currentWave];
    for (int i = 0; i < amount / 2; i++)
    {
        SPAWNER.SpawnObjects(new Daniels(true, i));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }
    for (int i = 0; i < amount / 2; i++)
    {
        SPAWNER.SpawnObjects(new Daniels(false, i));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }
}

void WaveManager::SpawnUfo()
{
    int amount = amountEnemies[currentWave];
    for (int i = 0; i < amount; i++)
    {
        SPAWNER.SpawnObjects(new UFO(i));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }
}

void WaveManager::SpawnAnnoyer()
{
    int amount = amountEnemies[currentWave];

    for (int i = 0; i < amount / 4; i++)
    {
        SPAWNER.SpawnObjects(new Annoyer(Vector2(100.f + (i * 80.f), 100.f)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }

    for (int i = 0; i < amount / 4; i++)
    {
        SPAWNER.SpawnObjects(new Annoyer(Vector2(RM->WINDOW_WIDTH - 300.f + (i * 80.f), 100.f)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }

    for (int i = 0; i < amount / 4; i++)
    {
        SPAWNER.SpawnObjects(new Annoyer(Vector2(100.f + (i * 80.f), RM->WINDOW_HEIGHT - 100.f)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }

    for (int i = 0; i < amount / 4; i++)
    {
        SPAWNER.SpawnObjects(new Annoyer(Vector2(RM->WINDOW_WIDTH - 300.f + (i * 80.f), RM->WINDOW_HEIGHT - 100.f)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }
}

void WaveManager::SpawnAngrygons()
{
    int amount = amountEnemies[currentWave];

    for (int i = 0; i < amount; i++) {
        SPAWNER.SpawnObjects(new Angrygons(Vector2(-100.f + (i * 80.f), 100.f)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }
    
}

void WaveManager::SpawnSpaceBoss()
{
    int amount = amountEnemies[currentWave];
    for (int i = 0; i < amount; i++)
    {
        SPAWNER.SpawnObjects(new SpaceBoss(Vector2(RM->WINDOW_WIDTH + 100.f, RM->WINDOW_HEIGHT / 2.f)));
        enemiesSpawnedInCurrentWave++;
        OnEnemySpawned();
    }
}
