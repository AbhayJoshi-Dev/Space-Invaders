#pragma once

#include"Entity.h"

class Player : public Entity
{
public:
	Player(const Vector& pos, SDL_Texture* tex);
};