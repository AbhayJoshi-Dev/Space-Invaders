#pragma once

#include"Entity.h"

class Enemy : public Entity
{
public:
	Enemy() = default;
	Enemy(const Vector& pos, const std::string& key, const float& scale, const std::string& enemyDeadTextureKey);
	void Update() override;
	void Render(SDL_Renderer* renderer) override;
	void Dead();

private:
	bool m_dead;
	SDL_Texture* m_EnemyDeadTexture;
	SDL_Rect m_EnemyDeadRect;
};