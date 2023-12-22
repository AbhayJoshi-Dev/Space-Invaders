#include"Wall.h"

WallPiece::WallPiece(const Vector& pos, const WallPieceType& m_type)
	:Entity(pos, { 0, 0, 0, 0 }, 3.f, "Wall"), m_pieceType(m_type)
{
	m_dead = false;
	if (m_pieceType == Square)
	{
		m_textureRect.x = 137;
		m_textureRect.y = 126;
		m_textureRect.w = 8;
		m_textureRect.h = 8;
	}
	else if(m_pieceType == RightTriangle)
	{
		m_textureRect.x = 182;
		m_textureRect.y = 154;
		m_textureRect.w = 7;
		m_textureRect.h = 7;
	}
	else if(m_pieceType == LeftTriangle)
	{
		m_textureRect.x = 183;
		m_textureRect.y = 127;
		m_textureRect.w = 7;
		m_textureRect.h = 7;
	}
	else if (m_pieceType == CenterSquare)
	{
		m_textureRect.x = 120;
		m_textureRect.y = 134;
		m_textureRect.w = 8;
		m_textureRect.h = 11;
	}

	m_flag = 0;

	//m_textureRect.w *= 3;
	//m_textureRect.h *= 3;
}

void WallPiece::Update()
{

	if (m_pieceType == Square || m_pieceType == CenterSquare)
	{
		if (m_flag == 5)
			m_dead = true;
	}
	else
	{
		if (m_flag == 3)
			m_dead = true;
	}

	if (m_flag > 0 && m_pieceType == CenterSquare)
		m_pieceType = Square;
}

void WallPiece::Render(SDL_Renderer* renderer)
{
	if (!m_dead)
	{
		//src.x = m_textureRect.x;
		//src.y = m_textureRect.y;
		//if (m_pieceType == Square)
		//{
		//	src.w = 8;
		//	src.h = 8;
		//}
		//else if (m_pieceType == CenterSquare)
		//{
		//	src.w = 8;
		//	src.h = 11;
		//}
		//else
		//{
		//	src.w = 7;
		//	src.h = 7;
		//}

		SDL_Rect dst;
		dst.x = m_position.m_x - (float)m_textureRect.w / 2.f * 3;
		dst.y = m_position.m_y - (float)m_textureRect.h / 2.f * 3;
		dst.w = m_textureRect.w * 3;
		dst.h = m_textureRect.h * 3;

		SDL_RenderCopy(renderer, m_texture, &m_textureRect, &dst);
	}
}

void WallPiece::OnCollision(ICollidable& otherCollidable)
{
	const auto& proj = dynamic_cast<Projectile*>(&otherCollidable);

	if (proj == NULL)
		return;

	if ((m_pieceType == CenterSquare || m_pieceType == Square) && m_flag == 4)
	{
		proj->m_dead = true;
		proj->m_boundDead = true;
		m_flag++;
		return;
	}

	if (proj->m_parentTag == "Player")
	{
		proj->m_dead = true;
		proj->m_boundDead = true;

		if (m_pieceType == CenterSquare && m_flag == 0)
		{
			m_textureRect.x += 17;
			m_textureRect.y += 1;
			m_textureRect.w = 8;
			m_textureRect.h = 8;
		}
		else
		{
			m_textureRect.y += 9;
		}
	}
	else if (proj->m_parentTag == "Enemy")
	{
		proj->m_dead = true;
		proj->m_boundDead = true;

		if (m_pieceType == CenterSquare && m_flag == 0)
		{
			m_textureRect.x += 26;
			m_textureRect.y -= 8;
			m_textureRect.w = 8;
			m_textureRect.h = 8;
		}
		else
		{
			m_textureRect.x += 9;
		}
	}
	m_flag++;
}

bool WallPiece::Destroy()
{
	return m_dead;
}

void Wall::CreateWall(const Vector& pos)
{
	m_pieces.push_back(new WallPiece(Vector(pos.m_x, pos.m_y - 24.f), Square));
	m_pieces.push_back(new WallPiece(Vector(pos.m_x, pos.m_y), CenterSquare));
	m_pieces.push_back(new WallPiece(Vector(pos.m_x + 24.f, pos.m_y), Square));
	m_pieces.push_back(new WallPiece(Vector(pos.m_x - 24.f, pos.m_y), Square));
	m_pieces.push_back(new WallPiece(Vector(pos.m_x + 24.f, pos.m_y + 24.f), Square));
	m_pieces.push_back(new WallPiece(Vector(pos.m_x - 24.f, pos.m_y + 24.f), Square));
	m_pieces.push_back(new WallPiece(Vector(pos.m_x + 22.5f, pos.m_y - 22.5f), RightTriangle));
	m_pieces.push_back(new WallPiece(Vector(pos.m_x - 22.5f, pos.m_y - 22.5f), LeftTriangle));
}

std::vector<WallPiece*>& Wall::GetPieces()
{
	return m_pieces;
}