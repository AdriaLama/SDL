#include "Enemy.h"

class CircleChild : public Enemy
{
private:
    Vector2 circleCenter;
    float angle;
    float radius;
    float loopCount;
    float diagonalDistance;
    float straightDistance;
    bool isDiagonal;
    bool isStraight;
public:
    CircleChild(Vector2(spawnPosition), Vector2(size))
        : Enemy()
    {

        _renderer = new ImageRenderer(_transform, "resources/circlerChild.png", Vector2(0.f, 0.f), Vector2(0.f, 0.f));

        _transform->size = size;
        _transform->position = spawnPosition;

        _physics->AddCollider(new AABB(_transform->position, _transform->size));
        currentState = SIMPLE_MOVE;
        loopCount = 0;
        health = 999;
        radius = 200.f;

    }
    void Update() override;
    void Behaviour() override;
 
};