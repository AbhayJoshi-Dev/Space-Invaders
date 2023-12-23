#include"Enemy.h"

Enemy::Enemy(const Vector& pos, const SDL_Rect& textureRect, const float& scale, const SDL_Rect& enemyDeadTextureRect, const SDL_Rect& enemySecondTextureRect)
	:Entity(pos, textureRect, scale, "Enemy"), m_projectile(Vector(-100.f, -100.f), Vector(0.f, 0.f), { 120, 54, 1, 6 }, 3.f, { 117, 45, 6, 8 }, "Enemy")
{
	m_dead = false;
	m_disappear = false;
	/*m_DeadTexture = AssetManager::GetInstance().Get(enemyDeadTextureKey);

	m_DeadRect.x = 0;
	m_DeadRect.y = 0;

	SDL_QueryTexture(m_DeadTexture, NULL, NULL, &m_DeadRect.w, &m_DeadRect.h);

	m_DeadRect.w *= m_scale;
	m_DeadRect.h *= m_scale;

	m_SecondTexture = AssetManager::GetInstance().Get(enemySecondTextureKey);*/


	m_deadTextureRect = enemyDeadTextureRect;
	//m_deadTextureRect.w *= m_scale;
	//m_deadTextureRect.h *= m_scale;

	m_secondTextureRect = enemySecondTextureRect;
	//m_secondTextureRect.w *= m_scale;
	//m_secondTextureRect.h *= m_scale;

	animate = false;
	canShoot = true;
	m_shootCounter = 0;
}

void Enemy::Update()
{

	if (m_dead)
	{
		if (!m_deadTimer.IsStarted())
			m_deadTimer.Start();
		
		if (m_deadTimer.GetTicks() * 0.001f > 0.3f)
		{
			m_disappear = true;
		}
	}

	m_projectile.Update();

}

void Enemy::Render(SDL_Renderer* renderer)
{
	SDL_Rect dst;

	if (!m_dead && !m_disappear)
	{
		SDL_Rect tempRect;

		if (animate)
			tempRect = m_textureRect;
		else
			tempRect = m_secondTextureRect;

		dst.x = m_position.m_x - tempRect.w / 2 * m_scale;
		dst.y = m_position.m_y - tempRect.h / 2 * m_scale;
		dst.w = tempRect.w * m_scale;
		dst.h = tempRect.h * m_scale;

		SDL_RenderCopy(renderer, m_texture, &tempRect, &dst);

	}
	else if(!m_disappear)
	{

		dst.x = m_position.m_x - m_deadTextureRect.w / 2 * m_scale;
		dst.y = m_position.m_y - m_deadTextureRect.h / 2 * m_scale;
		dst.w = m_deadTextureRect.w * m_scale;
		dst.h = m_deadTextureRect.h * m_scale;

		SDL_RenderCopy(renderer, m_texture, &m_deadTextureRect, &dst);
	}

	m_projectile.Render(renderer);

}

void Enemy::Shoot()
{
	m_projectile.m_dead = false;
	m_projectile.m_position = Vector(m_position.m_x, m_position.m_y + m_textureRect.h / 2 + 10);
	m_projectile.m_velocity.m_y = 7.0f;
}

void Enemy::Animate()
{
	animate = !animate;
}

void Enemy::OnCollision(ICollidable& otherCollidable)
{
	if (!m_dead)
	{
		const auto& proj = dynamic_cast<Projectile*>(&otherCollidable);

		if (proj == NULL)
			return;

		if (proj->m_parentTag == "Player")
		{
			SoundManager::GetInstance().Play("InvaderKilled");

			m_dead = true;
			proj->m_dead = true;
		}
	}
}

bool Enemy::Destroy()
{
	return (m_disappear && m_projectile.m_dead);
}