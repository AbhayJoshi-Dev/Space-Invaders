#include"Projectile.h"

Projectile::Projectile(const Vector& pos, const Vector& velocity, const std::string& key, float scale, const std::string& deadKey, std::string parentTag)
	:Entity(pos, key, scale, key), m_velocity(velocity), m_parentTag(parentTag)
{
	m_texture = AssetManager::GetInstance().Get(key);
	m_dead = true;
	m_disappear = false;
	m_DeadTex = AssetManager::GetInstance().Get(deadKey);
	SDL_QueryTexture(m_DeadTex, NULL, NULL, &m_DeadRect.w, &m_DeadRect.h);
	m_DeadRect.x = 0;
	m_DeadRect.y = 0;
	m_DeadRect.w *= m_scale;
	m_DeadRect.h *= m_scale;
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
	SDL_Rect src;
	SDL_Rect dst;

	if (!m_dead)
	{
		src.x = 0;
		src.y = 0;
		src.w = m_textureRect.w;
		src.h = m_textureRect.h;

		dst.x = m_position.m_x - (float)m_textureRect.w / 2.f;
		dst.y = m_position.m_y - (float)m_textureRect.h / 2.f;
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(renderer, m_texture, &src, &dst);
	}
	else if (!m_disappear && m_boundDead)
	{
		src.x = 0;
		src.y = 0;
		src.w = m_DeadRect.w;
		src.h = m_DeadRect.h;

		dst.x = m_position.m_x - (float)m_DeadRect.w / 2.f;
		dst.y = m_position.m_y - (float)m_DeadRect.h / 2.f;
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(renderer, m_DeadTex, &src, &dst);
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