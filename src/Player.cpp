#include"Player.h"

Player::Player(const Vector& pos, const std::string& key, const float& scale, const std::string& playerDeadKey1, const std::string& playerDeadKey2)
	:Entity(pos, key, scale, key), m_moveSpeed(2.5f), m_projectile(Vector(0.f, 0.f), Vector(0.f, -7.f), "Projectile", 3.5f, "ProjectileDead", "Player")
{
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

	m_animate = false;
	m_animateCounter = 0;
}

void Player::Update()
{
	m_projectile.Update();
}

void Player::Render(SDL_Renderer* renderer)
{
	SDL_Rect src;
	SDL_Rect dst;

	if (!m_dead)
	{
		src.x = 0;
		src.y = 0;
		src.w = m_textureRect.w;
		src.h = m_textureRect.h;

		dst.x = m_position.m_x - m_textureRect.w / 2;
		dst.y = m_position.m_y - m_textureRect.h / 2;
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(renderer, m_texture, &src, &dst);
	}
	else if (m_dead)
	{
		m_animateCounter += 1;

		if (m_animateCounter % 25 == 0)
		{
			m_animate = !m_animate;
		}

		if (m_animate)
		{
			src.x = 0;
			src.y = 0;
			src.w = m_deathRect1.w;
			src.h = m_deathRect1.h;

			dst.x = m_position.m_x - m_deathRect1.w / 2;
			dst.y = m_position.m_y - m_deathRect1.h / 2;
			dst.w = src.w;
			dst.h = src.h;
			SDL_RenderCopy(renderer, m_deathTexture1, &src, &dst);
		}

		else if (!m_animate)
		{
			src.x = 0;
			src.y = 0;
			src.w = m_deathRect2.w;
			src.h = m_deathRect2.h;

			dst.x = m_position.m_x - m_deathRect2.w / 2;
			dst.y = m_position.m_y - m_deathRect2.h / 2;
			dst.w = src.w;
			dst.h = src.h;
			SDL_RenderCopy(renderer, m_deathTexture2, &src, &dst);
		}
	}

	if(!m_projectile.m_Dead)
		m_projectile.Render(renderer);

}

void Player::HandleEvents(SDL_Event& event)
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT])
	{
		m_position.m_x = m_position.m_x + m_moveSpeed;
	}
	if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT])
	{
		m_position.m_x = m_position.m_x - m_moveSpeed;
	}

	if (keystate[SDL_SCANCODE_X] && m_projectile.m_Dead && !m_dead)
		Shoot();

}

void Player::Shoot()
{
	m_projectile.m_Dead = false;
	m_projectile.m_position = Vector(m_position.m_x, m_position.m_y - m_textureRect.h / 2 - 10);
}

/*bool Player::CheckProjectileCollision(Entity& e)
{
	if (utils::RectIntersect(e, m_projectile))
	{
		m_projectile.m_Dead = true;
		return true;
	}

	return false;
}*/

void Player::Dead()
{
	if (!m_dead)
	{
		std::cout << "PlayerDead" << std::endl;
		m_dead = true;
	}
}

void Player::OnCollision(ICollidable* otherCollidable)
{
	
}