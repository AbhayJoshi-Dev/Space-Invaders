#include"Projectile.h"

Projectile::Projectile(const Vector& pos, const Vector& velocity, const std::string& key, float scale)
	:Entity(pos, key, scale)
{
	m_velocity = velocity;

	m_texture = AssetManager::GetInstance().Get(key);
	m_isDead = false;
}

void Projectile::Update()
{
	m_position = m_position + m_velocity;
}

void Projectile::Render(SDL_Renderer* renderer)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = m_textureRect.w;
	src.h = m_textureRect.h;

	SDL_Rect dst;
	dst.x = m_position.GetX() - m_textureRect.w / 2;
	dst.y = m_position.GetY() - m_textureRect.h / 2;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, m_texture, &src, &dst);
}