#pragma once
#include "Vector2.h"
#include "Renderer.h"
#include <SDL3/SDL.h>
#include <string>

class Object
{
protected:
	Vector2 _position;
	Renderer* _renderer;

public:
	Object() { _position = Vector2(); _renderer = nullptr; }
	void SetPosition(Vector2 position)
	{
		_position = position;
		_renderer->SetDestinationRect({ _position.x, _position.y, 100.f, 100.f });
	}
	Vector2 GetPosition() const { return _position; }
	virtual void Update() { _renderer->Update(); }
	virtual void Render(SDL_Renderer* renderer){ _renderer->Render(renderer); }
};