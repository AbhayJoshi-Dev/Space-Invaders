#include"Entity.h"

Entity::Entity(const Vector& pos, const std::string& key, const float& scale, const std::string& tag)
	:m_position(pos), m_scale(scale), m_tag(tag)
{
	m_texture = AssetManager::GetInstance().Get(key);

	if (tag != "Wall")
	{
		m_textureRect.x = 0;
		m_textureRect.y = 0;

		SDL_QueryTexture(m_texture, NULL, NULL, &m_textureRect.w, &m_textureRect.h);

		m_textureRect.w *= m_scale;
		m_textureRect.h *= m_scale;// *0.8f; //
	}


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

bool Entity::Destroy()
{
	return false;
}