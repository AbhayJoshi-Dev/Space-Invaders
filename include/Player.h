#pragma once

#include<vector>

#include"Entity.h"
#include"Projectile.h"
#include"Utils.h"

class Player : public Entity
{
public:
	Player(const AssetManager& assetManager, const Vector& pos, const std::string& key, const float& scale);
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