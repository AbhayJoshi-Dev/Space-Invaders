#pragma once

#include"Entity.h"
#include"Utils.h"
#include"ICollidable.h"
#include"Timer.h"

class Projectile : public Entity, public ICollidable
{
public:
	Projectile(const Vector& pos, const Vector& velocity, const std::string& key, float scale, const std::string& deadKey, std::string parentTag);
	void Update() override;
	void Render(SDL_Renderer* renderer) override;

public:
	bool m_Dead;
	Vector m_velocity;
	std::string m_parentTag;
	bool m_boundDead;
	bool m_disappear;

private:

	SDL_Texture* m_DeadTex;
	SDL_Rect m_DeadRect;
	Timer m_timer;
};