#pragma comment(lib,"winmm")
#include <windows.h>
#include <digitalv.h>
#include "sound.h"
#include "../hsEngine/pch.h"
#include "Player.h"
#include "GameManager.h"
#include "Door.h"

extern hsEngine* Engine;
Door::Door(hsSprite m_img)
{
	img = m_img;
	Next = false;
	isRender = true;
}
Door::~Door()
{
}
void Door::Update()
{
	Collider.SetCenter(Pos.cx, Pos.cy, 50, 100, 50, 100);
	//나와 플레이어와 충동했다면
	if (Player::GetPlayer()->Collider == Collider && isCollider == true)
	{
		if (Next == false)
		{
			GameManager::GetGM()->NextStage();
			Next = true;
		}
	}
}

void Door::Render()
{
	if (GameManager::GetGM()->GetStage() != 1)
	{
		Engine->AnimeRender(&img, Pos.cx, Pos.cy,1);
	}
}

void Door::Debug()
{
	
	if (Player::GetPlayer()->Collider == Collider)
	{
		Engine->DrawRectangle(Collider, RGB(255, 0, 0));
	}
	else
	{
		Engine->DrawRectangle(Collider, RGB(255, 255, 255));
	}
}

void Door::init()
{
	Next = false;
	Collider.SetCenter(Pos.cx, Pos.cy, 50, 50, 50, 50);
	isCollider = false;
}
