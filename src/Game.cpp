#include"Game.h"
#include"Event.h"
#include"fstream"

Game::Game()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;

	int imgFlag = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlag) & imgFlag))
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1028) < 0)
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;

	if(TTF_Init() < 0)
		std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;

	CreateWindow("Space Invaders", 880, 660);//320, 180

	quit = false;

	//Texture Loading
	AssetManager::GetInstance().Load(m_renderer, "Sheet", "res/gfx/sheet.png");

	//Audio Loading
	SoundManager::GetInstance().Load("res/audio/shoot.wav", "Shoot");
	SoundManager::GetInstance().Load("res/audio/invaderkilled.wav", "InvaderKilled");

	m_font = nullptr;

	//Loading Font
	m_font = TTF_OpenFont("res/font/04B_03__.ttf", 40);

	if (!m_font)
		std::cout << "Font not loaded" << std::endl;

	//instead of loading every texture, entity is just taking a SDL_Rect which tells where the texture is in the sheet

	//creating entities                            playertexture        playerDeadtexture1   playerDeadtexture2
	m_player = new Player(Vector(300.f, 600.f), { 115, 63, 11, 8 }, 3.f, { 132, 63, 13, 8 }, { 147, 63, 15, 8 });

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
			case 0:                                                //enemytexture1        enemyDeadtexture   enemytexture2
				m_entities.push_back(new Enemy(Vector(XPos, YPos), { 1, 19, 6, 8 }, 3.f, { 103, 1, 7, 7 }, { 10, 19, 6, 8 }, 3, this));
				break;
			case 1:
				m_entities.push_back(new Enemy(Vector(XPos, YPos), { 0, 9, 7, 8 }, 3.f, { 103, 1, 7, 7 }, { 9, 9, 7, 8 }, 2, this));
				break;
			case 2:
				m_entities.push_back(new Enemy(Vector(XPos, YPos), { 0, 45, 7, 8 }, 3.f, { 103, 37, 7, 7 }, { 9, 45, 7, 8 }, 2, this));
				break;
			case 3:
				m_entities.push_back(new Enemy(Vector(XPos, YPos), { 0, 36, 8, 8 }, 3.f, { 103, 37, 7, 7 }, { 9, 36, 8, 8 }, 1, this));
				break;
			case 4:
				m_entities.push_back(new Enemy(Vector(XPos, YPos), { 0, 72, 8, 8 }, 3.f, { 103, 73, 7, 7 }, { 9, 72, 8, 8 }, 1, this));
				break;
			}
			XPos += xSpacing;
		}
		YPos += ySpacing;
		XPos = 50;
	}


	//Walls
	m_wall.CreateWall(Vector(150.f, 520.f));//150,  560
	m_wall.CreateWall(Vector(300.f, 520.f));
	m_wall.CreateWall(Vector(450.f, 520.f));
	m_wall.CreateWall(Vector(600.f, 520.f));

	for (auto& entity : m_wall.GetPieces())
	{
		m_entities.push_back(entity);
	}

	m_entities.push_back(new Entity( Vector(750.f, 600), { 115, 63, 11, 8 }, 3.f, "PlayerLiveUI" ));
	m_entities.push_back(new Entity( Vector(800.f, 600), { 115, 63, 11, 8 }, 3.f, "PlayerLiveUI" ));

	m_flag = m_entities.size();

	m_highScore = GetHighScore();
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
				if (!m_player->m_dead && m_canShoot && m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_x)
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

	if (m_player->m_lives < 0)
		m_resetgame = true;
		

	srand((unsigned int)SDL_GetTicks());
	utils::PrintFps();

	for (Entity* entity : m_entities)
	{
		entity->Update();

		entity->HandleEvents(m_event);

		//check for every if they are collidable and them into a vector
		ICollidable* collidable = dynamic_cast<ICollidable*>(entity);
		if (collidable)
		{
			//adding alive enemies to colllidable vector
			if (entity->m_tag == "Enemy")
			{
				Enemy* enemy = (Enemy*)entity;

				//don't include dead enemies into the vector
				// check this only if we are not deleting the allocated memory
				if (!enemy->m_dead)
					m_collidables.push_back(collidable);
			}
			//adding alive enemies to colllidable vector
			else if (entity->m_tag == "Wall")
			{
				WallPiece *wallPiece = (WallPiece*)entity;

				//don't include dead enemies into the vector
				// check this only if we are not deleting the allocated memory
				if (!wallPiece->m_dead)
					m_collidables.push_back(collidable);
			}
			else
			{
				m_collidables.push_back(collidable);
			}
		}

		if (!entity)
			continue;

		//adding enemy projectile in the collidable vector
		if (entity->m_tag == "Enemy")
		{
			Enemy* enemy = (Enemy*)entity;
			if (!enemy->m_projectile.m_dead)
			{
				ICollidable* col = dynamic_cast<ICollidable*>(&enemy->m_projectile);
				if (col)
					m_collidables.push_back(col);
			}
		}

		while (!m_events.empty())
		{
			Event& event = m_events.back();
			if (entity->m_tag == "Player")
				event.action(*entity);
				
			m_events.pop_back();
		}



		/*for (Event& event : m_events)
		{
			if (entity->m_tag == "Player")
				event.action(*entity);
		}
		m_events.clear();*/
	}

	//adding player projectile in the collidable vector
	if (!m_player->m_projectile.m_dead)
	{
		ICollidable* collidable = dynamic_cast<ICollidable*>(&m_player->m_projectile);
		if (collidable)
			m_collidables.push_back(collidable);
	}


	this->CheckCollisions(m_collidables);

	if(!m_player->m_dead)
		MoveAndShootEnemies();

	m_collidables.clear();


	//deleting heap allocated entitiies when they are dead
	//std::vector<Entity*>::iterator newEnd = std::remove_if(m_entities.begin(), m_entities.end(), [](Entity* entity) { return entity->Destroy() ; });

	//for (std::vector<Entity*>::iterator it = newEnd; it != m_entities.end(); it++)
	//{
	//	if ((*it)->Destroy())
	//	{
	//		delete* it;
	//	}
	//}

	//m_entities.erase(newEnd, m_entities.end());

}

