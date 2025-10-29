#include "Game.h"

void Game::Init(){

	InitSDL();
	CreateWindowAndRenderer();

	SDL_SetRenderDrawColor(_renderer, 225, 0, 0, 0xFF);

	_isRunning = true;

	_gameObject.push_back(GameObject("resources/image.png", _renderer));

}

void Game::InitSDL() {

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		throw SDL_GetError();
	}

}

void Game::CreateWindowAndRenderer()
{
	if (!SDL_CreateWindowAndRenderer("Test", 512, 512, SDL_WINDOW_RESIZABLE, &_window, &_renderer)) {
		throw SDL_GetError();
	}
}

void Game::HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT) {
			_isRunning = false;
		}
	}
}

void Game::Update() {
	for (GameObject go : _gameObject) {
		go.Update();
	}
}

void Game::Render()
{
	SDL_RenderClear(_renderer);

	for (GameObject go : _gameObject) {
		go.Render(_renderer);
	}

	SDL_RenderPresent(_renderer);
}

void Game::Release()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}





