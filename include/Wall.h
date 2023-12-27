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
	WallPiece(const Vector& pos, const WallPieceType& m_type, std::vector<WallPiece*>* m_referencesToPieces, float id);
	void SetTextureRect();
	void Update(float dt) override;
	void Render(SDL_Renderer* renderer) override;
	void OnCollision(ICollidable& otherCollidable) override;
	bool Destroy() override;
	void UpdateRect(const std::string& parentTag);
	void Reset() override;

public:

private:
	int m_flag;
	WallPieceType m_pieceType;
	std::vector<WallPiece*>* m_referencesToPieces;
	float m_id;
};


class Wall
{
public:
	Wall() = default;
	void CreateWall(const Vector& pos);
	std::vector<WallPiece*>& GetPieces();

public:
	std::vector<WallPiece*> m_pieces;
};