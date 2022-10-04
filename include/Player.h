#pragma once

#include<vector>

#include"Entity.h"
#include"Projectile.h"
#include"Utils.h"
#include"Enemy.h"

class Player : public Entity
{
public:
	Player() = default;
	Player(const Vector& pos, const std::string& key, const float& scale, const std::string& playerDeadKey1, const std::string& playerDeadKey2);
	void Update() override;
	void Render(SDL_Renderer* renderer) override;
	void HandleEvents(SDL_Event& event) override;
	void Shoot();
	bool CheckProjectileCollision(Entity& e);
	void Dead();

public:
	Projectile m_projectile;

private:
	float m_moveSpeed;
	bool m_isFired;
	bool m_dead;

	SDL_Texture* m_deathTexture1;
	SDL_Texture* m_deathTexture2;

	SDL_Rect m_deathRect1;
	SDL_Rect m_deathRect2;

	int m_animateCounter;
	bool m_animate;
};