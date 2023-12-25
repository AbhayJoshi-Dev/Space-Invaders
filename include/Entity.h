#pragma once

#include<SDL.h>
#include<iostream>

#include"Vector.h"
#include"AssetManager.h"

class Game;
struct Event;

class Entity
{
public:
	Entity(const Vector& pos, const SDL_Rect& textureRect, const float& scale, const std::string& tag, Game* game = nullptr);
	virtual ~Entity() = default;
	virtual void Update();
	virtual void Render(SDL_Renderer* renderer);
	virtual void HandleEvents(SDL_Event& event);
	virtual bool Destroy();
	virtual void Reset();
	void AddEvent(const Event& event);

public:
	Vector m_position;
	SDL_Rect m_textureRect;
	std::string m_tag;
	float m_scale;
	bool m_dead;

protected:
	SDL_Texture* m_texture;

private:
	Game* m_game;
};