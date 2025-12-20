#include "Enemy.h"

class Nuke : public Enemy
{
public:
    Nuke(Vector2(spawnPosition))
        : Enemy()
    {

        _renderer = new ImageRenderer(_transform, "resources/image.png", Vector2(0.f, 0.f), Vector2(0.f, 0.f));

        _transform->size = Vector2(125.f, 125.f);
        _transform->position = spawnPosition;

        _physics->AddCollider(new AABB(_transform->position, _transform->size));
        currentState = STAY;

    }
    void Update() override;
    void Behaviour() override;
};