#include"Game.h"

#include<functional>

Game::Game()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;

	int imgFlag = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlag) & imgFlag))
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1028) < 0)
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error : " << Mix_GetError() << std::endl;

	CreateWindow("Space Invaders", 880, 660);//320, 180

	quit = false;

	//Texture Loading
	AssetManager::GetInstance().Load(m_renderer, "Player", "res/gfx/Player.png");
	AssetManager::GetInstance().Load(m_renderer, "Projectile", "res/gfx/Projectile.png");
	AssetManager::GetInstance().Load(m_renderer, "Enemy1", "res/gfx/Enemy1.png");
	AssetManager::GetInstance().Load(m_renderer, "Enemy2", "res/gfx/Enemy2.png");
	AssetManager::GetInstance().Load(m_renderer, "Enemy1Dead", "res/gfx/Enemy1Dead.png");
	AssetManager::GetInstance().Load(m_renderer, "Enemy3", "res/gfx/Enemy3.png");
	AssetManager::GetInstance().Load(m_renderer, "Enemy4", "res/gfx/Enemy4.png");
	AssetManager::GetInstance().Load(m_renderer, "Enemy3Dead", "res/gfx/Enemy3Dead.png");
	AssetManager::GetInstance().Load(m_renderer, "Enemy5", "res/gfx/Enemy5.png");
	AssetManager::GetInstance().Load(m_renderer, "Enemy6", "res/gfx/Enemy6.png");
	AssetManager::GetInstance().Load(m_renderer, "Enemy5Dead", "res/gfx/Enemy5Dead.png");
	AssetManager::GetInstance().Load(m_renderer, "Enemy7", "res/gfx/Enemy7.png");
	AssetManager::GetInstance().Load(m_renderer, "Enemy8", "res/gfx/Enemy8.png");
	AssetManager::GetInstance().Load(m_renderer, "Enemy7Dead", "res/gfx/Enemy7Dead.png");
	AssetManager::GetInstance().Load(m_renderer, "PlayerDeath1", "res/gfx/PlayerDeath1.png");
	AssetManager::GetInstance().Load(m_renderer, "PlayerDeath2", "res/gfx/PlayerDeath2.png");
	AssetManager::GetInstance().Load(m_renderer, "ProjectileDead", "res/gfx/ProjectileDeath.png");
	AssetManager::GetInstance().Load(m_renderer, "Wall", "res/gfx/Wall.png");

	AssetManager::GetInstance().Load(m_renderer, "Sheet", "res/gfx/spritesheet.png");

	//Audio Loading

	SoundManager::GetInstance().Load("res/audio/shoot.wav", "Shoot");
	SoundManager::GetInstance().Load("res/audio/invaderkilled.wav", "InvaderKilled");




	//creating entities
	m_player = new Player(Vector(300.f, 640.f), "Player", 3.f, "PlayerDeath1", "PlayerDeath2");

	m_entities.push_back(m_player);

	int maxEnemiesInARow = 11;
	int maxEnemiesRows = 5;
	int xSpacing = 50;
	int ySpacing = 40;

	int XPos = 50;
	int YPos = 100;

	for (int i = 0; i < maxEnemiesRows; i++)
	{
		for (int j = 0; j < maxEnemiesInARow; j++)
		{
			switch (i)
			{
			case 0:
				m_entities.push_back(new Enemy(Vector(XPos, YPos), "Enemy1", 3.f, "Enemy1Dead", "Enemy2"));
				break;
			case 1:
				m_entities.push_back(new Enemy(Vector(XPos, YPos), "Enemy3", 3.f, "Enemy3Dead", "Enemy4"));
				break;
			case 2:
				m_entities.push_back(new Enemy(Vector(XPos, YPos), "Enemy5", 3.f, "Enemy5Dead", "Enemy6"));
				break;
			case 3:
				m_entities.push_back(new Enemy(Vector(XPos, YPos), "Enemy7", 3.f, "Enemy7Dead", "Enemy8"));
				break;
			case 4:
				m_entities.push_back(new Enemy(Vector(XPos, YPos), "Enemy1", 3.f, "Enemy1Dead", "Enemy2"));
				break;
			}
			XPos += xSpacing;
		}
		YPos += ySpacing;
		XPos = 50;
	}

 //   m_entities.push_back(new Enemy(Vector(75.f, 150.f), "Enemy3", 3.f, "Enemy3Dead", "Enemy4"));
	//m_entities.push_back(new Enemy(Vector(175.f, 150.f), "Enemy3", 3.f, "Enemy3Dead", "Enemy4"));
	//m_entities.push_back(new Enemy(Vector(275.f, 150.f), "Enemy3", 3.f, "Enemy3Dead", "Enemy4"));
	//m_entities.push_back(new Enemy(Vector(375.f, 150.f), "Enemy3", 3.f, "Enemy3Dead", "Enemy4"));
	//m_entities.push_back(new Enemy(Vector(475.f, 150.f), "Enemy3", 3.f, "Enemy3Dead", "Enemy4"));

	//m_entities.push_back(new Enemy(Vector(75.f, 200.f), "Enemy5", 3.f, "Enemy5Dead", "Enemy6"));
	//m_entities.push_back(new Enemy(Vector(175.f, 200.f), "Enemy5", 3.f, "Enemy5Dead", "Enemy6"));
	//m_entities.push_back(new Enemy(Vector(275.f, 200.f), "Enemy5", 3.f, "Enemy5Dead", "Enemy6"));
	//m_entities.push_back(new Enemy(Vector(375.f, 200.f), "Enemy5", 3.f, "Enemy5Dead", "Enemy6"));
	//m_entities.push_back(new Enemy(Vector(475.f, 200.f), "Enemy5", 3.f, "Enemy5Dead", "Enemy6"));
	//
	//m_entities.push_back(new Enemy(Vector(75.f, 250.f), "Enemy7", 3.f, "Enemy7Dead", "Enemy8"));
	//m_entities.push_back(new Enemy(Vector(175.f, 250.f), "Enemy7", 3.f, "Enemy7Dead", "Enemy8"));
	//m_entities.push_back(new Enemy(Vector(275.f, 250.f), "Enemy7", 3.f, "Enemy7Dead", "Enemy8"));
	//m_entities.push_back(new Enemy(Vector(375.f, 250.f), "Enemy7", 3.f, "Enemy7Dead", "Enemy8"));
	//m_entities.push_back(new Enemy(Vector(475.f, 250.f), "Enemy7", 3.f, "Enemy7Dead", "Enemy8"));


	//Walls
	m_wall.CreateWall(Vector(150.f, 560.f), "Wall");
	m_wall.CreateWall(Vector(300.f, 560.f), "Wall");
	m_wall.CreateWall(Vector(450.f, 560.f), "Wall");
	m_wall.CreateWall(Vector(600.f, 560.f), "Wall");

	for (auto& entity : m_wall.GetPieces())
	{
		m_entities.push_back(entity);
	}

	m_flag = m_entities.size();

	//m_wall.GetPieces().clear();
}

