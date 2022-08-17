#pragma once

#include"Entity.h"

class Player : public Entity
{
public:
	Player(const AssetManager& assetManager, const Vector& pos, const std::string& key, const float& scale);
	void Update() override;
	void Render(SDL_Renderer* renderer) override;
	void HandleEvents(SDL_Event& event) override;
private:
	float m_moveSpeed;
};