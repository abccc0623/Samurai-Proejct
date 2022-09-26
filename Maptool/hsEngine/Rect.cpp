#include "pch.h"
hsRect::hsRect()
{
	TOP		= 0;
	BOTTOM	= 0;
	RIGHT	= 0;
	LEFT	= 0;
}

hsRect::~hsRect()
{

}

bool hsRect::operator==(hsRect rect)
{
	bool Collision = false;
	if (TOP		<= rect.BOTTOM &&
		BOTTOM	>= rect.TOP &&
		RIGHT	>= rect.LEFT &&
		LEFT	<= rect.RIGHT)
	{

		Collision = true;
	}

	return Collision;
}

void hsRect::SetCenter(int posX,int posY,int Left,int top, int Right,int bottom)
{
	Center.cx = posX;
	Center.cy = posX;


	LEFT	= posX - Left;
	RIGHT	= posX + Right;
	TOP		= posY - top;
	BOTTOM	= posY + bottom;
}

hsRect hsRect::GetRect()
{
	hsRect rect;
	rect.TOP	= TOP;
	rect.BOTTOM = BOTTOM;
	rect.LEFT	= LEFT;
	rect.RIGHT	= RIGHT;
	return rect;
}
