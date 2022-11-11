#pragma once

#include<SDL.h>
#include<SDL_mixer.h>
#include<unordered_map>
#include<iostream>

class SoundManager
{
public:
	SoundManager() = default;
	~SoundManager();

	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;

	static SoundManager& GetInstance();
	void Load(const char* path, const std::string& key);

	void Play(const std::string& key) const;

private:

	std::unordered_map<std::string, Mix_Chunk*> m_chunksMap;
};