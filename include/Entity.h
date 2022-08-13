#pragma once

#include<SDL.h>

#include"Vector.h"
#include"AssetManager.h"

class Entity
{
public:
	Entity(const AssetManager& assetManager, const Vector& pos, const std::string& key);
	~Entity();
	virtual void Update();
	virtual void Render(SDL_Renderer* renderer);
	virtual void HandleEvents(SDL_Event& event);
protected:
	SDL_Rect m_textureRect;
	Vector m_position;
	SDL_Texture* m_texture;
};