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

	static AssetManager& GetInstance();

	void Load(SDL_Renderer* renderer, const std::string& key, const std::string& filePath);

	SDL_Texture* Get(const std::string& key) const;

	SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& key, const std::string& filePath);
private:

	std::unordered_map < std::string, SDL_Texture*> m_assetMap;
};