void Game::Render()
{
	SDL_RenderClear(m_renderer);

	for (auto& entity : m_entities)
	{
		//if (m_player->m_dead)
		//	SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
		entity->Render(m_renderer);
	}

	RenderText(Vector(700.f, 35.f), "HIGH", white);
	RenderText(Vector(750.f, 65.f), "SCORE", white);

	int score = m_player->m_score;

	if (score > m_highScore)
	{
		SetHighScore(score);
		m_highScore = score;
	}

	char buffer[10];
	sprintf_s(buffer, "%d", m_highScore);

	RenderText(Vector(750.f, 100.f), buffer, white);


	RenderText(Vector(700.f, 250.f), "SCORE", white);
	sprintf_s(buffer, "%d", score);
	RenderText(Vector(750.f, 300.f), buffer, white);


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

				//Don't check for Wall To Wall colision
				if(entity1->m_tag == "Wall" && entity2->m_tag == "Wall")
					continue;
				//Don't check for Enemy To Enemy colision
				if (entity1->m_tag == "Enemy" && entity2->m_tag == "Enemy")
					continue;
				//Don't check for Wall To Player colision
				if ((entity1->m_tag == "Wall" && entity2->m_tag == "Player")
					|| entity1->m_tag == "Player" && entity2->m_tag == "Wall")
					continue;

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
	int maxdis = 650;
	int mindis = 40;

	int MoveDir = 1;
	int numBullets = 0;

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

			//enemy shooting
			if (!enemy->m_dead && enemy->m_projectile.m_dead)
			{
				if (enemy->m_position.m_x <= m_player->m_position.m_x + 25.f 
					&& enemy->m_position.m_x >= m_player->m_position.m_x - 25.f)
				{
					int r = utils::Random(0, 200);
					if (r == 5)
					{
						enemy->Shoot();
						numBullets++;
					}
				}
			}
		}
	}

	if (m_enemies.empty())
		return;

	if (m_flag >= m_enemies.size() || m_flag < 0)
	{
		m_flag = m_enemies.size() - 1;
	}

	if (!m_return)
		m_enemies[m_flag]->m_position.m_x += 10.f;
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

void Game::RenderText(const Vector& position, const char* str, const SDL_Color& color)
{
	if (!m_font)
		return;

	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(m_font, str, color);
	SDL_Texture* message = SDL_CreateTextureFromSurface(m_renderer, surfaceMessage);

	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = surfaceMessage->w;
	src.h = surfaceMessage->h;

	SDL_Rect dst;
	dst.x = position.m_x;
	dst.y = position.m_y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(m_renderer, message, &src, &dst);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}

void Game::AddEvent(const Event& event)
{
	m_events.push_back(event);
}

int Game::GetHighScore()
{
	int highScore;
	std::ifstream input("data.txt");

	input >> highScore;

	return highScore;
}

void Game::SetHighScore(int score)
{
	std::ofstream output("data.txt");
	output << score;
}