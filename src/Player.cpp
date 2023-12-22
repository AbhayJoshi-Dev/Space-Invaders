#include"Player.h"

Player::Player(const Vector& pos, const SDL_Rect& playertextureRect, const float& scale, const SDL_Rect& playerDeadTexture1Rect, const SDL_Rect& playerDeadTexture2Rect)
	:Entity(pos, playertextureRect, scale, "Player"), m_moveSpeed(4.f), m_projectile(Vector(-10.f, 0.f), Vector(0.f, 0.f), { 120, 54, 1, 6 }, 3.f, { 117, 45, 6, 8 }, "Player")
{
	m_dead = false;


	m_deathRect1 = playerDeadTexture1Rect;


	m_deathRect2 = playerDeadTexture2Rect;

	m_lives = 3;


	m_animate = false;
}

void Player::Update()
{
	m_projectile.Update();

	if (m_dead && !m_deadTimer.IsStarted())
		m_deadTimer.Start();

	if (m_deadTimer.GetTicks() > 2000.f)
	{
		if (m_lives <= 0)
			Reset();
		m_dead = false;
		m_deadTimer.Stop();
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


		//src.x = 0;
		//src.y = 0;
		//src.w = tempRect.w;
		//src.h = tempRect.h;

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
	if (!m_dead)
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
	}
}

void Player::Reset()
{

}

void Player::Shoot()
{
	if (m_projectile.m_dead)
	{
		m_projectile.m_dead = false;
		m_projectile.m_position = Vector(m_position.m_x, m_position.m_y - m_textureRect.h / 2 - m_projectile.m_textureRect.h / 2 - 1);
		m_projectile.m_velocity.m_y = -10.0f;
		SoundManager::GetInstance().Play("Shoot");
	}
}

void Player::Dead()
{
	if (!m_dead)
	{
		m_dead = true;
		m_lives--;
	}
}

void Player::OnCollision(ICollidable& otherCollidable)
{
	if (!m_dead)
	{
		const auto& proj = dynamic_cast<Projectile*>(&otherCollidable);

		if (proj == NULL)
			return;

		if (proj->m_parentTag == "Enemy")
		{
			Dead();
			proj->m_dead = true;
		}
	}
}