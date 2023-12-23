#pragma once

#include<vector>

#include"Entity.h"
#include"Projectile.h"
#include"Utils.h"
#include"SoundManager.h"

class Player : public Entity, public ICollidable
{
public:
	Player() = default;
	Player(const Vector& pos, const SDL_Rect& playertextureRect, const float& scale, const SDL_Rect& playerDeadTexture1Rect, const SDL_Rect& playerDeadTexture2Rect);
	void Update() override;
	void Render(SDL_Renderer* renderer) override;
	void HandleEvents(SDL_Event& event) override;
	void Reset() override;
	void Shoot();
	void Dead();
	void OnCollision(ICollidable& otherCollidable) override;
	void BoundCollision();

public:
	Projectile m_projectile;
	bool m_dead;
	int m_lives;

private:
	float m_moveSpeed;

//	SDL_Texture* m_deathTexture1;
//	SDL_Texture* m_deathTexture2;

	SDL_Rect m_deathRect1;
	SDL_Rect m_deathRect2;

	bool m_animate;
	Timer m_timer;
	Timer m_deadTimer;
};