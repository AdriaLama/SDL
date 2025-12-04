#include "Game.h"
#include "ImageObject.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "Gameplay.h"
#include "MenuScene.h"
#include <cassert>

void Game::Init()
{
	RM->Init();
	RM->LoadTexture("resources/image.png");
	RM->LoadTexture("resources/player.png");
	RM->LoadTexture("resources/bullet.png");
	RM->LoadTexture("resources/backgroundGameplay.png");
	RM->LoadFont("resources/fonts/hyperspace.ttf");
	assert(SM.AddScene("Gameplay", new Gameplay()));
	assert(SM.AddScene("MenuScene", new MenuScene()));
	assert(SM.InitFirstScene("MenuScene"));
	_isRunning = true;
	
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
		RM->WINDOW_WIDTH, RM->WINDOW_HEIGHT,
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

	SM.UpdateCurrentScene();

}

void Game::Render()
{

	 RM -> ClearScreen();
	 SM.GetCurrentScene()->Render();
	 RM -> RenderScreen();
}

void Game::Release()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}