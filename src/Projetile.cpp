#include"Projectile.h"

Projectile::Projectile(const Vector& pos, const Vector& velocity, const SDL_Rect& textureRect, float scale, const SDL_Rect& deadTextureRect, std::string parentTag)
	:Entity(pos, textureRect, scale, "Projectile"), m_velocity(velocity), m_parentTag(parentTag)
{
	//m_texture = AssetManager::GetInstance().Get(key);
	m_dead = true;
	m_disappear = false;
	//m_DeadTex = AssetManager::GetInstance().Get(deadKey);
	//SDL_QueryTexture(m_DeadTex, NULL, NULL, &m_DeadRect.w, &m_DeadRect.h);
	//m_DeadRect.x = 0;
	//m_DeadRect.y = 0;
	//m_DeadRect.w *= m_scale;
	//m_DeadRect.h *= m_scale;


	m_deadRect = deadTextureRect;
	//m_deadRect.w *= m_scale;
	//m_deadRect.h *= m_scale;



	m_boundDead = false;
}

void Projectile::Update()
{
	if (!m_dead)
	{
		m_boundDead = false;
		if (m_timer.IsStarted())
			m_timer.Stop();

		m_disappear = false;
		m_position = m_position + m_velocity;

		if (m_position.m_y > 650 || m_position.m_y < 10)
		{
			m_dead = true;
			m_boundDead = true;
		}
	}
	else if (m_boundDead)
	{
		if (!m_timer.IsStarted())
			m_timer.Start();

		if (m_timer.GetTicks() * 0.001f > 0.3f)
		{
			m_disappear = true;
			m_position = Vector(0.f, 0.f);
		}
	}
}

void Projectile::Render(SDL_Renderer* renderer)
{
	SDL_Rect dst;

	if (!m_dead)
	{

		dst.x = m_position.m_x - (float)m_textureRect.w / 2.f * m_scale;
		dst.y = m_position.m_y - (float)m_textureRect.h / 2.f * m_scale;
		dst.w = m_textureRect.w * m_scale;
		dst.h = m_textureRect.h * m_scale;

		SDL_RenderCopy(renderer, m_texture, &m_textureRect, &dst);
	}
	else if (!m_disappear && m_boundDead)
	{

		dst.x = m_position.m_x - (float)m_deadRect.w / 2.f * m_scale;
		dst.y = m_position.m_y - (float)m_deadRect.h / 2.f * m_scale;
		dst.w = m_deadRect.w * m_scale;
		dst.h = m_deadRect.h * m_scale;

		SDL_RenderCopy(renderer, m_texture, &m_deadRect, &dst);
	}
}

void Projectile::OnCollision(ICollidable& otherCollidable)
{
	if (!m_dead)
	{
		const auto& proj = dynamic_cast<Projectile*>(&otherCollidable);

		if (proj == NULL)
			return;

		proj->m_dead = true;
		m_dead = true;
		//proj->m_boundDead = true;
		m_boundDead = true;
	}
}