#include"Player.h"

Player::Player(const AssetManager& assetManager, const Vector& pos, const std::string& key, const float& scale)
	:Entity(assetManager, pos, key, scale), m_moveSpeed(4.5f)
{
	isfiring = false;
	m_fireCooldown = 5.f;
	m_counter = 0.f;
}

void Player::Update()
{
	m_counter += 0.05f;
	if (m_counter >= m_fireCooldown)
	{
		m_counter = 0.f;
		isfiring = false;
	}
}

void Player::Render(SDL_Renderer* renderer)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = m_textureRect.w;
	src.h = m_textureRect.h;

	SDL_Rect dst;
	dst.x = m_position.GetX();
	dst.y = m_position.GetY();
	dst.w = src.w * m_scale;
	dst.h = src.h * m_scale;

	SDL_RenderCopy(renderer, m_texture, &src, &dst);
}

void Player::HandleEvents(SDL_Event& event)
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT])
	{
		m_position.SetX(m_position.GetX() + m_moveSpeed);
	}
	if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT])
	{
		m_position.SetX(m_position.GetX() - m_moveSpeed);
	}

	if (keystate[SDL_SCANCODE_X] && !isfiring)
	{
		isfiring = true;
		std::cout << "Fire" << std::endl;
	}
}