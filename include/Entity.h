#pragma once

#include<SDL.h>
#include<iostream>

#include"Vector.h"
#include"AssetManager.h"

class Entity
{
public:
	Entity(const Vector& pos, const SDL_Rect& textureRect, const float& scale, const std::string& tag);
	virtual ~Entity() = default;
	virtual void Update();
	virtual void Render(SDL_Renderer* renderer);
	virtual void HandleEvents(SDL_Event& event);
	virtual bool Destroy();
	virtual void Reset();

public:
	Vector m_position;
	SDL_Rect m_textureRect;
	std::string m_tag;
	float m_scale;

protected:
	SDL_Texture* m_texture;
};