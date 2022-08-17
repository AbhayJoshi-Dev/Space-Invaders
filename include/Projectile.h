#pragma once

#include"Entity.h"

class Projectile : public Entity
{
public:
	Projectile(const AssetManager& assetManager, const Vector& pos, const Vector& velocity, const std::string& key, float scale);
	void Update();
private:
	Vector m_velocity;
	float m_bulletSpeed;
};