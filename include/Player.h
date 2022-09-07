#pragma once

#include<vector>

#include"Entity.h"
#include"Projectile.h"
#include"Utils.h"

class Player : public Entity
{
public:
	Player() = default;
	Player(const Vector& pos, const std::string& key, const float& scale);
	void Update() override;
	void Render(SDL_Renderer* renderer) override;
	void HandleEvents(SDL_Event& event) override;
	void Shoot();
	void CheckProjectileCollision(Entity& e);

public:
	Projectile m_projectile;

private:
	float m_moveSpeed;
	bool m_isFired;

};