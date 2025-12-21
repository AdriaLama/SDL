#include "Enemy.h"

class Missiles : public Enemy
{
private:
    float velocityX;
public:
    Missiles(Vector2(spawnPosition))
        : Enemy()
    {

        _renderer = new ImageRenderer(_transform, "resources/image.png", Vector2(0.f, 0.f), Vector2(0.f, 0.f));

        _transform->size = Vector2(100.f, 100.f);
        _transform->position = spawnPosition;

        _physics->AddCollider(new AABB(_transform->position, _transform->size));
        currentState = SIMPLE_MOVE;
        health = 1;
        velocityX = (rand() % 1500) + 1300;

    }
    void Update() override;
    void Behaviour() override;
    void OnCollisionEnter(Object* object) override;
};