#include "Amoeba.h"
#include "TimeManager.h"
#include "Bullet.h"
#include "ScoreManager.h"
#include "WaveManager.h"

Amoeba::Amoeba(Vector2 spawnPos)
    : Enemy()
{
    _renderer = new ImageRenderer(_transform, "resources/amoeba.png", Vector2(0.f, 0.f), Vector2(0.f, 0.f));
    _transform->size = Vector2(50.f, 50.f);
    _transform->position = spawnPos;
    spawnPosition = spawnPos;
    _physics->AddCollider(new AABB(_transform->position, _transform->size));
    currentState = SIMPLE_MOVE;
    health = 8;
    
    circleTimer = 0.0f;
    circleCount = 0;
    isCopy = false;
    moveSpeed = 100.0f;
    copyIndex = 0;
    parentAmoeba = nullptr;
}

Amoeba::Amoeba(Vector2 spawnPos, int index, bool copy, Amoeba* parent)
    : Enemy()
{
    _renderer = new ImageRenderer(_transform, "resources/amoeba.png", Vector2(0.f, 0.f), Vector2(0.f, 0.f));
    _transform->size = Vector2(50.f, 50.f);
    _transform->position = spawnPos;
    _physics->AddCollider(new AABB(_transform->position, _transform->size));
    currentState = CIRCLE_MOVE;
    health = 1;
    
    circleTimer = 0.0f;
    circleCount = 0;
    isCopy = copy;
    moveSpeed = 100.0f;
    copyIndex = index;
    centerPosition = spawnPos;
    parentAmoeba = parent;
}

void Amoeba::Behaviour()
{
    switch (currentState)
    {
    case SIMPLE_MOVE:
        MoveToCenter();
        break;
    case CIRCLE_MOVE:
        CircleMovement();
        break;
    case RETURN:
        ReturnToRight();
        break;
    default:
        break;
    }
}

void Amoeba::Update()
{
    Enemy::Update();
    Behaviour();

    if (_transform->position.x > RM->WINDOW_WIDTH + 100.f)
    {
        WAVE_MANAGER.OnEnemyDestroyed();
        Destroy();
    }
}

void Amoeba::OnCollisionEnter(Object* object)
{
    if (isDying) return;
    Bullet* bullet = dynamic_cast<Bullet*>(object);
    if (bullet != nullptr) {

        health--;
        if (health <= 0) {
            
            if (isCopy && parentAmoeba != nullptr) {
                parentAmoeba->health--; 
                parentAmoeba->RemoveCopyReference(this);
                parentAmoeba = nullptr;
                HUD_MANAGER.AddScore(150);
                WAVE_MANAGER.OnEnemyDestroyed(_transform->position);

            }
            isDying = true;
            Destroy();
        }
    }
}

void Amoeba::MoveToCenter()
{
    _physics->SetVelocity(Vector2(moveSpeed, 0.f));
    if (_transform->position.x >= RM->WINDOW_WIDTH / 2.0f)
    {
        _physics->SetVelocity(Vector2(0.f, 0.f));
        centerPosition = _transform->position;
        Split();
        currentState = CIRCLE_MOVE;
    }
}

void Amoeba::Split()
{
    int numCopies = health;
    for (int i = 0; i < numCopies; i++)
    {
        Amoeba* copy = new Amoeba(centerPosition, i, true, this);
        copies.push_back(copy);
        SPAWNER.SpawnObjects(copy);
    }
}

void Amoeba::CircleMovement()
{
    circleTimer += TM.GetDeltaTime();
    float radius = 100.0f;
    float angularSpeed = 2.0f;
    float angle = circleTimer * angularSpeed;
    int totalCopies = 8;

    if (isCopy && parentAmoeba != nullptr)
    {
        totalCopies = parentAmoeba->GetHealth();
    }

    float offsetAngle = (2.0f * 3.14159f / totalCopies) * copyIndex;
    float finalAngle = angle + offsetAngle;

    Vector2 newPos;
    newPos.x = centerPosition.x + cos(finalAngle) * radius;
    newPos.y = centerPosition.y + sin(finalAngle) * radius;

    _transform->position = newPos;

    if (circleTimer >= 3.14159f)
    {
        circleCount++;
        circleTimer = 0.0f;

        if (circleCount >= 2)
        {
            Recombine();
        }
    }
}

void Amoeba::Recombine()
{
    if (!isCopy)
    {
        
        std::vector<Amoeba*> copiesToDestroy = copies;
        copies.clear(); 

        for (Amoeba* copy : copiesToDestroy)
        {
            if (copy != nullptr)
            {
                copy->parentAmoeba = nullptr;
                copy->Destroy();
            }
        }

        _transform->position = centerPosition;
        currentState = RETURN;
    }
}

void Amoeba::RemoveCopyReference(Amoeba* copy)
{
    for (auto it = copies.begin(); it != copies.end(); ++it)
    {
        if (*it == copy)
        {
            copies.erase(it);
            break;
        }
    }
}

void Amoeba::ReturnToRight()
{
    _physics->SetVelocity(Vector2(moveSpeed, 0.f));
}