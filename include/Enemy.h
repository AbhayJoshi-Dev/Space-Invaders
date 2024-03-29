#pragma once

#include"Entity.h"
#include"Projectile.h"
#include"Utils.h"
#include"ICollidable.h"
#include"Timer.h"
#include"SoundManager.h"

class Enemy : public Entity, public ICollidable
{
public:
	Enemy() = default;
	Enemy(const Vector& pos, const SDL_Rect& textureRect, const float& scale, const SDL_Rect& enemyDeadTextureRect, int enemyLevel, Game* game = nullptr);
	void Update(float dt) override;
	void Render(SDL_Renderer* renderer) override;
	void Shoot();
	void Animate();
	void OnCollision(ICollidable& otherCollidable) override;
	bool Destroy() override;
	void EnemyRed();
	void Reset() override;

public:
	Projectile m_projectile;

private:
	bool m_disappear;
	bool animate;
	bool canShoot;
	float m_shootCounter;

	SDL_Rect m_deadTextureRect;
	SDL_Rect m_redTextureRect;
	
	Timer m_deadTimer;
	int m_enemyLevel;
	bool m_makeRed;
};