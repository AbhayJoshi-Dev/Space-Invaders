#include"Wall.h"

WallPiece::WallPiece(const Vector& pos, const WallPieceType& m_type, std::vector<WallPiece*>* referencesToPieces, float id)
	:Entity(pos, { 0, 0, 0, 0 }, 3.f, "Wall"), m_pieceType(m_type), m_referencesToPieces(referencesToPieces), m_id(id)
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

	proj->m_dead = true;
	proj->m_boundDead = true;

	UpdateRect(proj->m_parentTag);

}

bool WallPiece::Destroy()
{
	return m_dead;
}

void WallPiece::UpdateRect(const std::string& parentTag)
{

	//this condition is just for a small visual thing for walls
	if (((m_pieceType == CenterSquare || m_pieceType == Square) && m_flag == 4))
	{
		std::vector<WallPiece*>::iterator it = std::find(m_referencesToPieces->begin(), m_referencesToPieces->end(), this);
		
		if (parentTag == "Player" && *it != m_referencesToPieces->back() && m_id != 2.2f)
			(*++it)->UpdateRect(parentTag);
		else if (parentTag == "Enemy" && *it != m_referencesToPieces->front() && m_id != 1.1f && m_id != 3.1f && m_id != 2.1f)
			(*--it)->UpdateRect(parentTag);

		m_flag++;
		return;
	}
	else if ((m_pieceType == RightTriangle || m_pieceType == LeftTriangle) && m_flag == 2)
	{
		std::vector<WallPiece*>::iterator it = std::find((*m_referencesToPieces).begin(), (*m_referencesToPieces).end(), this);

		if (parentTag == "Enemy" && *it != m_referencesToPieces->front())
			(*--it)->UpdateRect(parentTag);

		m_flag++;
		return;
	}

	if (parentTag == "Player")
	{
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
	else if (parentTag == "Enemy")
	{
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

void Wall::CreateWall(const Vector& pos)
{
	m_pieces.reserve(24);
	//first column
	m_pieces.push_back(new WallPiece(Vector(pos.m_x - 24.f, pos.m_y + 24.f), Square, &m_pieces, 1.1f));
	m_pieces.push_back(new WallPiece(Vector(pos.m_x - 24.f, pos.m_y), Square, &m_pieces, 1.2f));
	m_pieces.push_back(new WallPiece(Vector(pos.m_x - 22.5f, pos.m_y - 22.5f), LeftTriangle, &m_pieces, 1.3f));

	//second column
	m_pieces.push_back(new WallPiece(Vector(pos.m_x, pos.m_y), CenterSquare, &m_pieces, 2.1f));
	m_pieces.push_back(new WallPiece(Vector(pos.m_x, pos.m_y - 24.f), Square, &m_pieces, 2.2f));

	//third column
	m_pieces.push_back(new WallPiece(Vector(pos.m_x + 24.f, pos.m_y + 24.f), Square, &m_pieces, 3.1f));
	m_pieces.push_back(new WallPiece(Vector(pos.m_x + 24.f, pos.m_y), Square, &m_pieces, 3.2f));
	m_pieces.push_back(new WallPiece(Vector(pos.m_x + 22.5f, pos.m_y - 22.5f), RightTriangle, &m_pieces, 3.3f));
}

std::vector<WallPiece*>& Wall::GetPieces()
{
	return m_pieces;
}