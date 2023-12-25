#pragma once

#include<SDL.h>
#include<iostream>
#include<cmath>


#include"Entity.h"

namespace utils
{
	static float m_currentTime = 0.f;
	static float m_lastTime = 0.f;
	static int m_fps;

	inline float HireTimeInSeconds()
	{
		float t = (float)SDL_GetTicks();
		return t * 0.001f;
	}

	inline void PrintFps()
	{
		m_currentTime = (float)SDL_GetTicks();
		if ((m_currentTime - m_lastTime) >= 1000.f)
		{
			m_lastTime = m_currentTime;
			std::cout << m_fps << std::endl;
			m_fps = 0;
		}
		m_fps++;
	}

	inline int Random(int min, int max)
	{
		return (rand() % (max - min + 1)) + min;
	}

	inline bool RangeIntersect(float min0, float max0, float min1, float max1)
	{
		return std::max(min0, max0) >= std::min(min1, max1) &&
			std::min(min0, max0) <= std::max(min1, max1);
	}

	inline bool RectIntersect(Entity e1, Entity e2)
	{
		return RangeIntersect(e1.m_position.m_x - (float)e1.m_textureRect.w / 2.f * e1.m_scale, e1.m_position.m_x + (float)e1.m_textureRect.w / 2.f * e1.m_scale, e2.m_position.m_x - (float)e2.m_textureRect.w / 2.f * e2.m_scale, e2.m_position.m_x + (float)e2.m_textureRect.w / 2.f * e2.m_scale) &&
			RangeIntersect(e1.m_position.m_y - (float)e1.m_textureRect.h / 2.f * e1.m_scale, e1.m_position.m_y + (float)e1.m_textureRect.h / 2.f * e1.m_scale, e2.m_position.m_y - (float)e2.m_textureRect.h / 2.f * e2.m_scale, e2.m_position.m_y + (float)e2.m_textureRect.h / 2.f * e2.m_scale);
	}


}