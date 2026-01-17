#include "AudioManager.h"
#include <exception>
#include <iostream>
#include <vector>
#include <thread>

bool AudioManager::Init()
{
	try
	{
		if (!SDL_Init(SDL_INIT_AUDIO))
			throw SDL_GetError();

		_audioDevice = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);

		if (_audioDevice == 0)
			throw SDL_GetError();

		//shouldHaltAudio = false;

		return true;
	}
	catch (std::exception exception)
	{
		std::cout << "Error: " << exception.what();
		return false;
	}
}

void AudioManager::HaltAudio()
{
	shouldHaltAudio = true;

	int size = threadsDone.size();
	for (int i = 0; i < size; )
	{
		//Només incrementa comptador si el thread que s'està comprovant ha acabat
		if (threadsDone.at(i)._a)
			i++;
	}

	//NOU! -> Reset
	shouldHaltAudio = false;
	threadsDone.clear();
}

bool AudioManager::LoadSoundData(std::string path)
{
	if (_soundsData.find(path) != _soundsData.end())
		return false;

	SoundData* soundData = new SoundData();

	try
	{
		//Carregar el fitxer .wav des de la ruta
		if (!SDL_LoadWAV(
			path.c_str(),
			&soundData->spec,			//Llegir el format
			&soundData->wavData,		//Llegir les dades d'àudio
			&soundData->wavDataLength	//Llegir la mida (en bytes) de les dades d'àudio
		))
		{
			throw SDL_GetError();
		}

		//Guardar la informació d'aquest so
		_soundsData[path] = soundData;

		return true;

	}
	catch (std::exception exception)
	{
		delete soundData;
		std::cout << "Error: " << exception.what();
		return false;
	}
}

void AudioManager::PlaySound(std::string path)
{
	// Este if lo hemos tenido que añadir porque sino la CPU llega al 100% 
	if (_muted)
		return;
	if (_soundsData.find(path) == _soundsData.end())
		return;

	//1) Crear thread amb la funció corresponent
	threadsDone.push_back(std::atomic<bool>(false));
	std::thread thread(&AudioManager::PlaySoundCallback, this, path, (threadsDone.size() - 1), false);
	thread.detach();
}

void AudioManager::PlaySoundLooping(std::string path)
{
	// Este if lo hemos tenido que añadir porque sino la CPU llega al 100% 
	if (_muted)
		return;
	if (_soundsData.find(path) == _soundsData.end())
		return;

	//1) Crear thread amb la funció corresponent
	threadsDone.push_back(std::atomic<bool>(false));
	std::thread thread(&AudioManager::PlaySoundCallback, this, path, (threadsDone.size() - 1), true);
	thread.detach();
}

void AudioManager::Mute()
{
	if (_muted)
		return;

	SDL_PauseAudioDevice(_audioDevice);
	_muted = true;
}

void AudioManager::Unmute()
{
	if (!_muted)
		return;

	SDL_ResumeAudioDevice(_audioDevice);
	_muted = false;
}

AudioManager::~AudioManager()
{
	//Netejar les dades de sons
	for (std::map<std::string, SoundData*>::iterator it = _soundsData.begin(); it != _soundsData.end(); it++)
	{
		delete it->second;
	}
	_soundsData.clear();
}