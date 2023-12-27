#pragma once

#include"Entity.h"
#include"Utils.h"
#include"ICollidable.h"
#include"Timer.h"

class Projectile : public Entity, public ICollidable
{
public:
	Projectile(const Vector& pos, float velocity, const SDL_Rect& textureRect, float scale, const SDL_Rect& deadTextureRect, std::string parentTag);
	void Update(float dt) override;
	void Render(SDL_Renderer* renderer) override;
	void OnCollision(ICollidable& otherCollidable) override;

public:
	float m_velocity;
	std::string m_parentTag;
	bool m_boundDead;
	bool m_disappear;

private:

	SDL_Rect m_deadRect;
	Timer m_timer;
};