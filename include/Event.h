#pragma once
#include<functional>

#include"Entity.h"

struct Event
{
	std::function<void(Entity& entity)> action;
};