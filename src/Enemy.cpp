#include"Enemy.h"
#include"Player.h"
#include"Event.h"

Enemy::Enemy(const Vector& pos, const SDL_Rect& textureRect, const float& scale, const SDL_Rect& enemyDeadTextureRect, int enemyLevel, Game* game)
	:Entity(pos, textureRect, scale, "Enemy", game),
	m_projectile(Vector(-100.f, -100.f), 0.f, { 120, 54, 1, 6 }, 3.f, { 117, 45, 6, 8 }, "Enemy"),
	m_enemyLevel(enemyLevel)
{
	m_dead = false;
	m_disappear = false;

	m_deadTextureRect = enemyDeadTextureRect;

	int offset = 144;
	if (enemyLevel == 2)
		offset += 9;
	else if (enemyLevel == 3)
		offset += 9 * 2;

	m_redTextureRect = { textureRect.x, offset, textureRect.w, textureRect.h };

	animate = false;
	canShoot = true;
	m_shootCounter = 0;
	m_makeRed = false;
}

void Enemy::Update(float dt)
{
	if (m_dead && !m_disappear)
	{
		if (!m_deadTimer.IsStarted())
			m_deadTimer.Start();
		
		if (m_deadTimer.GetTicks() * 0.001f > 0.3f)
		{
			m_disappear = true;
			m_deadTimer.Stop();
		}
	}

	m_projectile.Update(dt);
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
				tempRect = m_redTextureRect;
		}
		else
		{
			tempRect = m_textureRect;
			tempRect.x += 9;//for second enemy Texture
			if (m_makeRed)
			{
				tempRect = m_redTextureRect;
				tempRect.x = m_redTextureRect.x + 9;
			}
		}

		dst.x = m_position.m_x - tempRect.w / 2 * m_scale;
		dst.y = m_position.m_y - tempRect.h / 2 * m_scale;
		dst.w = tempRect.w * m_scale;
		dst.h = tempRect.h * m_scale;

		SDL_RenderCopy(renderer, m_texture, &tempRect, &dst);

	}
	else if(!m_disappear)
	{
		SDL_Rect tempRect = m_deadTextureRect;

		if (m_makeRed)
			tempRect.y = 145; //just for red enemy death effect if player dies after shooting

		dst.x = m_position.m_x - tempRect.w / 2 * m_scale;
		dst.y = m_position.m_y - tempRect.h / 2 * m_scale;
		dst.w = tempRect.w * m_scale;
		dst.h = tempRect.h * m_scale;


		SDL_RenderCopy(renderer, m_texture, &tempRect, &dst);
	}

	m_projectile.Render(renderer);

}

void Enemy::Shoot()
{
	m_projectile.m_dead = false;
	m_projectile.m_position = Vector(m_position.m_x, m_position.m_y + m_textureRect.h / 2 + 10);
	m_projectile.m_velocity = 600.0f;
}

void Enemy::Animate()
{
	animate = !animate;
}

void Enemy::OnCollision(ICollidable& otherCollidable)
{
	if (m_dead)
		return;

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
		scoreEvent.entityTag = "Player";
		scoreEvent.action = [score](Entity& entity)
			{
				Player* player = dynamic_cast<Player*>(&entity);
				player->AddScore(score);
			};

		this->AddEvent(scoreEvent);
	}
}

bool Enemy::Destroy()
{
	return (m_disappear && m_projectile.m_dead);
}

void Enemy::EnemyRed()
{
	m_makeRed = !m_makeRed;
}

void Enemy::Reset()
{
	m_makeRed = false;
	m_disappear = false;
	m_dead = false;
	m_position = Vector(-10.f, -10.f);
}