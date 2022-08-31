#include"Enemy.h"

Enemy::Enemy(const Vector& pos, const std::string& key, const float& scale)
	:Entity(pos, key, scale)
{

}

void Enemy::Update()
{

}

void Enemy::Render(SDL_Renderer* renderer)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = m_textureRect.w;
	src.h = m_textureRect.h;

	SDL_Rect dst;
	dst.x = m_position.GetX() * m_scale - m_textureRect.w / 2;
	dst.y = m_position.GetY() * m_scale - m_textureRect.h / 2;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, m_texture, &src, &dst);
}