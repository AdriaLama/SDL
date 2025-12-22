#include "Enemy.h"

class Chainsaw : public Enemy
{
private:
    Vector2 circleCenter;
    float angle;
    bool spawnedLeftChainsaw;
public:
    Chainsaw(Vector2(spawnPosition))
        : Enemy()
    {

        _renderer = new ImageRenderer(_transform, "resources/turboChainsaw.png", Vector2(0.f, 0.f), Vector2(0.f, 0.f));

        _transform->size = Vector2(100.f, 100.f);
        _transform->position = spawnPosition;

        if (spawnPosition.x < RM->WINDOW_WIDTH / 2.f)
            spawnedLeftChainsaw = true;
        else
            spawnedLeftChainsaw = false;

        _physics->AddCollider(new AABB(_transform->position, _transform->size));
        currentState = SIMPLE_MOVE;
        health = 1;


    }
    void Update() override;
    void Behaviour() override;
    void OnCollisionEnter(Object* object) override;
};