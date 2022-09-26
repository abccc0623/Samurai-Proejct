#include "../hsEngine/pch.h"
#include "MapManager.h"
#include "Player.h"
#include "trap.h"
#include "Ston.h"
#include "GameManager.h"
#include <vector>

extern hsEngine* Engine;
GameManager* GameManager::instance = 0;
GameManager::GameManager()
{
	isDebug = true;
}
GameManager::~GameManager()
{
	delete instance;
}
GameManager* GameManager::GetGM()
{
	if (instance == nullptr)
	{
		instance = new GameManager();
	}
	return instance;
}

void GameManager::Update()
{
	for (int i = 0; i < ObjList.size(); i++)
	{
		//없으면 그냥 다음놈으로
		if (ObjList[i] == nullptr)
		{
			continue;
		}
		
		//디버깅상태일때는 디버그화면을 보여준다
		if (isDebug == true)
		{
			ObjList[i]->Debug();
			//Engine->DebugGameOption(RGB(255,0,0));
			//Engine->DebugGrid(2000,2000,50,50,RGB(0,255,0));
		}

		//오브젝트 업데이트를 한다
		ObjList[i]->Update();
		if (ObjList[i]->isRender == true)
		{
			ObjList[i]->Render();
		}

		//if(ObjList[i]->isCollider == )

		//CreateMap();
	}
}

void GameManager::input_obj(GameObject* obj)
{
	ObjList.push_back(obj);
}

void GameManager::init()
{
	Ground = Engine->LoadSprite(L"../../4_Resources/GameData/green.bmp");
	Ground->SetOption(1, 0, 0);

	CreateTrap(600,600,15,15,15,15);
	CreateSton(0,680,0,0,235,100);
	CreateSton(240,780, 0, 0, 215, 100);
	CreateSton(455, 890, 0, 0, 50, 100);
}

void GameManager::pushCollider(GameObject* obj)
{
	ColliderList.push_back(obj);
}

bool GameManager::Collision(GameObject* obj)
{
	for (int i = 0; i <ColliderList.size(); i++)
	{
		if (obj != ColliderList[i])
		{
			//충돌했을때 
			if (obj->Collider == ColliderList[i]->Collider)
			{
				obj->isCollider = true;
				break;
			}
			else
			{
				obj->isCollider = false;
			}
		}
	}

	

	return false;
}

void GameManager::CreateMap()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (stage01[j][i] == 1)
			{
				Engine->SpriteRender(Ground,i*100,j*100);
			}
		}
	}


}

void GameManager::CreateTrap(int PosX, int PosY, int Left, int top, int right, int bottom)
{
	trap* temp = new trap(PosX, PosY);
	temp->init();
	input_obj(temp);
	pushCollider(temp);
	temp->Collider.SetCenter(PosX, PosY, Left, top, right, bottom);
}
void GameManager::CreateSton(int PosX, int PosY, int Left, int top, int right, int bottom)
{
	Ston* temp = new Ston();
	temp->init();
	input_obj(temp);
	pushCollider(temp);
	temp->Collider.SetCenter(PosX,PosY, Left, top,right,bottom);
}