Game::~Game()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	IMG_Quit();
	SDL_Quit();
}

void Game::CreateWindow(const char* title, int w, int h)
{
	m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);

	if (m_window == NULL)
		std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	if (m_renderer == NULL)
		std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;

}

void Game::GameLoop()
{
	while (!quit)
	{
		m_startTicks = SDL_GetTicks();

		m_newTime = utils::HireTimeInSeconds();
		m_frameTime = m_newTime - m_currentTime;
		m_currentTime = m_newTime;
		m_accumulator += m_frameTime;

		while (m_accumulator >= TIMESTEP)
		{
			while (SDL_PollEvent(&m_event) != 0)
			{
				if (m_event.type == SDL_QUIT)
					quit = true;
				if (m_canShoot && m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_x)
				{
					m_player->Shoot();
					m_canShoot = false;
				}
				if (m_event.type == SDL_KEYUP && m_event.key.keysym.sym == SDLK_x)
				{
					m_canShoot = true;
				}
			}

			m_accumulator -= TIMESTEP;
		}
		m_alpha = m_accumulator / TIMESTEP;

		Update();
		Render();

		m_frameTicks = SDL_GetTicks() - m_startTicks;
		if (m_frameTicks < 1000 / 60)
			SDL_Delay(1000 / 60 - m_frameTicks);

	}
}

