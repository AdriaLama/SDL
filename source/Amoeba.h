#pragma once
#include "Enemy.h"
#include <vector>

class Amoeba : public Enemy
{
private:
    Vector2 spawnPosition;
    Vector2 centerPosition;
    std::vector<Amoeba*> copies;
    float circleTimer;
    int circleCount;
    bool isCopy;
    float moveSpeed;
    int copyIndex;
    Amoeba* parentAmoeba;


public:
    Amoeba(Vector2 spawnPos);
    Amoeba(Vector2 spawnPos, int index, bool copy, Amoeba* parent);

    void Behaviour() override;
    void Update() override;
    void OnCollisionEnter(Object* object) override;
    void RemoveCopyReference(Amoeba* copy);

private:
    void MoveToCenter();
    void Split();
    void CircleMovement();
    void Recombine();
    void ReturnToRight();
};