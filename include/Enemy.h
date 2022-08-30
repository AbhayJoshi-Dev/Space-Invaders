#pragma once

#include"Entity.h"

class Enemy : public Entity
{
public:
	Enemy() = default;
	Enemy(const Vector& pos, const std::string& key, const float& scale);
	void Update() override;
	void Render(SDL_Renderer* renderer) override;
};