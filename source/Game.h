#pragma once
#include "GameObject.h"
#include <SDL3/SDL.h>
#include <vector>

class Game {
public:
	Game() = default;

	void Init();
	void HandleEvents();
	void Update();
	void Render();
	void Release();

	bool isRunning() const { return _isRunning; }

private:
	void InitSDL();
	void CreateWindowAndRenderer();

	bool _isRunning;
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	std::vector<GameObject> _gameObject;


};