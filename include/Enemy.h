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
	Enemy(const Vector& pos, const SDL_Rect& textureRect, const float& scale, const SDL_Rect& enemyDeadTextureRect, const SDL_Rect& enemySecondTextureRect);
	void Update() override;
	void Render(SDL_Renderer* renderer) override;
	void Shoot();
	void Animate();

	void OnCollision(ICollidable& otherCollidable) override;

	bool Destroy() override;

public:
	Projectile m_projectile;
	bool m_dead;

private:
	bool m_disappear;
	bool animate;
	bool canShoot;
	float m_shootCounter;

	SDL_Rect m_deadTextureRect;
	SDL_Rect m_secondTextureRect;
	
	Timer m_deadTimer;
};