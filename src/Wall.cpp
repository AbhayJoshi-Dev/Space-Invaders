#include"Wall.h"

WallPiece::WallPiece(const Vector& pos, const std::string& key, const WallPieceType& m_type)
	:Entity(pos, key, 1.f, "Wall"), m_pieceType(m_type)
{
	m_dead = false;
	if (m_pieceType == Square)
	{
		m_textureRect.x = 25;
		m_textureRect.y = 0;
		m_textureRect.w = 8;
		m_textureRect.h = 8;
	}
	else if(m_pieceType == RightTriangle)
	{
		m_textureRect.x = 70;
		m_textureRect.y = 28;
		m_textureRect.w = 7;
		m_textureRect.h = 7;
	}
	else if(m_pieceType == LeftTriangle)
	{
		m_textureRect.x = 71;
		m_textureRect.y = 1;
		m_textureRect.w = 7;
		m_textureRect.h = 7;
	}

	m_flag = 0;

	m_textureRect.w *= 3;
	m_textureRect.h *= 3;
}

void WallPiece::Update()
{

	if (m_pieceType == Square)
	{
		if (m_flag == 5)
			m_dead = true;
	}
	else
	{
		if (m_flag == 3)
			m_dead = true;
	}
}

void WallPiece::Render(SDL_Renderer* renderer)
{
	if (!m_dead)
	{
		SDL_Rect src;
		src.x = m_textureRect.x;
		src.y = m_textureRect.y;
		if (m_pieceType == Square)
		{
			src.w = 8;
			src.h = 8;
		}
		else
		{
			src.w = 7;
			src.h = 7;
		}

		SDL_Rect dst;
		dst.x = m_position.m_x - (float)m_textureRect.w / 2.f;
		dst.y = m_position.m_y - (float)m_textureRect.h / 2.f;
		dst.w = src.w * 3;
		dst.h = src.h * 3;

		SDL_RenderCopy(renderer, m_texture, &src, &dst);
	}
}

void WallPiece::OnCollision(ICollidable& otherCollidable)
{
	const auto& proj = dynamic_cast<Projectile*>(&otherCollidable);

	if (proj->m_parentTag == "Player")
	{
		proj->m_Dead = true;
		proj->m_boundDead = true;

		m_textureRect.y += 9;
		m_flag++;

	}
	else if (proj->m_parentTag == "Enemy")
	{
		proj->m_Dead = true;
		proj->m_boundDead = true;

		m_textureRect.x += 9;
		m_flag++;
	}
}

bool WallPiece::Destroy()
{
	return m_dead;
}

void Wall::CreateWall(const Vector& pos, const std::string& key)
{
	m_pieces.push_front(std::make_shared<WallPiece>(Vector(pos.m_x, pos.m_y - 24.f), key, Square));
	m_pieces.push_front(std::make_shared<WallPiece>(Vector(pos.m_x, pos.m_y), key, Square));
	m_pieces.push_front(std::make_shared<WallPiece>(Vector(pos.m_x + 24.f, pos.m_y), key, Square));
	m_pieces.push_front(std::make_shared<WallPiece>(Vector(pos.m_x - 24.f, pos.m_y), key, Square));
	m_pieces.push_front(std::make_shared<WallPiece>(Vector(pos.m_x + 24.f, pos.m_y + 24.f), key, Square));
	m_pieces.push_front(std::make_shared<WallPiece>(Vector(pos.m_x - 24.f, pos.m_y + 24.f), key, Square));
	m_pieces.push_front(std::make_shared<WallPiece>(Vector(pos.m_x + 22.5f, pos.m_y - 22.5f), key, RightTriangle));
	m_pieces.push_front(std::make_shared<WallPiece>(Vector(pos.m_x - 22.5f, pos.m_y - 22.5f), key, LeftTriangle));
}

std::forward_list<std::shared_ptr<WallPiece>> Wall::GetPieces()
{
	return m_pieces;
}