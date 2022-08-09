#include"Entity.h"

Entity::Entity(const Vector& pos, SDL_Texture* tex)
	:m_position(pos), m_texture(tex)
{
	m_textureRect.x = 0;
	m_textureRect.y = 0;

	SDL_QueryTexture(m_texture, NULL, NULL, &m_textureRect.w, &m_textureRect.h);
}

Entity::~Entity()
{

}

void Entity::Update()
{

}

void Entity::Render(SDL_Renderer* renderer)
{

}