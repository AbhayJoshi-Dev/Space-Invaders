#include"Game.h"

#include<functional>

Game::Game()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;

	int imgFlag = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlag) & imgFlag))
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;

	CreateWindow("Space Invaders", 1280, 720);//320, 180

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

	//creating entities

	auto ptr = std::make_unique<Player>(Vector(300.f, 675.f), "Player", 3.f, "PlayerDeath1", "PlayerDeath2");
	m_player = ptr.get();
	m_entities.push_front(std::move(ptr));
	m_entities.push_front(std::make_unique<Enemy>(Vector(200.f, 100.f), "Enemy1", 3.f, "Enemy1Dead", "Enemy2"));
	m_entities.push_front(std::make_unique<Enemy>(Vector(400.f, 100.f), "Enemy3", 3.f, "Enemy3Dead", "Enemy4"));
	m_entities.push_front(std::make_unique<Enemy>(Vector(600.f, 100.f), "Enemy5", 3.f, "Enemy5Dead", "Enemy6"));
	m_entities.push_front(std::make_unique<Enemy>(Vector(800.f, 100.f), "Enemy7", 3.f, "Enemy7Dead", "Enemy8"));
	m_entities.push_front(std::make_unique<Enemy>(Vector(200.f, 200.f), "Enemy1", 3.f, "Enemy1Dead", "Enemy2"));
	m_entities.push_front(std::make_unique<Enemy>(Vector(400.f, 200.f), "Enemy3", 3.f, "Enemy3Dead", "Enemy4"));
	m_entities.push_front(std::make_unique<Enemy>(Vector(600.f, 200.f), "Enemy5", 3.f, "Enemy5Dead", "Enemy6"));
	m_entities.push_front(std::make_unique<Enemy>(Vector(800.f, 200.f), "Enemy7", 3.f, "Enemy7Dead", "Enemy8"));
	//Walls
	/*m_entities.push_front(std::make_unique<WallPiece>(Vector(200.f, 500.f), "Wall", Square));
	m_entities.push_front(std::make_unique<WallPiece>(Vector(200.f, 524.f), "Wall", Square));
	m_entities.push_front(std::make_unique<WallPiece>(Vector(224.f, 524.f), "Wall", Square));
	m_entities.push_front(std::make_unique<WallPiece>(Vector(176.f, 524.f), "Wall", Square));
	m_entities.push_front(std::make_unique<WallPiece>(Vector(224.f, 548.f), "Wall", Square));
	m_entities.push_front(std::make_unique<WallPiece>(Vector(176.f, 548.f), "Wall", Square));
	m_entities.push_front(std::make_unique<WallPiece>(Vector(222.5f, 501.5f), "Wall", RightTriangle));
	m_entities.push_front(std::make_unique<WallPiece>(Vector(177.5f, 501.5f), "Wall", LeftTriangle));*/

	m_wall.CreateWall(Vector(200.f, 500.f), "Wall");
	m_wall.CreateWall(Vector(400.f, 500.f), "Wall");
	m_wall.CreateWall(Vector(600.f, 500.f), "Wall");
	m_wall.CreateWall(Vector(800.f, 500.f), "Wall");

	for (auto& entity : m_wall.GetPieces())
	{
		m_entities.push_front(entity);
	}
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
		if (m_frameTicks < 1000 / 120)
			SDL_Delay(1000 / 120 - m_frameTicks);

	}
}

void Game::Update()
{

//	std::function<void(int)> fun = [](int a) {
	//	std::cout << "print" << " " << a << std::endl;
	//};

	//fun(0);

	srand((unsigned int)time(0));
	utils::PrintFps();

	std::forward_list<ICollidable*> collidables;

	for (const auto& entity : m_entities)
	{
		entity->Update();

		entity->HandleEvents(m_event);

		auto collidable = dynamic_cast<ICollidable*>(entity.get());
		if (collidable)
		{
			collidables.push_front(collidable);
		}


		if (entity->m_tag == "Player")
		{
			const auto& player = dynamic_cast<Player*>(entity.get());
			if (!player->m_projectile.m_Dead)
			{

				auto collidable = dynamic_cast<ICollidable*>(&player->m_projectile);

				if (collidable)
					collidables.push_front(collidable);
			}
		}
		else if (entity->m_tag == "Enemy")
		{
			const auto& enemy = dynamic_cast<Enemy*>(entity.get());
			if (!enemy->m_projectile.m_Dead)
			{

				auto collidable = dynamic_cast<ICollidable*>(&enemy->m_projectile);

				if (collidable)
					collidables.push_front(collidable);
			}
		}
	}
	this->CheckCollisions(collidables);

	m_entities.remove_if([](const auto& entity)
		{ 
			return entity->Destroy();
		}
	);
}

void Game::Render()
{
	SDL_RenderClear(m_renderer);

	for (auto& entity : m_entities)
	{
		entity->Render(m_renderer);
	}

	SDL_RenderPresent(m_renderer);
}

void Game::CheckCollisions(std::forward_list<ICollidable*>& collidables)
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
					std::cout << "Collision" << std::endl;
					entityA->OnCollision(*entityB);
				}
			}
		}
	}
}