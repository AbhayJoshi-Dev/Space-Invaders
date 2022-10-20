#pragma once

class ICollidable
{
public:
	virtual ~ICollidable() {}

	virtual void OnCollision(ICollidable& otherCollidable) {}
};