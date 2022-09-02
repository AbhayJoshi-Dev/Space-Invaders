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

	inline bool RangeIntersect(float min0, float max0, float min1, float max1)
	{
		return std::max(min0, max0) <= std::min(min1, max1) &&
			std::min(min0, max0) >= std::max(min1, max1);
	}

	inline bool RectIntersect(Entity e1, Entity e2)
	{
		return RangeIntersect(e1.m_position.GetX() - e1.m_textureRect.w * e1.m_scale / 2, e1.m_position.GetX() + e1.m_textureRect.w * e1.m_scale / 2, e2.m_position.GetX() - e2.m_textureRect.w * e2.m_scale / 2, e2.m_position.GetX() + e2.m_textureRect.w * e2.m_scale / 2) &&
			RangeIntersect(e1.m_position.GetY() - e1.m_textureRect.h * e1.m_scale / 2, e1.m_position.GetY() + e1.m_textureRect.h * e1.m_scale / 2, e2.m_position.GetY() - e2.m_textureRect.h * e2.m_scale / 2, e2.m_position.GetY() + e2.m_textureRect.h * e2.m_scale / 2);
	}
}