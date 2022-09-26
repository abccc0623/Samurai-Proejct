#pragma comment(lib,"winmm")
#include <windows.h>
#include <digitalv.h>
#include "sound.h"
#include "../hsEngine/pch.h"
#include "GameManager.h"
#include "Player.h"
#include "Trap.h"
extern hsEngine* Engine;
Trap::Trap()
{
	
}
Trap::~Trap()
{
}
void Trap::Update()
{
	Collider.SetCenter(Pos.cx, Pos.cy, 25, 0, 25, 50);

	if (Player::GetPlayer()->Collider == Collider)
	{
		Player::GetPlayer()->Dead();
	}



	if (isRight == true)
	{
		Pos.cx += Engine->GetDeltaTime() * Speed;
		if (Pos.cx >= Distance)
		{
			isRight = false;
			isLeft	= true;
			
		}
	}

	if (isLeft == true)
	{
		Pos.cx -= Engine->GetDeltaTime() * Speed;
		if (Pos.cx <= MaxDir)
		{
			isLeft = false;
			isRight = true;
		}
	}
}

void Trap::Render()
{
	Engine->AnimeRender(&img, Pos.cx, Pos.cy, 0.01f);
}

void Trap::Debug()
{
	Engine->DrawRectangle(Collider, RGB(255, 0, 0));
}

void Trap::init()
{
}

void Trap::init(hsSprite m_img, int PosX, int PosY,int Dis)
{
	img			= m_img;
	Pos.cx		= PosX;
	Pos.cy		= PosY;
	isRender	= true;
	Speed		= 300;
	isRight		= true;
	isLeft		= false;
	Distance	= Pos.cx + Dis;
	MaxDir		= Pos.cx;
}
