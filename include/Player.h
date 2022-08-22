#pragma once

#include<vector>

#include"Entity.h"
#include"Projectile.h"
#include"Utils.h"

class Player : public Entity
{
public:
	Player(SDL_Texture* tex, const Vector& pos, const float& scale);
	void SetTexture(SDL_Texture* tex);
	void Update() override;
	void Render(SDL_Renderer* renderer) override;
	void HandleEvents(SDL_Event& event) override;
public:
	bool isfiring;
private:
	float m_moveSpeed;
	float m_fireCooldown;
	float m_counter;
};