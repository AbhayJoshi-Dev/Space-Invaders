#pragma once

#include"Entity.h"

class Projectile : public Entity
{
public:
	Projectile(const Vector& pos, const Vector& velocity, const std::string& key, float scale, const std::string& deadKey);
	void Update() override;
	void Render(SDL_Renderer* renderer) override;
public:
	bool m_Dead;
	bool m_boundDead;
	Vector m_velocity;
private:

	SDL_Texture* m_projectileDeadTex;
	SDL_Rect m_projectileDeadRect;
};