#pragma once

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<memory>
#include<SDL_ttf.h>

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
	void MoveAndShootEnemies();
	void RenderText(const Vector& position, const char* str, const SDL_Color& color);
	void AddEvent(const Event& event);
	int GetHighScore();
	void SetHighScore(int score);

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	bool quit;
	SDL_Event m_event;

	std::vector<Entity*> m_entities;
	std::vector<Enemy*> m_enemies;
	std::vector<ICollidable*> m_collidables;
	std::vector<Event> m_events;

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
	int m_flag = 0;
	bool m_return = false;
	bool m_moveDown = false;
	bool m_resetgame = false;

	TTF_Font* m_font;
	SDL_Color white = { 255, 255, 255, 255 };

	int m_highScore;

};