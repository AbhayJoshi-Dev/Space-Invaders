#pragma once

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<memory>

#include"Utils.h"
#include"Player.h"
#include"Enemy.h"
#include"Wall.h"
#include"SoundManager.h"

class Game
{
public:
	Game();
	~Game();
	void CreateWindow(const char* title, int w, int h);
	void GameLoop();
	void Update();
	void Render();
	void CheckCollisions(std::vector<ICollidable*>& collidables);
	void MoveEnemies();

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	bool quit;
	SDL_Event m_event;

	std::vector<Entity*> m_entities;

	const float TIMESTEP = 0.01f;
	float m_accumulator = 0.f;
	float m_currentTime = 0.f;
	float m_newTime = 0.f;
	float m_frameTime = 0.f;
	float m_alpha = 0.f;
	int m_startTicks;
	int m_frameTicks;
	bool m_canShoot = true;

	Player* m_player;

	Wall m_wall;
	Timer m_timer;
	int m_flag = 0;
	bool m_returnflag = false;
	bool m_moveDown = false;
};