#include "Enemy.h"

class Bubble : public Enemy
{
private:
    Vector2 circleCenter;
    float angle;
    bool spawnedUpBubbles;
public:
    Bubble(Vector2(spawnPosition))
        : Enemy()
    {

        _renderer = new ImageRenderer(_transform, "resources/bubbles.png", Vector2(0.f, 0.f), Vector2(0.f, 0.f));

        _transform->size = Vector2(100.f, 100.f);
        _transform->position = spawnPosition;

        if (spawnPosition.y < RM->WINDOW_HEIGHT / 2.f)
            spawnedUpBubbles = true;
        else
            spawnedUpBubbles = false;

        _physics->AddCollider(new AABB(_transform->position, _transform->size));
        currentState = SIMPLE_MOVE;
        health = 1;

        
    }
    void Update() override;
    void Behaviour() override;
    void OnCollisionEnter(Object* object) override;
};