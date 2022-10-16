#pragma once

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<memory>
#include<forward_list>

#include"Utils.h"
#include"Player.h"
#include"Enemy.h"

class Game
{
public:
	Game();
	~Game();
	void CreateWindow(const char* title, int w, int h);
	void GameLoop();
	void Update();
	void Render();
	void CheckCollisions(std::forward_list<ICollidable*>& collidables);

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	bool quit;
	SDL_Event m_event;

	std::forward_list<std::unique_ptr<Entity>> m_entities;

	const float TIMESTEP = 0.01f;
	float m_accumulator = 0.f;
	float m_currentTime = 0.f;
	float m_newTime = 0.f;
	float m_frameTime = 0.f;
	float m_alpha = 0.f;
	int m_startTicks;
	int m_frameTicks;
};