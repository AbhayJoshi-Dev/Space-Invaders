#pragma once

#include"Entity.h"

class Projectile : public Entity
{
public:
	Projectile(const Vector& pos, const Vector& velocity, const std::string& key, float scale);
	void Update() override;
	void Render(SDL_Renderer* renderer) override;
public:
	bool m_isDead;
private:
	Vector m_velocity;
};