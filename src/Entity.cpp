#include"Entity.h"

Entity::Entity(const AssetManager& assetManager, const Vector& pos, const std::string& key, const float& scale)
	:m_position(pos), m_scale(scale)
{
	m_texture = assetManager.Get(key);

	m_textureRect.x = 0;
	m_textureRect.y = 0;

	SDL_QueryTexture(m_texture, NULL, NULL, &m_textureRect.w, &m_textureRect.h);
}

Entity::Entity(SDL_Texture* tex, const Vector& pos, const float& scale)
	:m_position(pos), m_scale(scale)
{
	m_texture = tex;

	m_textureRect.x = 0;
	m_textureRect.y = 0;

	SDL_QueryTexture(m_texture, NULL, NULL, &m_textureRect.w, &m_textureRect.h);
}

Entity::~Entity()
{

}

void Entity::ESetTexture(SDL_Texture* tex)
{
	m_texture = tex;

	m_textureRect.x = 0;
	m_textureRect.y = 0;

	SDL_QueryTexture(m_texture, NULL, NULL, &m_textureRect.w, &m_textureRect.h);
}

void Entity::Update()
{

}

void Entity::Render(SDL_Renderer* renderer)
{

}

void Entity::HandleEvents(SDL_Event& event)
{

}