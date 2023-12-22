#include"Entity.h"

Entity::Entity(const Vector& pos, const SDL_Rect& textureRect, const float& scale, const std::string& tag)
	:m_position(pos), m_scale(scale), m_tag(tag)
{
	m_texture = AssetManager::GetInstance().Get("Sheet");

	if (tag != "Wall")
	{
		m_textureRect = textureRect;

		//m_textureRect.x = textureRect.x;
		//m_textureRect.y = textureRect.y;

		//SDL_QueryTexture(m_texture, NULL, NULL, &m_textureRect.w, &m_textureRect.h);

		//m_textureRect.w *= m_scale;
		//m_textureRect.h *= m_scale;// *0.8f; //
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
void Entity::Reset()
{

}