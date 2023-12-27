#include"Entity.h"
#include"Game.h"
#include"Event.h"

Entity::Entity(const Vector& pos, const SDL_Rect& textureRect, const float& scale, const std::string& tag, Game* game)
	:m_position(pos), m_scale(scale), m_tag(tag), m_game(game)
{
	m_texture = AssetManager::GetInstance().Get("Sheet");

	if (tag != "Wall")
		m_textureRect = textureRect;
}

void Entity::Update(float dt)
{

}

void Entity::Render(SDL_Renderer* renderer)
{
	if (m_dead)
		return;

	SDL_Rect dst;

	dst.x = m_position.m_x - m_textureRect.w / 2 * m_scale;
	dst.y = m_position.m_y - m_textureRect.h / 2 * m_scale;
	dst.w = m_textureRect.w * m_scale;
	dst.h = m_textureRect.h * m_scale;

	SDL_RenderCopy(renderer, m_texture, &m_textureRect, &dst);
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
	m_dead = false;
}

void Entity::AddEvent(const Event& event)
{
	m_game->AddEvent(event);
}