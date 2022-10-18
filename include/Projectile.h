#pragma once

#include"Entity.h"
#include"Utils.h"
#include"ICollidable.h"

class Projectile : public Entity, public ICollidable
{
public:
	Projectile(const Vector& pos, const Vector& velocity, const std::string& key, float scale, const std::string& deadKey, std::string parentTag);
	void Update() override;
	void Render(SDL_Renderer* renderer) override;
	bool OnCollision(Entity& entity);
	void OnCollision(ICollidable* otherCollidable) override;
public:
	bool m_Dead;
	bool m_boundDead;
	Vector m_velocity;
	std::string m_parentTag;
private:

	SDL_Texture* m_projectileDeadTex;
	SDL_Rect m_projectileDeadRect;
};