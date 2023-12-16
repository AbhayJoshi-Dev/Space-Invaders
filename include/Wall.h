#pragma once

#include<forward_list>

#include"Entity.h"
#include"ICollidable.h"
#include"Projectile.h"

enum WallPieceType
{
	RightTriangle = 0,
	LeftTriangle,
	Square,
	CenterSquare
};

class WallPiece : public Entity, public ICollidable
{
public:
	WallPiece(const Vector& pos, const std::string& key, const WallPieceType& m_type);
	void Update() override;
	void Render(SDL_Renderer* renderer) override;
	void OnCollision(ICollidable& otherCollidable) override;
	bool Destroy() override;

private:
	int m_flag;
	bool m_dead;
	WallPieceType m_pieceType;
};


class Wall
{
public:
	Wall() = default;
	void CreateWall(const Vector& pos, const std::string& key);
	std::vector<WallPiece*>& GetPieces();

public:
	std::vector<WallPiece*> m_pieces;
};