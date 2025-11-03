#include "Game.h"
#include "ImageObject.h"
#include "InputManager.h"

void Game::Init()
{
	InitSDL();
	CreateWindowAndRenderer();

	SDL_SetRenderDrawColor(
		_renderer,
		225, 0, 0, 0xFF
	);

	_isRunning = true;
	_gameObjects.push_back(new ImageObject("resources/image.png", _renderer));
}

void Game::InitSDL()
{
	if (!SDL_Init(SDL_INIT_VIDEO))
		throw SDL_GetError();
}

void Game::CreateWindowAndRenderer()
{
	if (!SDL_CreateWindowAndRenderer(
		"Test",
		512, 512,
		SDL_WINDOW_RESIZABLE,
		&_window,
		&_renderer
	))
		throw SDL_GetError();
}

void Game::HandleEvents()
{
	_isRunning = !IM->Listen();
}


void Game::Update()
{
	for (Object* go : _gameObjects)
		go->Update();
}

void Game::Render()
{
	SDL_RenderClear(_renderer);
	
	for (Object* go : _gameObjects)
		go->Render(_renderer);

	SDL_RenderPresent(_renderer);
}

void Game::Release()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}