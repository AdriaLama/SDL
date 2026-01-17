#pragma once
#include "Stream.h"
#include "AtomicWrapper.h"

#include "SDL3/SDL_audio.h"
#include <SDL3/SDL.h>

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <queue>

//https://github.com/libsdl-org/SDL/blob/main/examples/audio/04-multiple-streams/multiple-streams.c
//https://github.com/libsdl-org/SDL/blob/main/examples/audio/05-planar-data/planar-data.c

//Threads
//https://stackoverflow.com/questions/9094422/how-to-check-if-a-stdthread-is-still-running

//Per controlar quan cal terminar de cop els threads
static std::atomic<bool> shouldHaltAudio = false;
static std::vector<AtomicWrapper<bool>> threadsDone;

#define AM AudioManager::GetInstance()

class AudioManager
{
public:
	static AudioManager* GetInstance()
	{
		static AudioManager instance;
		return &instance;
	}

	//Obre dispositiu d'àudio
	bool Init();

	//Fonamental cridar abans d'acabar el programa per terminar els threads correctament
	void HaltAudio();

	//Llegeix i guarda dades d'un so (fitxer .wav) a partir de la seva ruta
	bool LoadSoundData(std::string path);

	//Crea un nou stream a partir de les dades del fitxer .wav associat a una ruta
	void PlaySound(std::string path);

	void PlaySoundLooping(std::string path);

	//Silencia / dessilencia TOT l'àudio (= pausa / ressumeix el dispositiu d'àudio)
	void Mute();
	void Unmute();

	////FUNCIONS INTRODUÏDES PEL REFACTOR
	SoundData* GetSoundData(std::string path)
	{
		if (_soundsData.find(path) == _soundsData.end())
			return nullptr;

		return _soundsData[path];
	}

private:
	AudioManager() = default;
	AudioManager(AudioManager&) = delete;
	AudioManager& operator=(const AudioManager&) = default;
	~AudioManager();

	void PlaySoundCallback(std::string path, int pos, bool looping)
	{
		Stream stream = Stream(_soundsData[path]->spec, _audioDevice);

		if (looping)
			stream.CheckPlaybackLooping(_soundsData[path], shouldHaltAudio);
		else
			stream.CheckPlayback(_soundsData[path], shouldHaltAudio);

		threadsDone[pos] = AtomicWrapper<bool>(std::atomic<bool>(true));
	}

	bool _muted = false;
	SDL_AudioDeviceID _audioDevice = 0;

	//key: ruta al .wav
	std::map<std::string, SoundData*> _soundsData;
};