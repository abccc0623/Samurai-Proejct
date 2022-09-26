#include "../hsEngine/pch.h"
#include "Ston.h"

extern hsEngine* Engine;
void Ston::Update()
{

}

void Ston::Render()
{


}

void Ston::init()
{
	Pos.cx = 0;
	Pos.cy = 0;
	Collider.SetCenter(Pos.cx, Pos.cy, 100, 100, 100, 100);
	
}

void Ston::Debug()
{
	isDebug = true;
	Engine->DrawRectangle(Collider,RGB(0,0,255));
}

Ston::Ston()
{

}

Ston::~Ston()
{

}

