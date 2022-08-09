#pragma once

#include<SDL.h>

#include"Vector.h"

class Entity
{
public:
	Entity(const Vector& pos, SDL_Texture* tex);
	~Entity();
	void Update();
	void Render(SDL_Renderer* renderer);
private:

	Vector m_position;
	SDL_Texture* m_texture;
	SDL_Rect m_textureRect;
};