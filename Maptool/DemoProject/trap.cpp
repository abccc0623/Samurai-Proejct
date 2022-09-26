#include "../hsEngine/pch.h"
#include "GameManager.h"
#include "trap.h"


extern hsEngine* Engine;
trap::trap(int PosX,int PosY)
{
	isRender	= true;
	Pos.cx		= PosX;
	Pos.cy		= PosY;
	MoveSpeed	= 0;
	img			= NULL;
	isRight		= true;
}

trap::~trap()
{
	delete img;
}


void trap::init()
{
	img = Engine->LoadSprite(L"../../4_Resources/GameData/trap.bmp");
	img->SetOption(0.1f, 0.5f,0.5f);
	Engine->CreateAnime(img, 3);

	Collider = hsRect();
	Collider.SetCenter(Pos.cx, Pos.cy, 50, 50, 50, 50);
	isRight = true;
	isDebug = true;
	MoveSpeed = 100;
	MoveRange.cx = Pos.cx+300;
	MoveRange.cy = Pos.cy+300;
	GameManager::GetGM()->input_obj(this);
}

void trap::Update()
{
	////È¸ÀüÈ¸¿À·ò~~~
	//if (isRight == true)
	//{
	//	Pos.cx += Engine->GetDeltaTime()* MoveSpeed;
	//	if (Pos.cx > MoveRange.cx)
	//	{
	//		isRight = false;
	//	}
	//}
	//else
	//{
	//	Pos.cx -= Engine->GetDeltaTime() * MoveSpeed;
	//	if (Pos.cx < MoveRange.cy)
	//	{
	//		isRight = true;
	//	}
	//}

}

void trap::Render()
{
	Engine->AnimeRender(img, Pos.cx, Pos.cy,0.1f);
}

void trap::Debug()
{
	Collider.SetCenter(Pos.cx, Pos.cy, 20, 20, 20, 20);
	Engine->DrawRectangle(Collider, RGB(0, 0, 255));
}

