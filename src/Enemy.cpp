#include"Enemy.h"

Enemy::Enemy(const Vector& pos, const std::string& key, const float& scale, const std::string& enemyDeadTextureKey, const std::string& enemySecondTextureKey)
	:Entity(pos, key, scale), m_projectile(Vector(-100.f, -100.f), Vector(0.f, 0.f), "Projectile", 3.5f, "ProjectileDead")
{
	m_dead = false;
	m_disappear = false;
	m_DeadTexture = AssetManager::GetInstance().Get(enemyDeadTextureKey);

	m_DeadRect.x = 0;
	m_DeadRect.y = 0;

	SDL_QueryTexture(m_DeadTexture, NULL, NULL, &m_DeadRect.w, &m_DeadRect.h);

	m_DeadRect.w *= m_scale;
	m_DeadRect.h *= m_scale;

	m_SecondTexture = AssetManager::GetInstance().Get(enemySecondTextureKey);

	m_animateCounter = 0;
	animate = false;
	canShoot = true;
	m_shootCounter = 0;
}

void Enemy::Update()
{

	if (!m_dead && m_projectile.m_Dead)
	{
		if (utils::Random(0, 10) == 5)
		{
			if (canShoot)
			{
				canShoot = false;
				Shoot();
			}
		}
	}

	m_shootCounter += 1;
	if (m_shootCounter > 300)
	{
		canShoot = true;
		m_shootCounter = 0;
	}

	if (m_dead)
	{
		m_counter += 0.1f;

		if (m_counter > 4.f)
		{
			m_disappear = true;
			m_position = Vector(-10.f, -10.f);
		}
	}
	else
		m_counter = 0.f;

	m_projectile.Update();

}

void Enemy::Render(SDL_Renderer* renderer)
{
	SDL_Rect src;
	SDL_Rect dst;

	if (!m_dead && !m_disappear)
	{
		src.x = 0;
		src.y = 0;
		src.w = m_textureRect.w;
		src.h = m_textureRect.h;

		dst.x = m_position.GetX() - m_textureRect.w / 2;
		dst.y = m_position.GetY() - m_textureRect.h / 2;
		dst.w = src.w;
		dst.h = src.h;

		m_animateCounter += 1;

		if (m_animateCounter % 130 == 0)
		{
			animate = !animate;
		}

		if(animate)
			SDL_RenderCopy(renderer, m_texture, &src, &dst);
		else if(!animate)
			SDL_RenderCopy(renderer, m_SecondTexture, &src, &dst);

		m_projectile.Render(renderer);

	}
	else if(!m_disappear)
	{
		src.x = 0;
		src.y = 0;
		src.w = m_DeadRect.w;
		src.h = m_DeadRect.h;

		dst.x = m_position.GetX() - m_DeadRect.w / 2;
		dst.y = m_position.GetY() - m_DeadRect.h / 2;
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(renderer, m_DeadTexture, &src, &dst);
	}
}

void Enemy::Dead()
{
	m_dead = true;
}
void Enemy::Shoot()
{
	m_projectile.m_Dead = false;
	m_projectile.m_position = Vector(m_position.GetX(), m_position.GetY() + m_textureRect.h / 2);
	m_projectile.m_velocity.SetY(6.0f);
}

bool Enemy::CheckProjectileCollision(Entity& e)
{
	if (utils::RectIntersect(e, m_projectile))
	{
		m_projectile.m_Dead = true;
		return true;
	}

	return false;
}