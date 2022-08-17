#include"Projectile.h"

Projectile::Projectile(const AssetManager& assetManager, const Vector& pos, const Vector& velocity, const std::string& key, float scale)
	:Entity(assetManager, pos, key, scale)
{
	m_velocity = velocity;
}

void Projectile::Update()
{
	m_position = m_position + m_velocity;
}