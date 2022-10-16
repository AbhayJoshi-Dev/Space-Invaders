#pragma once

class ICollidable
{
	virtual ~ICollidable() {}

	virtual void OnCollision(const ICollidable& otherCollidable) {}
};