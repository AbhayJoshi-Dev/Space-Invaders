#include"Player.h"
#include"Event.h"
#include"Enemy.h"

Player::Player(const Vector& pos, const SDL_Rect& playertextureRect, const float& scale, const SDL_Rect& playerDeadTexture1Rect, const SDL_Rect& playerDeadTexture2Rect, Game* game)
	:Entity(pos, playertextureRect, scale, "Player", game),
	m_moveSpeed(300.f),
	m_projectile(Vector(-10.f, 0.f), 0.f, { 120, 54, 1, 6 }, 3.f, { 117, 45, 6, 8 }, "Player")
{
	m_dead = false;

	m_deathRect1 = playerDeadTexture1Rect;

	m_deathRect2 = playerDeadTexture2Rect;

	m_lives = 2;

	m_score = 0;
	m_animate = false;
	m_canShoot = true;
}

void Player::Update(float dt)
{
	m_dt = dt;
	m_projectile.Update(dt);
	BoundCollision();

	if (m_dead && !m_deadTimer.IsStarted())
		m_deadTimer.Start();

	if (m_dead && m_deadTimer.GetTicks() > 2000.f)
	{
		m_lives--;
		if (m_lives < 0)
		{
			//Reset();
			return;
		}

		m_dead = false;
		m_deadTimer.Stop();

		Event enemyRedfalse;
		enemyRedfalse.entityTag = "Enemy";
		enemyRedfalse.action = [](Entity& entity)
			{
				Enemy* enemy = dynamic_cast<Enemy*>(&entity);
				if (enemy)
					enemy->EnemyRed();
			};
		this->AddEvent(enemyRedfalse);

		Event healthUIRedFalse;
		healthUIRedFalse.entityTag = "PlayerHealthUI";
		healthUIRedFalse.action = [](Entity& entity)
			{
				PlayerHealthUI* health = dynamic_cast<PlayerHealthUI*>(&entity);
				if (health)
					health->HealthRed();
			};
		this->AddEvent(healthUIRedFalse);
	}

}

void Player::Render(SDL_Renderer* renderer)
{
	SDL_Rect dst;

	if (!m_dead)
	{
		dst.x = m_position.m_x - m_textureRect.w / 2 * m_scale;
		dst.y = m_position.m_y - m_textureRect.h / 2 * m_scale;
		dst.w = m_textureRect.w * m_scale;
		dst.h = m_textureRect.h * m_scale;

		SDL_RenderCopy(renderer, m_texture, &m_textureRect, &dst);
	}
	else if (m_dead)
	{
		if (!m_timer.IsStarted())
			m_timer.Start();

		if (m_timer.GetTicks() * 0.001f > .2f)
		{
			m_animate = !m_animate;
			m_timer.Stop();
		}

		SDL_Rect tempRect;
		if (m_animate)
			tempRect = m_deathRect1;
		else
			tempRect = m_deathRect2;

		dst.x = m_position.m_x - tempRect.w / 2 * m_scale;
		dst.y = m_position.m_y - tempRect.h / 2 * m_scale;
		dst.w = tempRect.w * m_scale;
		dst.h = tempRect.h * m_scale;
		SDL_RenderCopy(renderer, m_texture, &tempRect, &dst);

	}

	if(!m_projectile.m_disappear)
		m_projectile.Render(renderer);

}

void Player::HandleEvents(SDL_Event& event)
{
	if (m_dead)
		return;

	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT])
	{
		m_position.m_x = m_position.m_x + m_moveSpeed * m_dt;
	}
	if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT])
	{
		m_position.m_x = m_position.m_x - m_moveSpeed * m_dt;
	}
}

void Player::Reset()
{
	m_dead = false;
	m_lives = 2;
	m_timer.Stop();
	m_deadTimer.Stop();
	m_score = 0;
}

void Player::Shoot()
{
	if (!m_projectile.m_dead)
		return;

	m_projectile.m_dead = false;
	m_projectile.m_position = Vector(m_position.m_x, m_position.m_y - m_textureRect.h / 2 - m_projectile.m_textureRect.h / 2 - 1);
	m_projectile.m_velocity = -800.0f;
	SoundManager::GetInstance().Play("Shoot");
}

void Player::Dead()
{
	m_dead = true;

	Event enemyRedTrue;
	enemyRedTrue.entityTag = "Enemy";
	enemyRedTrue.action = [](Entity& entity)
		{
			Enemy* enemy = dynamic_cast<Enemy*>(&entity);
			if(enemy)
				enemy->EnemyRed();
		};
	this->AddEvent(enemyRedTrue);


	Event healthUIRedTrue;
	healthUIRedTrue.entityTag = "PlayerHealthUI";
	healthUIRedTrue.action = [](Entity& entity)
		{
			PlayerHealthUI* health = dynamic_cast<PlayerHealthUI*>(&entity);
			if (health)
				health->HealthRed();
		};
	this->AddEvent(healthUIRedTrue);

}

void Player::OnCollision(ICollidable& otherCollidable)
{
	if (m_dead)
		return;

	const auto& proj = dynamic_cast<Projectile*>(&otherCollidable);

	if (proj == NULL)
		return;

	if (proj->m_parentTag == "Enemy")
	{
		Dead();
		proj->m_dead = true;
	}
}

void Player::BoundCollision()
{
	if (m_position.m_x >= 650.f)
		m_position.m_x = 650.f;
	else if (m_position.m_x <= 40.f)
		m_position.m_x = 40.f;
}
void Player::AddScore(int score)
{
	m_score += score;
}

PlayerHealthUI::PlayerHealthUI(const Vector& pos, const SDL_Rect& textureRect, const float& scale, const std::string& tag, int deadTextureOffset, Game* game)
	:Entity(pos, textureRect, scale, tag, game), m_deadTextureOffset(deadTextureOffset), m_makeRed(false)
{

}

void PlayerHealthUI::Render(SDL_Renderer* renderer)
{
	if (m_dead)
		return;

	SDL_Rect tempRect = m_textureRect;
	SDL_Rect dst;

	if (m_makeRed)
		tempRect.x = m_deadTextureOffset;

	dst.x = m_position.m_x - tempRect.w / 2 * m_scale;
	dst.y = m_position.m_y - tempRect.h / 2 * m_scale;
	dst.w = tempRect.w * m_scale;
	dst.h = tempRect.h * m_scale;

	SDL_RenderCopy(renderer, m_texture, &tempRect, &dst);
}

void PlayerHealthUI::HealthRed()
{
	m_makeRed = !m_makeRed;
}

void PlayerHealthUI::Reset()
{
	m_dead = false;
	m_makeRed = false;
}