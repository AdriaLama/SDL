#include "Game.h"
#include "ImageObject.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "Gameplay.h"
#include "MenuScene.h"
#include "AudioManager.h"
#include <cassert>

void Game::Init()
{
	RM->Init();
	RM->LoadTexture("resources/player.png");
	RM->LoadTexture("resources/bullet.png");
	RM->LoadTexture("resources/backgroundGameplay.png");
	RM->LoadTexture("resources/boss1.png");
	RM->LoadTexture("resources/boss2.png");
	RM->LoadTexture("resources/laser.png");
	RM->LoadTexture("resources/cannon.png");
	RM->LoadTexture("resources/amoeba.png");
	RM->LoadTexture("resources/angrygons.png");
	RM->LoadTexture("resources/annoyer.png");
	RM->LoadTexture("resources/beholder.png");
	RM->LoadTexture("resources/bubbles.png");
	RM->LoadTexture("resources/chomper.png");
	RM->LoadTexture("resources/circler.png");
	RM->LoadTexture("resources/circlerChild.png");
	RM->LoadTexture("resources/daniels.png");
	RM->LoadTexture("resources/horizontalMedusa.png");
	RM->LoadTexture("resources/killerWhale.png");
	RM->LoadTexture("resources/missile.png");
	RM->LoadTexture("resources/nuke.png");
	RM->LoadTexture("resources/roboKrabs.png");
	RM->LoadTexture("resources/torpedo.png");
	RM->LoadTexture("resources/turboChainsaw.png");
	RM->LoadTexture("resources/ufo.png");
	RM->LoadTexture("resources/verticalMedusa.png");
	AM->LoadSoundsData("resources/audio/music/froggerSong.wav");
	AM->LoadSoundsData("resources/audio/sfx/defeat.wav");
	RM->LoadFont("resources/fonts/hyperspace.ttf");
	RM->LoadTexture("resources/turret.png");
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
	AM->HaltAudio();
	SDL_Quit();
}