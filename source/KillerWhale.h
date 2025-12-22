#include "Enemy.h"

class KillerWhale : public Enemy
{
private:
    bool spawnedUpWhale;
public:
    KillerWhale(Vector2(spawnPosition))
        : Enemy()
    {

        _renderer = new ImageRenderer(_transform, "resources/image.png", Vector2(0.f, 0.f), Vector2(0.f, 0.f));

        _transform->size = Vector2(125.f, 125.f);
        _transform->position = spawnPosition;

        if (spawnPosition.y < RM->WINDOW_HEIGHT / 2.f)
            spawnedUpWhale = true;
        else
            spawnedUpWhale = false;

        _physics->AddCollider(new AABB(_transform->position, _transform->size));
        currentState = SIMPLE_MOVE;
        health = 5;


    }
    void Update() override;
    void Behaviour() override;
    void OnCollisionEnter(Object* object) override;
};