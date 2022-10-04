#include"Projectile.h"

Projectile::Projectile(const Vector& pos, const Vector& velocity, const std::string& key, float scale, const std::string& deadKey)
	:Entity(pos, key, scale)
{
	m_velocity = velocity;

	m_texture = AssetManager::GetInstance().Get(key);
	m_Dead = true;

	m_projectileDeadTex = AssetManager::GetInstance().Get(deadKey);
	SDL_QueryTexture(m_projectileDeadTex, NULL, NULL, &m_projectileDeadRect.w, &m_projectileDeadRect.h);
	m_projectileDeadRect.x = 0;
	m_projectileDeadRect.y = 0;
	m_projectileDeadRect.w *= m_scale;
	m_projectileDeadRect.h *= m_scale;
	m_boundDead = false;
}

void Projectile::Update()
{
	m_position = m_position + m_velocity;
	if (m_position.GetY() > 600)
	{
		m_Dead = true;
	}
}

void Projectile::Render(SDL_Renderer* renderer)
{
	SDL_Rect src;
	SDL_Rect dst;

	if (!m_Dead)
	{
		src.x = 0;
		src.y = 0;
		src.w = m_textureRect.w;
		src.h = m_textureRect.h;

		dst.x = m_position.GetX() - m_textureRect.w / 2;
		dst.y = m_position.GetY() - m_textureRect.h / 2;
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(renderer, m_texture, &src, &dst);
	}
}