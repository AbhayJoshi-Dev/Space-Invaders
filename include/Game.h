#pragma once

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>

#include"Utils.h"

class Game
{
public:
	Game();
	~Game();
	void CreateWindow(const char* title, int w, int h);
	void GameLoop();
	void Update();
	void Render();

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	bool quit;
	SDL_Event m_event;

	const float TIMESTEP = 0.01f;
	float m_accumulator = 0.f;
	float m_currentTime = 0.f;
	float m_newTime = 0.f;
	float m_frameTime = 0.f;
	float m_alpha = 0.f;
	int m_startTicks;
	int m_frameTicks;
};