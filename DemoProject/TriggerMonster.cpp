#pragma comment(lib,"winmm")
#include <windows.h>
#include <digitalv.h>
#include "sound.h"

#include "../hsEngine/pch.h"
#include "Player.h"
#include "GameManager.h"
#include "Impact.h"
#include "Eclass.h"
#include "Monster.h"
#include "General.h"
#include "TriggerMonster.h"
extern hsEngine* Engine;
TriggerMonster::TriggerMonster(int PosX, int PosY)
{
	Pos.cx = PosX;
	Pos.cy = PosY;
	CreateTime	= 0;
	WaveCount	= 0;
	isRender	= true;
	isDebug		= true;
	isCollider	= true;
}

TriggerMonster::~TriggerMonster()
{


}

void TriggerMonster::Update()
{
	hit();
	Collider.SetCenter(Pos.cx, Pos.cy, 50, 50, 50, 50);
}

void TriggerMonster::Render()
{
}

void TriggerMonster::Debug()
{
	Engine->DrawRectangle(Collider, RGB(255, 0, 0));

}

void TriggerMonster::init()
{

}

void TriggerMonster::hit()
{
	if (ishit == true )
	{
		CreateTime += Engine->GetDeltaTime();
		if (CreateTime > 2)
		{
			General* temp01 = GameManager::GetGM()->CreateMonster02(250, 2100);
			temp01->M_dir = 1;
			General* temp02 = GameManager::GetGM()->CreateMonster02(3200, 2100);
			temp02->M_dir = -1;
			CreateTime = 0;
			WaveCount++;
		}		
	}

	if (WaveCount > 4)
	{
		ishit = false;
	}

}