void Game::Update()
{

//	std::function<void(int)> fun = [](int a) {
	//	std::cout << "print" << " " << a << std::endl;
	//};

	//fun(0);

	srand((unsigned int)SDL_GetTicks());
	utils::PrintFps();

	for (const auto& entity : m_entities)
	{
		entity->Update();

		entity->HandleEvents(m_event);

		auto collidable = dynamic_cast<ICollidable*>(entity);
		if (collidable)
		{
			//don't include dead enemies into the vector
			// check nly if we are not deleting the memory
			if (entity->m_tag == "Enemy")
			{
				Enemy* enemy = (Enemy*)entity;
				if (!enemy->m_dead)
				{
					m_collidables.push_back(collidable);
				}
			}
			else if (entity->m_tag == "Wall")
			{
				WallPiece *wallPiece = (WallPiece*)entity;
				if (!wallPiece->m_dead)
				{
					m_collidables.push_back(collidable);
				}
			}
			else
			{
				m_collidables.push_back(collidable);
			}
		}


		if (entity->m_tag == "Player")
		{
			Player* player = (Player*)entity;
			if (!player->m_projectile.m_dead)
			{

				auto collidable = dynamic_cast<ICollidable*>(&player->m_projectile);

				if (collidable)
					m_collidables.push_back(collidable);
			}
		}
		else if (entity->m_tag == "Enemy")
		{
			Enemy* enemy = (Enemy*)entity;
			if (!enemy->m_projectile.m_dead)
			{

				auto collidable = dynamic_cast<ICollidable*>(&enemy->m_projectile);

				if (collidable)
					m_collidables.push_back(collidable);
			}
		}
	}
	this->CheckCollisions(m_collidables);

	if(!m_player->m_dead)
		MoveAndShootEnemies();

	m_collidables.clear();

	std::vector<Entity*>::iterator newEnd = std::remove_if(m_entities.begin(), m_entities.end(), [](Entity* entity) { return entity->Destroy() ; });

	for (std::vector<Entity*>::iterator it = newEnd; it != m_entities.end(); it++)
	{
		if ((*it)->Destroy())
		{
			delete* it;
		}
	}

	m_entities.erase(newEnd, m_entities.end());

	/*for (std::vector<Entity*>::iterator it = m_entities.begin(); it != m_entities.end();)
	{
		if ((*it)->Destroy())
		{
			delete* it;
			it = m_entities.erase(it);
		}
		else
			it++;
	}*/

}

void Game::Render()
{
	SDL_RenderClear(m_renderer);

	for (auto& entity : m_entities)
	{
		if (m_player->m_dead)
			SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
		entity->Render(m_renderer);
	}

	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(m_renderer, 700, 10, 700, 650);
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

	SDL_RenderPresent(m_renderer);
}

void Game::CheckCollisions(std::vector<ICollidable*>& collidables)
{
	for (auto& entityA : collidables)
	{
		for (auto& entityB : collidables)
		{
			if (entityA != entityB)
			{
				auto entity1 = dynamic_cast<Entity*>(entityA);
				auto entity2 = dynamic_cast<Entity*>(entityB);

				if(entity1->m_tag == "Wall" && entity2->m_tag == "Wall")
				{
					continue;
				}

				if (utils::RectIntersect(*entity1, *entity2))
				{
					entityA->OnCollision(*entityB);
				}
			}
		}
	}
}

void Game::MoveAndShootEnemies()
{
	int maxdis = 680;
	int mindis = 40;

	int MoveDir = 1;

	for (const auto& entity : m_entities)
	{
		if (entity->m_tag != "Enemy")
			continue;

		Enemy* enemy = (Enemy*)entity;
		if (enemy)
		{
			m_enemies.push_back(enemy);
			if (enemy->m_position.m_x >= maxdis && !m_return && !enemy->m_dead)
			{
				if (m_flag < 0)
				{
					m_return = true;
					m_moveDown = true;
				}
			}
			else if (enemy->m_position.m_x <= mindis && m_return && !enemy->m_dead)
			{
				if (m_flag < 0)
				{
					m_return = false;
					m_moveDown = true;
				}
			}

			//for shooting
			if (!enemy->m_dead && enemy->m_projectile.m_dead)
			{
				if (enemy->m_position.m_x <= m_player->m_position.m_x + 25.f && enemy->m_position.m_x >= m_player->m_position.m_x - 25.f)
				{
					int r = utils::Random(0, 100);
					if (r == 5)
						enemy->Shoot();
				}
			}


		}
	}

	if (m_flag >= m_enemies.size() || m_flag < 0)
		m_flag = m_enemies.size() - 1;


	if (!m_return)
	{
		m_enemies[m_flag]->m_position.m_x += 10.f;
	}
	else
		m_enemies[m_flag]->m_position.m_x -= 10.f;


	if (m_moveDown)
	{
		m_enemies[m_flag]->m_position.m_y += 10.f;
		if(m_flag == 0)
			m_moveDown = false;
	}


	m_enemies[m_flag]->Animate();
	m_flag--;
	m_enemies.clear();
}