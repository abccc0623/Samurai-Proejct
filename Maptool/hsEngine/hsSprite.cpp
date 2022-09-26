#include "pch.h"


hsSprite::hsSprite()
{
	imgDC	= NULL;
	imgbit	= NULL;
	size	= 0;
	Original_Size	= { 0,0 };
	Re_Size			= { 0,0 };
	pivotX = 0;
	pivotY = 0;
	AnimeCount = 1;
	isLoop = true;
}



hsSprite::~hsSprite()
{
	DeleteDC(imgDC);
	DeleteObject(imgbit);
}


void hsSprite::SetOption(float m_size, float m_pivotX, float m_pivotY)
{
	size = m_size;
	pivotX = m_pivotX;
	pivotY = m_pivotY;
}




