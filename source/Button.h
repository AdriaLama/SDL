#pragma once
#include "ImageObject.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "AudioManager.h"
#include <functional>

class Button : public ImageObject
{
public:
    typedef std::function<void()> OnClick;

private:
    bool _isHovered = false;
    OnClick _onClick;
    SDL_Color _normalColor;
    SDL_Color _hoverColor;

public:
    Button(OnClick onClick, Vector2 position, Vector2 size, std::string texturePath = "resources/images/boss1.png")
        : ImageObject(texturePath, Vector2(0.f, 0.f), size)
    {
        _onClick = onClick;
        _transform->position = position;
        _transform->size = size;
        _transform->scale = Vector2(1.f, 1.f);

        _normalColor = { 255, 255, 255, 255 };
        _hoverColor = { 255, 215, 0, 255 };

        _renderer->SetColor(_normalColor);

        _physics->AddCollider(new AABB(_transform->position, _transform->size));
    }

    void SetColors(SDL_Color normal, SDL_Color hover)
    {
        _normalColor = normal;
        _hoverColor = hover;
    }

    virtual void Update() override
    {
        Vector2 mousePos = Vector2(IM->GetMouseX(), IM->GetMouseY());

        if (!_isHovered && _physics->CheckOverlappingPoint(mousePos))
            OnHoverEnter();
        else if (_isHovered && !_physics->CheckOverlappingPoint(mousePos))
            OnHoverExit();
        else if (_isHovered && IM->GetLeftClick())
            OnClicked();

        Object::Update();
    }

    virtual void Render() override
    {
        Object::Render();
    }

private:
    void OnHoverEnter()
    {
        _renderer->SetColor(_hoverColor);
        _isHovered = true;
    }

    void OnHoverExit()
    {
        _renderer->SetColor(_normalColor);
        _isHovered = false;
    }

    void OnClicked()
    {
        _onClick();
    }
};