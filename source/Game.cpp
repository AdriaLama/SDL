#include "Game.h"
#include "ImageObject.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "Gameplay.h"
#include "MenuScene.h"
#include "SplashScreen.h"
#include "RankingScene.h"
#include "RankingNameScene.h"
#include "LevelSelectorScene.h"
#include "AudioManager.h"
#include "GameStateManager.h"
#include <cassert>

void Game::Init()
{
	RM->Init();

	RM->LoadTexture("resources/images/player.png");
	RM->LoadTexture("resources/images/bullet.png");
	RM->LoadTexture("resources/images/backgroundGameplay.png");
	RM->LoadTexture("resources/images/boss1.png");
	RM->LoadTexture("resources/images/boss2.png");
	RM->LoadTexture("resources/images/laser.png");
	RM->LoadTexture("resources/images/cannon.png");
	RM->LoadTexture("resources/images/amoeba.png");
	RM->LoadTexture("resources/images/angrygons.png");
	RM->LoadTexture("resources/images/annoyer.png");
	RM->LoadTexture("resources/images/beholder.png");
	RM->LoadTexture("resources/images/bubbles.png");
	RM->LoadTexture("resources/images/chomper.png");
	RM->LoadTexture("resources/images/circler.png");
	RM->LoadTexture("resources/images/circlerChild.png");
	RM->LoadTexture("resources/images/daniels.png");
	RM->LoadTexture("resources/images/horizontalMedusa.png");
	RM->LoadTexture("resources/images/killerWhale.png");
	RM->LoadTexture("resources/images/missile.png");
	RM->LoadTexture("resources/images/nuke.png");
	RM->LoadTexture("resources/images/roboKrabs.png");
	RM->LoadTexture("resources/images/torpedo.png");
	RM->LoadTexture("resources/images/turboChainsaw.png");
	RM->LoadTexture("resources/images/ufo.png");
	RM->LoadTexture("resources/images/verticalMedusa.png");
	RM->LoadTexture("resources/images/powerup1.png");
	RM->LoadTexture("resources/images/powerup2.png");
	RM->LoadTexture("resources/images/powerup3.png");
	RM->LoadTexture("resources/images/powerup4.png");
	RM->LoadTexture("resources/images/powerup5.png");
	RM->LoadTexture("resources/images/powerup6.png");
	RM->LoadTexture("resources/images/SplashScreen.png");
	RM->LoadTexture("resources/images/button.png");
	RM->LoadTexture("resources/images/turret.png");

	AM->LoadSoundData("resources/audio/music/froggerSong.wav");
	AM->LoadSoundData("resources/audio/sfx/defeat.wav");
	AM->LoadSoundData("resources/audio/455911__bolkmar__machine-gun-shoot-only.wav");
	AM->LoadSoundData("resources/audio/138481__justinvoke__bullet-blood-4.wav");
	AM->LoadSoundData("resources/audio/270333__littlerobotsoundfactory__jingle_win_00.wav");
	AM->LoadSoundData("resources/audio/414209__jacksonacademyashmore__death.wav");
	AM->LoadSoundData("resources/audio/501104__evretro__8-bit-damage-sound.wav");
	AM->LoadSoundData("resources/audio/538151__fupicat__8bit-fall.wav");
	AM->LoadSoundData("resources/audio/450616__breviceps__8-bit-error.wav");
	AM->LoadSoundData("resources/audio/retro-arcade-game-music-396890.wav");

	RM->LoadFont("resources/fonts/hyperspace.ttf");

	assert(SM.AddScene("Gameplay", new Gameplay()));
	assert(SM.AddScene("MenuScene", new MenuScene()));
	assert(SM.AddScene("SplashScreen", new SplashScreen()));
	assert(SM.AddScene("Ranking", new RankingScene()));
	assert(SM.AddScene("RankingNameScene", new RankingNameScene()));
	assert(SM.AddScene("LevelSelector", new LevelSelectorScene()));

	assert(SM.InitFirstScene("SplashScreen"));

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
	GAME_STATE_MANAGER.Update(TM.GetDeltaTime());
}

void Game::Render()
{
	RM->ClearScreen();
	GAME_STATE_MANAGER.Render();
	RM->RenderScreen();
}

void Game::Release()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	AM->HaltAudio();
	SDL_Quit();
}