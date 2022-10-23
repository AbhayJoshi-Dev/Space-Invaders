#include"Enemy.h"

Enemy::Enemy(const Vector& pos, const std::string& key, const float& scale, const std::string& enemyDeadTextureKey, const std::string& enemySecondTextureKey)
	:Entity(pos, key, scale, "Enemy"), m_projectile(Vector(-100.f, -100.f), Vector(0.f, 0.f), "Projectile", 3.f, "ProjectileDead", "Enemy")
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
		if (utils::Random(0, 15) == 5)
		{
			if (canShoot)
			{
				canShoot = false;
				Shoot();
			}
		}
	}

	m_shootCounter += 1;
	if (m_shootCounter > 600)
	{
		canShoot = true;
		m_shootCounter = 0;
	}

	if (m_dead)
	{
		if (!m_timer.IsStarted())
			m_timer.Start();
		
		if (m_timer.GetTicks() * 0.001f > 0.3f)
		{
			m_disappear = true;
		}
	}
	//else
	//{
	//	if(m_timer.IsStarted())
		//	m_timer.Stop();
//	}

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

		dst.x = m_position.m_x - m_textureRect.w / 2;
		dst.y = m_position.m_y - m_textureRect.h / 2;
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
	}
	else if(!m_disappear)
	{
		src.x = 0;
		src.y = 0;
		src.w = m_DeadRect.w;
		src.h = m_DeadRect.h;

		dst.x = m_position.m_x - m_DeadRect.w / 2;
		dst.y = m_position.m_y - m_DeadRect.h / 2;
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(renderer, m_DeadTexture, &src, &dst);
	}

	m_projectile.Render(renderer);

}

void Enemy::Shoot()
{
	m_projectile.m_Dead = false;
	m_projectile.m_position = Vector(m_position.m_x, m_position.m_y + m_textureRect.h / 2 + 10);
	m_projectile.m_velocity.m_y = 6.0f;
}

void Enemy::OnCollision(ICollidable& otherCollidable)
{
	if (!m_dead)
	{
		const auto& proj = dynamic_cast<Projectile*>(&otherCollidable);

		if (proj->m_parentTag == "Player")
		{
			m_dead = true;
			proj->m_Dead = true;
		}
	}
}

bool Enemy::Destroy()
{
	return (m_disappear && m_projectile.m_Dead);
}