#pragma once
#include<functional>

#include"Entity.h"

struct Event
{
	std::string entityTag;
	std::function<void(Entity& entity)> action;
};