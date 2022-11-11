#include"SoundManager.h"

SoundManager::~SoundManager()
{
	for (const auto& chunk : m_chunksMap)
		Mix_FreeChunk(chunk.second);
}

SoundManager& SoundManager::GetInstance()
{
	static SoundManager* instance = new SoundManager;
	return *instance;
}

void SoundManager::Load(const char* path, const std::string& key)
{
	Mix_Chunk* chunk = NULL;

	chunk = Mix_LoadWAV(path);
	if (chunk == NULL)
		std::cout << "Audio Not Loaded!" << Mix_GetError() << std::endl;

	m_chunksMap[key] = chunk;
}

void SoundManager::Play(const std::string& key) const
{
	Mix_Chunk* chunk = NULL;

	if (m_chunksMap.find(key) != m_chunksMap.end())
		chunk = m_chunksMap.at(key);
	
	Mix_PlayChannel(-1, chunk, 0);
}