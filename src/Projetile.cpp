#include"Projectile.h"

Projectile::Projectile(const AssetManager& assetManager, const Vector& pos, const Vector& velocity, const std::string& key, float scale)
	:Entity(assetManager, pos, key, scale)
{
	m_velocity = velocity;
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
	dst.x = m_position.GetX();
	dst.y = m_position.GetY();
	dst.w = src.w * m_scale;
	dst.h = src.h * m_scale;

	SDL_RenderCopy(renderer, m_texture, &src, &dst);
}