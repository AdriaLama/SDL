#pragma once
#include "Object.h"
#include <SDL3/SDL.h>
#include <vector>

class Game
{
public:
	Game() = default;

	void Init();
	void HandleEvents();
	void Update();
	void Render();
	void Release();

	bool IsRunning() const { return _isRunning; }

private:
	void InitSDL();
	void CreateWindowAndRenderer();

	bool _isRunning;
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	std::vector<Object*> _gameObjects;
};