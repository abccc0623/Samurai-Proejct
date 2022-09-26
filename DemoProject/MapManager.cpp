#include "../hsEngine/pch.h"
#include "MapManager.h"


extern hsEngine* Engine;
MapManager* MapManager::instance = 0;
MapManager* MapManager::GetMap()
{
	if (instance == nullptr)
	{
		instance = new MapManager();
	}
	return instance;
}
void MapManager::init()
{
	//이미지들 불러오는곳
	//tile
	Ground = Engine->LoadSprite(L"../../4_Resources/GameData/10.bmp");
	BackGround = Engine->LoadSprite(L"../../4_Resources/GameData/green.bmp");
	//Ground->SetSize(1);
	//Ground->SetPivot(0, 0);
}	
MapManager::MapManager()
{
	
}
MapManager::~MapManager()
{

}
void MapManager::CreateMap()
{
	for (int i = 0; i < 10; i++) 
	{
		for (int j = 0; j < 10; j++)
		{
			if (Stage01[i][j] == 1)
			{
				Engine->SpriteRender(Ground, i*100, j*100);
			}
		}
	}

}
