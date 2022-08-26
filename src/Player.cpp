#include"Player.h"

Player::Player(const Vector& pos, const std::string& key, const float& scale)
	:Entity(pos, key, scale), m_moveSpeed(4.5f), m_projectile(Vector(0.f, 0.f), Vector(0.f, 0.f), "Projectile", 3.5f)
{
	fire = false;

}

void Player::Update()
{

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

	if (keystate[SDL_SCANCODE_X])
		Shoot();
}

void Player::Shoot()
{

}