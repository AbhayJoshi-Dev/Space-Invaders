#pragma once

#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include<unordered_map>

class AssetManager
{
public:
	AssetManager() = default;
	~AssetManager();

	AssetManager(const AssetManager&) = delete;

	AssetManager& operator=(const AssetManager&) = delete;

	void Load(SDL_Renderer* renderer, const std::string& key, const std::string& filePath);

	SDL_Texture* Get(const std::string& key) const;

private:

	std::unordered_map < std::string, SDL_Texture*> m_assetMap;
};