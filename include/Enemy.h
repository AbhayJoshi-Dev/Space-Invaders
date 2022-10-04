#pragma once

#include"Entity.h"
#include"Projectile.h"
#include"Utils.h"

class Enemy : public Entity
{
public:
	Enemy() = default;
	Enemy(const Vector& pos, const std::string& key, const float& scale, const std::string& enemyDeadTextureKey, const std::string& enemySecondTextureKey);
	void Update() override;
	void Render(SDL_Renderer* renderer) override;
	void Dead();
	void Shoot();
	bool CheckProjectileCollision(Entity& e);

private:
	bool m_dead;
	bool m_disappear;
	float m_counter;
	int m_animateCounter;
	bool animate;
	bool canShoot;
	float m_shootCounter;

	SDL_Texture* m_SecondTexture;

	SDL_Texture* m_DeadTexture;
	SDL_Rect m_DeadRect;

	Projectile m_projectile;
};