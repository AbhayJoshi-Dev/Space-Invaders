#include"Game.h"

Game::Game()
	:m_assetManager(std::make_unique<AssetManager>()), m_player(NULL, Vector(200.f, 650.f), 3.5f)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;

	int imgFlag = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlag) & imgFlag))
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;

	CreateWindow("Space Invaders", 1280, 720);

	quit = false;

	m_assetManager->Load(m_renderer, "Player", "res/gfx/Player.png");
	m_assetManager->Load(m_renderer, "Projectile", "res/gfx/Projectile.png");

	m_player.SetTexture(m_assetManager->Get("Player"));
	//m_entities.push_back(std::make_unique<Player>(*m_assetManager, Vector(200.f, 650.f), "Player", 3.5f));
	
	fire = true;
	m_fireCooldown = 10.0f;
	m_counter = 0.f;

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
			}

			m_accumulator -= TIMESTEP;
		}
		m_alpha = m_accumulator / TIMESTEP;

		const Uint8* keystate = SDL_GetKeyboardState(NULL);
		if (keystate[SDL_SCANCODE_X] && fire)
		{
			PlayerFiring();
		}

		Update();
		Render();

		m_frameTicks = SDL_GetTicks() - m_startTicks;
		if (m_frameTicks < 1000 / 120)
			SDL_Delay(1000 / 120 - m_frameTicks);

	}
}

void Game::Update()
{
	utils::PrintFps();

	for (auto& entity : m_entities)
		entity->Update();

	for (auto& entity : m_entities)
		entity->HandleEvents(m_event);

	m_player.Update();
	m_player.HandleEvents(m_event);

	m_counter += 0.05f;
	if (m_counter >= m_fireCooldown)
	{
		m_counter = 0.f;
		fire = true;
	}
}

void Game::Render()
{
	SDL_RenderClear(m_renderer);

	for (auto& entity : m_entities)
	{
		entity->Render(m_renderer);
	}

	m_player.Render(m_renderer);

	SDL_RenderPresent(m_renderer);
}

void Game::PlayerFiring()
{
	fire = false;
	m_entities.push_back(std::make_unique<Projectile>(*m_assetManager, Vector(m_player.m_position.GetX(), m_player.m_position.GetY()), Vector(0.f, -1.f), "Projectile", 3.5f));
	std::cout << "Fire" << std::endl;
}