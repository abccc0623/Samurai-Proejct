#include "../hsEngine/pch.h"
#include "obj.h"


extern hsEngine* Engine;
obj::obj()
{
	
}

obj::~obj()
{
	
}

void obj::Render()
{
	Engine->SpriteRender(&img,Pos.cx, Pos.cy);
}

void obj::Create(hsSprite* m_img, int PosY, int PosX)
{
	img = *m_img;
	Pos.cy = PosY;
	Pos.cx = PosX;
}



