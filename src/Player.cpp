#include"Player.h"

Player::Player(const Vector& pos, const std::string& key, const float& scale, const std::string& playerDeadKey1, const std::string& playerDeadKey2)
	:Entity(pos, key, scale), m_moveSpeed(4.5f), m_projectile(Vector(0.f, 0.f), Vector(0.f, -7.f), "Projectile", 3.5f)
{
	m_isFired = false;
	m_dead = false;

	m_deathTexture1 = AssetManager::GetInstance().Get(playerDeadKey1);
	SDL_QueryTexture(m_deathTexture1, NULL, NULL, &m_deathRect1.w, &m_deathRect1.h);
	m_deathRect1.x = 0;
	m_deathRect1.y = 0;
	m_deathRect1.w *= m_scale;
	m_deathRect1.h *= m_scale;

	m_deathTexture2 = AssetManager::GetInstance().Get(playerDeadKey2);
	SDL_QueryTexture(m_deathTexture2, NULL, NULL, &m_deathRect2.w, &m_deathRect2.h);
	m_deathRect2.x = 0;
	m_deathRect2.y = 0;
	m_deathRect2.w *= m_scale;
	m_deathRect2.h *= m_scale;

}

void Player::Update()
{
	m_projectile.Update();

	if (m_projectile.m_isDead)
		m_isFired = false;
}

void Player::Render(SDL_Renderer* renderer)
{

	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = m_textureRect.w;
	src.h = m_textureRect.h;

	SDL_Rect dst;
	dst.x = m_position.GetX() - m_textureRect.w / 2;
	dst.y = m_position.GetY() - m_textureRect.h / 2;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, m_texture, &src, &dst);

	if(m_isFired && !m_projectile.m_isDead)
		m_projectile.Render(renderer);

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

	if (keystate[SDL_SCANCODE_X] && !m_isFired && m_projectile.m_isDead)
		Shoot();
}

void Player::Shoot()
{
	m_isFired = true;
	m_projectile.m_isDead = false;
	m_projectile.m_position = Vector(m_position.GetX(), m_position.GetY() - m_textureRect.h / 2);
}

bool Player::CheckProjectileCollision(Entity& e)
{
	if (utils::RectIntersect(e, m_projectile))
	{
		m_projectile.m_isDead = true;
		return true;
	}

	return false;
}

void Player::Dead()
{
	m_dead = true;
}