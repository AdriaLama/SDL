#pragma once
#include "vector2.h"
#include <SDL3/SDL.h>
#include <string>

class GameObject {
protected:
	Vector2 _position;
	SDL_Texture* _texture;
	SDL_FRect _sourceRect;
	SDL_FRect _destinationRect;

public:
	GameObject(std::string texturePath, SDL_Renderer* renderer);
	void SetPosition(Vector2 position);
	Vector2 GetPosition() const { return _position; }
	void Update();
	void Render(SDL_Renderer* renderer);
};