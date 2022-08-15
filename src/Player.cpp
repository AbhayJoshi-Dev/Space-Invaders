#include"Player.h"

Player::Player(const AssetManager& assetManager, const Vector& pos, const std::string& key, const float& scale)
	:Entity(assetManager, pos, key, scale)
{

}

void Player::Update()
{
	std::cout << "Player" << std::endl;
}

void Player::Render(SDL_Renderer* renderer)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = m_textureRect.w;
	src.h = m_textureRect.h;

	SDL_Rect dst;
	dst.x = m_position.GetX();
	dst.y = m_position.GetY();
	dst.w = src.w * m_scale;
	dst.h = src.h * m_scale;

	SDL_RenderCopy(renderer, m_texture, &src, &dst);
}

void Player::HandleEvents(SDL_Event& event)
{

}

void Player::test()
{

}