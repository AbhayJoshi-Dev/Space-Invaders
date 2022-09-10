#include"Enemy.h"

Enemy::Enemy(const Vector& pos, const std::string& key, const float& scale, const std::string& enemyDeadTextureKey)
	:Entity(pos, key, scale)
{
	m_dead = false;
	m_EnemyDeadTexture = AssetManager::GetInstance().Get(enemyDeadTextureKey);

	m_EnemyDeadRect.x = 0;
	m_EnemyDeadRect.y = 0;

	SDL_QueryTexture(m_EnemyDeadTexture, NULL, NULL, &m_EnemyDeadRect.w, &m_EnemyDeadRect.h);

	m_EnemyDeadRect.w *= m_scale;
	m_EnemyDeadRect.h *= m_scale;
}

void Enemy::Update()
{

}

void Enemy::Render(SDL_Renderer* renderer)
{
	if (!m_dead)
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
	else
	{
		SDL_Rect src;
		src.x = 0;
		src.y = 0;
		src.w = m_EnemyDeadRect.w;
		src.h = m_EnemyDeadRect.h;

		SDL_Rect dst;
		dst.x = m_position.GetX() - m_EnemyDeadRect.w / 2;
		dst.y = m_position.GetY() - m_EnemyDeadRect.h / 2;
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(renderer, m_EnemyDeadTexture, &src, &dst);
	}
}

void Enemy::Dead()
{
	m_dead = true;
	std::cout << "Enemy Dead" << std::endl;
}