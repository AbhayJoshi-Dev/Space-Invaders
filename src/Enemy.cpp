#include"Enemy.h"
#include"Player.h"
#include"Event.h"

Enemy::Enemy(const Vector& pos, const SDL_Rect& textureRect, const float& scale, const SDL_Rect& enemyDeadTextureRect, const SDL_Rect& enemySecondTextureRect, int enemyLevel, Game* game)
	:Entity(pos, textureRect, scale, "Enemy", game),
	m_projectile(Vector(-100.f, -100.f), Vector(0.f, 0.f), { 120, 54, 1, 6 }, 3.f, { 117, 45, 6, 8 }, "Enemy"),
	m_enemyLevel(enemyLevel)
{
	m_dead = false;
	m_disappear = false;

	m_deadTextureRect = enemyDeadTextureRect;

	m_secondTextureRect = enemySecondTextureRect;

	animate = false;
	canShoot = true;
	m_shootCounter = 0;
	m_makeRed = false;
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
		int y;
		int x;

		if (animate)
		{
			tempRect = m_textureRect;
			if (m_makeRed)
			{
				y = 144 + m_textureRect.y;
			}
		}
		else
		{
			tempRect = m_secondTextureRect;
			x = 9 + m_textureRect.y;
			y = 144 + m_textureRect.y;
		}

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

			int score = 10 * m_enemyLevel;

			Event scoreEvent;
			scoreEvent.action = [score](Entity& entity)
				{
					Player* player = dynamic_cast<Player*>(&entity);
					player->AddScore(score);
				};

			this->AddEvent(scoreEvent);
		}
	}
}

bool Enemy::Destroy()
{
	return (m_disappear && m_projectile.m_dead);
}

void Enemy::MakeEnemyRed()
{
	m_makeRed = true;
}