#pragma comment(lib,"winmm")
#include <windows.h>
#include <digitalv.h>
#include "sound.h"
#include "../hsEngine/pch.h"

#include "General.h"
#include "Player.h"
#include "Eclass.h"
#include "Impact.h"
#include "Monster.h"
#include "Door.h"
#include "Trap.h"
#include "TriggerMonster.h"
#include <vector>
#include "GameManager.h"

class Sound;
extern hsEngine* Engine;
extern int GameNum;
GameManager* GameManager::instance = 0;
GameManager::GameManager()
{
	nowCount = 0;
	Stage = 1;
	isDebug = false;
	for (int i = 0; i < TileCountMax; i++)
	{
		Tile[i] = NULL;
	}
}
GameManager::~GameManager()
{
	delete instance;
	for (int i = 0; i < 12; i++)
	{
		DeleteObject(Monster01[i].imgbit);
		DeleteDC(Monster01[i].imgDC);
	}

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
	CreateMap();

	for (int i = 0; i < ImPList.size(); i++)
	{
		if (ImPList[i] == nullptr)
		{
			continue;
		}

		if (ImPList[i]->isRender == false)
		{
			//delete ImPList[i];
			ImPList[i] = nullptr;
		}
		else
		{
			ImPList[i]->Render();
			
		}
	}

	if (GetAsyncKeyState(VK_F5) & 0x0001)
	{
		if (isDebug == true)
		{
			isDebug = false;
		}
		else
		{
			isDebug = true;
		}
	}

	for (int i = 0; i < ObjList.size(); i++)
	{
		//없으면 그냥 다음놈으로
		if (ObjList[i] == nullptr)
		{
			continue;
		}
		//죽은놈이라면 삭제하고 다음놈으로
		if (ObjList[i]->isDelete == true)
		{
			delete ObjList[i];
			ObjList[i] = NULL;
			continue;
		}
		
		//오브젝트 업데이트를 한다
		ObjList[i]->Update();

		if (ObjList[i]!= nullptr && ObjList[i]->isRender == true)
		{
			ObjList[i]->Render();
		}

		if (ObjList[i] != nullptr && isDebug == true)
		{
			ObjList[i]->Debug();
		}
	}

	if (isDebug == true)
	{
		Engine->DebugGameOption(RGB(255, 0, 0));
		Engine->DebugGrid(8000, 4000, 50, 50, RGB(0, 0, 0));
		Player::GetPlayer()->Debug();
	}


	





}
void GameManager::input_obj(GameObject* obj)
{
	ObjList.push_back(obj);
}
void GameManager::init()
{
	LoadSprite();
	CreateMap();
	LoadStage(1);
}
void GameManager::pushCollider(GameObject* obj)
{
	ColliderList.push_back(obj);
}

//충돌 검사
bool GameManager::Collision(GameObject* obj)
{
	for (int i = 0; i <ColliderList.size(); i++)
	{
		
		if (ColliderList[i] != nullptr &&
			obj != ColliderList[i] &&
			ColliderList[i]->isCollider == false)
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
bool GameManager::Collision(hsRect rect)
{
	for (int i = 0; i < ColliderList.size(); i++)
	{
		if (ColliderList[i] == nullptr){continue;}
		if (ColliderList[i]->isCollider == false) { continue; }

		//충돌 했다면
		if (rect == ColliderList[i]->Collider)
		{
			ColliderList[i]->ishit = true;
		}

	}

	return false;
}
void GameManager::ColliderInput(GameObject* temp)
{
	bool input = false;
	for (int i = 0; i < ColliderList.size(); i++)
	{
		if (ColliderList[i] == nullptr)
		{
			ColliderList[i] = temp;
			input = true;
			break;
		}
	}

	if (input == false)
	{
		ColliderList.push_back(temp);
	}
}

//로드
void GameManager::Load(const char* path)
{
	FILE* fp = NULL;
	Data hs;
	fp = fopen(path, "rb");
	if (fp == NULL)
	{
		return;
	}
	fread(&Mapdata, sizeof(Data), 1, fp);

	fclose(fp);
}
void GameManager::LoadSprite()
{
	
	trap = Engine->LoadSprite("../GameData/trap.bmp");
	trap->SetOption(0.25f, 0.5f, 0.5f);
	Engine->CreateAnime(trap, 3);

	door = Engine->LoadSprite("../GameData/Door.bmp");
	door->SetOption(1, 0.5f,0.5f);

	//타일불러오기
	{
		Tile[0] = Engine->LoadSprite("../GameData/brick.bmp");
		Tile[0]->SetOption(0.5f, 0, 0);

		Tile[1] = Engine->LoadSprite("../GameData/brick.bmp");
		Tile[1]->SetOption(0.5f, 0, 0);

		Tile[2] = Engine->LoadSprite("../GameData/brick.bmp");
		Tile[2]->SetOption(0.5f, 0, 0);

		Tile[3] = Engine->LoadSprite("../GameData/brick.bmp");
		Tile[3]->SetOption(0.5f, 0, 0);

		Tile[4] = Engine->LoadSprite("../GameData/brick.bmp");
		Tile[4]->SetOption(0.5f, 0, 0);
	}
	//스테이지 맵
	{
		Intro[0] = Engine->LoadSprite("../GameData/map/intro/scene01.bmp");
										
		Map01[0] = Engine->LoadSprite("../GameData/map/stage01/tutorial map_1.bmp");
		Map01[1] = Engine->LoadSprite("../GameData/map/stage01/tutorial map_2.bmp");
		Map01[2] = Engine->LoadSprite("../GameData/map/stage01/tutorial map_3.bmp");
		Map01[3] = Engine->LoadSprite("../GameData/map/stage01/tutorial map_4.bmp");
									
		Map02[0] = Engine->LoadSprite("../GameData/map/stage02/StageA map_1.bmp");
		Map02[1] = Engine->LoadSprite("../GameData/map/stage02/StageA map_2.bmp");
		Map02[2] = Engine->LoadSprite("../GameData/map/stage02/StageA map_3.bmp");
		Map02[3] = Engine->LoadSprite("../GameData/map/stage02/StageA map_4.bmp");
									
		Map03[0] = Engine->LoadSprite("../GameData/map/stage03/StageB map_1.bmp");
		Map03[1] = Engine->LoadSprite("../GameData/map/stage03/StageB map_2.bmp");
		Map03[2] = Engine->LoadSprite("../GameData/map/stage03/StageB map_3.bmp");
		Map03[3] = Engine->LoadSprite("../GameData/map/stage03/StageB map_4.bmp");
	}
	//임팩트 불러오기
	{
		//피 왼쪽
		ImpactList[(int)IMPACT::Blood_L] = *Engine->LoadSprite("../GameData/Impact/Blood_L.bmp");
		ImpactList[(int)IMPACT::Blood_L].SetOption(0.75f, 0.5f, 0.5f);
		Engine->CreateAnime(&ImpactList[(int)IMPACT::Blood_L], 5, false);
		//피 오른쪽
		ImpactList[(int)IMPACT::Blood_R] = *Engine->LoadSprite("../GameData/Impact/Blood_L.bmp");
		ImpactList[(int)IMPACT::Blood_R].SetOption(0.75f, 0.5f, 0.5f);
		Engine->CreateAnime(&ImpactList[(int)IMPACT::Blood_R], 5, false);

		//피 01
		ImpactList[(int)IMPACT::Blood_01] = *Engine->LoadSprite("../GameData/Impact/Blood_01.bmp");
		ImpactList[(int)IMPACT::Blood_01].SetOption(0.5f, 0.5f, 0.6f);
		Engine->CreateAnime(&ImpactList[(int)IMPACT::Blood_01], 1);

		//피 02
		ImpactList[(int)IMPACT::Blood_02] = *Engine->LoadSprite("../GameData/Impact/Blood_02.bmp");
		ImpactList[(int)IMPACT::Blood_02].SetOption(0.5f, 0.5f, 0.6f);
		Engine->CreateAnime(&ImpactList[(int)IMPACT::Blood_02], 1);

		//피 03
		ImpactList[(int)IMPACT::Blood_03] = *Engine->LoadSprite("../GameData/Impact/Blood_03.bmp");
		ImpactList[(int)IMPACT::Blood_03].SetOption(0.5f, 0.5f, 0.6f);
		Engine->CreateAnime(&ImpactList[(int)IMPACT::Blood_03], 1);


		//히트 1
		ImpactList[(int)IMPACT::HIT_01] = *Engine->LoadSprite("../GameData/Impact/HIT_01.bmp");
		ImpactList[(int)IMPACT::HIT_01].SetOption(1, 0.5f, 0.5f);
		Engine->CreateAnime(&ImpactList[(int)IMPACT::HIT_01], 4, false);
		//히트 2
		ImpactList[(int)IMPACT::HIT_02] = *Engine->LoadSprite("../GameData/Impact/HIT_02.bmp");
		ImpactList[(int)IMPACT::HIT_02].SetOption(1, 0.5f, 0.5f);
		Engine->CreateAnime(&ImpactList[(int)IMPACT::HIT_02], 4, false);
		//히트 3
		ImpactList[(int)IMPACT::HIT_03] = *Engine->LoadSprite("../GameData/Impact/HIT_03.bmp");
		ImpactList[(int)IMPACT::HIT_03].SetOption(1, 0.5f, 0.5f);
		Engine->CreateAnime(&ImpactList[(int)IMPACT::HIT_03], 4, false);

		//먼지 오른쪽
		ImpactList[(int)IMPACT::Lightning01] =*Engine->LoadSprite("../GameData/Impact/Lightning01.bmp");
		ImpactList[(int)IMPACT::Lightning01].SetOption(3, 0.5f, 0.5f);
		Engine->CreateAnime(&ImpactList[(int)IMPACT::Lightning01], 9);

		//먼지 왼쪽
		ImpactList[(int)IMPACT::Lightning01] = *Engine->LoadSprite("../GameData/Impact/Lightning01.bmp");
		ImpactList[(int)IMPACT::Lightning01].SetOption(3, 0.5f, 0.5f);
		Engine->CreateAnime(&ImpactList[(int)IMPACT::Lightning01], 9);

	}
	//쫄병01관련 스프라이트 
	{
		//쫄병1 몬스터 스프라이트
		Monster01[(int)MONSTER::IDLE_L] = *Engine->LoadSprite("../GameData/monster/monster01/Idle_L.bmp");
		Monster01[(int)MONSTER::IDLE_L].SetOption(0.5f, 0.4f, 0.85f);
		Engine->CreateAnime(&Monster01[(int)MONSTER::IDLE_L], 5);
		//오른쪽 숨쉬기
		Monster01[(int)MONSTER::IDLE_R] = *Engine->LoadSprite("../GameData/monster/monster01/Idle_R.bmp");
		Monster01[(int)MONSTER::IDLE_R].SetOption(0.5f, 0.5f, 0.85f);
		Engine->CreateAnime(&Monster01[(int)MONSTER::IDLE_R], 5);
		//왼쪽 걷기
		Monster01[(int)MONSTER::RUN_L] = *Engine->LoadSprite("../GameData/monster/monster01/Walking_L.bmp");
		Monster01[(int)MONSTER::RUN_L].SetOption(0.5f, 0.5f, 0.85f);
		Engine->CreateAnime(&Monster01[(int)MONSTER::RUN_L], 3);
		//오른쪽 걷기
		Monster01[(int)MONSTER::RUN_R] = *Engine->LoadSprite("../GameData/monster/monster01//Walking_R.bmp");
		Monster01[(int)MONSTER::RUN_R].SetOption(0.5f, 0.5f, 0.85f);
		Engine->CreateAnime(&Monster01[(int)MONSTER::RUN_R], 3);

		//피격_오른쪽
		Monster01[(int)MONSTER::HIT_R] = *Engine->LoadSprite("../GameData/monster/monster01/hit_R.bmp");
		Monster01[(int)MONSTER::HIT_R].SetOption(0.5f, 0.5f, 0.85f);
		Engine->CreateAnime(&Monster01[(int)MONSTER::HIT_R], 3, false);

		//피격_왼쪽
		Monster01[(int)MONSTER::HIT_L] = *Engine->LoadSprite("../GameData/monster/monster01/hit_L.bmp");
		Monster01[(int)MONSTER::HIT_L].SetOption(0.5f, 0.5f, 0.85f);
		Engine->CreateAnime(&Monster01[(int)MONSTER::HIT_L], 3, false);

		//죽음 _오른쪽
		Monster01[(int)MONSTER::DEAD_R] = *Engine->LoadSprite("../GameData/monster/monster01/Dead_R.bmp");
		Monster01[(int)MONSTER::DEAD_R].SetOption(0.5f, 0.5f, 0.85f);
		Engine->CreateAnime(&Monster01[(int)MONSTER::DEAD_R], 14, false);

		//죽음 _왼쪽
		Monster01[(int)MONSTER::DEAD_L] = *Engine->LoadSprite("../GameData/monster/monster01/Dead_L.bmp");
		Monster01[(int)MONSTER::DEAD_L].SetOption(0.5f, 0.5f, 0.85f);
		Engine->CreateAnime(&Monster01[(int)MONSTER::DEAD_L], 14, false);

		//공격준비 공격준비
		Monster01[(int)MONSTER::ATTACK_READY_R] = *Engine->LoadSprite("../GameData/monster/monster01/AttackBase_R.bmp");
		Monster01[(int)MONSTER::ATTACK_READY_R].SetOption(0.5f, 0.5f, 0.85f);
		Engine->CreateAnime(&Monster01[(int)MONSTER::ATTACK_READY_R], 10, false);

		//공격준비 왼쪽
		Monster01[(int)MONSTER::ATTACK_READY_L] = *Engine->LoadSprite("../GameData/monster/monster01/AttackBase_L.bmp");
		Monster01[(int)MONSTER::ATTACK_READY_L].SetOption(0.5f, 0.5f, 0.85f);
		Engine->CreateAnime(&Monster01[(int)MONSTER::ATTACK_READY_L], 10, false);

		//공격 오른쪽
		Monster01[(int)MONSTER::ATTACK_R] = *Engine->LoadSprite("../GameData/monster/monster01/Attack_R.bmp");
		Monster01[(int)MONSTER::ATTACK_R].SetOption(0.5f, 0.5f, 0.85f);
		Engine->CreateAnime(&Monster01[(int)MONSTER::ATTACK_R], 11, false);

		//공격왼쪽
		Monster01[(int)MONSTER::ATTACK_L] = *Engine->LoadSprite("../GameData/monster/monster01/Attack_L.bmp");
		Monster01[(int)MONSTER::ATTACK_L].SetOption(0.5f, 0.5f, 0.85f);
		Engine->CreateAnime(&Monster01[(int)MONSTER::ATTACK_L], 11, false);
	}
	//쫄병 02관련 스프라이트
	{
	 	float Monster02_Size = 0.75f;
		float PivotX = 0.4f;
		float PivotY = 0.85f;
		Monster02[(int)MONSTER::RUN_R]= *Engine->LoadSprite("../GameData/monster/monster02/Run_R.bmp");
		Monster02[(int)MONSTER::RUN_R].SetOption(Monster02_Size, 0.5f, PivotY);
		Engine->CreateAnime(&Monster02[(int)MONSTER::RUN_R], 3);

		Monster02[(int)MONSTER::RUN_L] = *Engine->LoadSprite("../GameData/monster/monster02/Run_L.bmp");
		Monster02[(int)MONSTER::RUN_L].SetOption(Monster02_Size, PivotX, PivotY);
		Engine->CreateAnime(&Monster02[(int)MONSTER::RUN_L], 3);

		Monster02[(int)MONSTER::DEAD_R] = *Engine->LoadSprite("../GameData/monster/monster02/Dead_R.bmp");
		Monster02[(int)MONSTER::DEAD_R].SetOption(Monster02_Size, PivotX, 0.8f);
		Engine->CreateAnime(&Monster02[(int)MONSTER::DEAD_R], 27,false);

		Monster02[(int)MONSTER::DEAD_L] = *Engine->LoadSprite("../GameData/monster/monster02/Dead_L.bmp");
		Monster02[(int)MONSTER::DEAD_L].SetOption(Monster02_Size, PivotX, 0.8f);
		Engine->CreateAnime(&Monster02[(int)MONSTER::DEAD_L], 27,false);

		Monster02[(int)MONSTER::HIT_R] = *Engine->LoadSprite("../GameData/monster/monster02/Hit_R.bmp");
		Monster02[(int)MONSTER::HIT_R].SetOption(Monster02_Size, PivotX, PivotY);
		Engine->CreateAnime(&Monster02[(int)MONSTER::HIT_R], 3,false);

		Monster02[(int)MONSTER::HIT_L] = *Engine->LoadSprite("../GameData/monster/monster02/Hit_L.bmp");
		Monster02[(int)MONSTER::HIT_L].SetOption(Monster02_Size, PivotX, PivotY);
		Engine->CreateAnime(&Monster02[(int)MONSTER::HIT_L], 3,false);

		Monster02[(int)MONSTER::ATTACK_R] = *Engine->LoadSprite("../GameData/monster/monster02/Attack_R.bmp");
		Monster02[(int)MONSTER::ATTACK_R].SetOption(Monster02_Size, 0.3f, PivotY);
		Engine->CreateAnime(&Monster02[(int)MONSTER::ATTACK_R], 10,false);

		Monster02[(int)MONSTER::ATTACK_L] = *Engine->LoadSprite("../GameData/monster/monster02/Attack_L.bmp");
		Monster02[(int)MONSTER::ATTACK_L].SetOption(Monster02_Size, 0.6f, PivotY);
		Engine->CreateAnime(&Monster02[(int)MONSTER::ATTACK_L], 10,false);
	}

	//게임 사운드
	{
		GameSound[(int)SOUND::BGM_MAIN].soundOpen("../Sound/BGM/BGM_Main.mp3");
		GameSound[(int)SOUND::BGM_RAINY].soundOpen("../Sound/BGM/BGM_rainy.mp3");
		GameSound[(int)SOUND::BGM_TITLE].soundOpen("../Sound/BGM/BGM_Title.wav");
		
		GameSound[(int)SOUND::PLAYER_ATTACK].soundOpen("../Sound/player/player_attack.mp3");
		GameSound[(int)SOUND::PLAYER_HIT].soundOpen("../Sound/player/Player_hit.mp3");
		GameSound[(int)SOUND::PLAYER_JUMP].soundOpen("../Sound/player/player_jump.mp3");
		GameSound[(int)SOUND::PLAYER_RUN].soundOpen("../Sound/player/player_run.mp3");
		GameSound[(int)SOUND::PLAYER_SHADOW].soundOpen("../Sound/player/player_shadow.mp3");
		GameSound[(int)SOUND::PLAYER_SKILL].soundOpen("../Sound/player/player_skill.mp3");
		
		GameSound[(int)SOUND::ENEMY_ATTACK].soundOpen("../Sound/enemy/enemy_attack.mp3");
		GameSound[(int)SOUND::ENEMY_HIT1].soundOpen("../Sound/enemy/enemy_hit.mp3");
		GameSound[(int)SOUND::ENEMY_HIT2].soundOpen("../Sound/enemy/enemy_hit2.mp3");
		GameSound[(int)SOUND::ENEMY_HIT3].soundOpen("../Sound/enemy/enemy_hit3.mp3");
		GameSound[(int)SOUND::ENEMY_READY].soundOpen("../Sound/enemy/enemy_ready.mp3");
	}
}

//배열체크
bool GameManager::MapCheck(int PosX,int PosY)
{
	//해당 좌표를 배열위치의 위치로 변경
	int X = PosX / 50;
	int Y = PosY / 50;

	//타일이 없다면 true
	if (Mapdata.SaveMap[Y][X] == 0) 
	{
		return true;
	}
	else
	{
		return false;
	}	
}

//몬스터 생성
void GameManager::CreateMonster01(int PosX,int PosY)
{
	switch (Stage)
	{
	case 1:
		MonsterCount[0]++;
		break;
	case 2:
		MonsterCount[1]++;
		break;
	case 3:
		MonsterCount[2]++;
		break;
	}



	Monster* temp = new Monster(PosX, PosY);
	temp->init(Monster01);

	ObjInput(temp);
	ColliderInput(temp);
}
General* GameManager::CreateMonster02(int PosX, int PosY)
{
	switch (Stage)
	{
	case 1:
		MonsterCount[0]++;
		break;
	case 2:
		MonsterCount[1]++;
		break;
	case 3:
		MonsterCount[2]++;
		break;
	}

	General* temp = new General(PosX, PosY);
	temp->init(Monster02);

	ObjInput(temp);
	ColliderInput(temp);
	return temp;
}
void GameManager::CreateTriggerMonster(int PosX, int PosY)
{
	TriggerMonster* temp = new TriggerMonster(PosX, PosY);
	//temp->init(Monstetempr01);
	ObjInput(temp);
	ColliderInput(temp);
}
Door* GameManager::CreateDoor(int PosX, int PosY)
{
	Door* temp = new Door(*door);
	temp->Pos.cx = PosX;
	temp->Pos.cy = PosY;
	bool input = false;
	ObjInput(temp);
	ColliderInput(temp);
	return temp;
}
void GameManager::CreateMap()
{
	switch (Stage)
	{

	case 1:
		Engine->TileRender(Map01[0], 0, 0);
		Engine->TileRender(Map01[1], 1920, 0);
		Engine->TileRender(Map01[2], 0, 1080);
		Engine->TileRender(Map01[3], 1920,1080);
		break;
	case 2:
		Engine->TileRender(Map02[0], 0, 0);
		Engine->TileRender(Map02[1], 1920, 0);
		Engine->TileRender(Map02[2], 0, 1080);
		Engine->TileRender(Map02[3], 1920, 1080);
		break;
	case 3:
		Engine->TileRender(Map03[0], 0, 0);
		Engine->TileRender(Map03[1], 1920, 0);
		Engine->TileRender(Map03[2], 0, 1080);
		Engine->TileRender(Map03[3], 1920, 1080);
		break;
	}
	



	for (int i = 0; i < 80; i++)
	{
		for (int j = 0; j < 46; j++)
		{
			if (Mapdata.SaveMap[j][i] == 1)
			{
				switch (Stage)
				{
				case 1:
					Engine->TileRender(Tile[0], i * 50, j * 50);
					break;
				case 2:
					Engine->TileRender(Tile[1], i * 50, j * 50);
					break;
				case 3:
					Engine->TileRender(Tile[2], i * 50, j * 50);
					break;
				}
				
			}
		}
	}
}
Impact* GameManager::CreateImpact(int PosX,int PosY)
{
	bool input = false;
	Impact* temp = new Impact(PosX, PosY);
	temp->init(ImpactList);

	for (int i = 0; i < ImPList.size(); i++)
	{
		if (ImPList[i] == nullptr)
		{
			ImPList[i] = temp;
			input = true;
			break;
		}
	}

	if (input == false)
	{
		ImPList.push_back(temp);
	}
	return temp;
}


void GameManager::LoadStage(int stageNum)
{
	switch (stageNum)
	{
	case 1:
		stage01();
		break;
	case 2:
		stage02();
		break;
	case 3:
		stage03();
		break;
	}
}
void GameManager::ObjInput(GameObject* temp)
{
	bool input = false;
	//리스트에 빈곳찾아넣는다
	for (int i = 0; i < ObjList.size(); i++)
	{
		if (ObjList[i] == nullptr)
		{
			ObjList[i] = temp;
			input = true;
			break;
		}
	}
	//빈곳이없다면 새로만들어서 넣는다
	if (input == false)
	{
		ObjList.push_back(temp);
	}
}
void GameManager::RetrunStage()
{
	ReSetStage();
	switch (Stage)
	{
	case 1:
		stage01();
		break;
	case 2:
		stage02();
		break;
	case 3:
		stage03();
		break;
	}

}
void GameManager::CreateTrap(int PosX,int PosY,int Dis)
{
	Trap* temp = new Trap();
	temp->init(*trap, PosX, PosY, Dis);
	ObjInput(temp);
	ColliderInput(temp);
}
void GameManager::MonsterCountDown()
{
	switch (Stage)
	{
	case 1:
		MonsterCount[0]--;
		break;
	case 2:
		MonsterCount[1]--;
		break;
	case 3:
		MonsterCount[2]--;
		break;
	}

	if (stageDoor[0] != nullptr && MonsterCount[0] <= 0)
	{
		stageDoor[0]->isCollider = true;
	}
	if (stageDoor[1] != nullptr && MonsterCount[1] <= 0)
	{
		stageDoor[1]->isCollider = true;
	}
	if (stageDoor[2] != nullptr && MonsterCount[2] <= 0)
	{
		stageDoor[2]->isCollider = true;
	}


}
void GameManager::PlayGameSound(int num)
{
	GameSound[num].soundSeek(0);
	GameSound[num].soundPlay();
}
Sound* GameManager::PlayGameSound_Loop(int num)
{
	GameSound[num].soundPlayLooping();
	return &GameSound[num];
}

void GameManager::stage01()
{
	Load("../SaveMap/Stage01.sav");
	Player::GetPlayer()->Pos.cx = 400;
	Player::GetPlayer()->Pos.cy = 1200;
	stageDoor[0] = CreateDoor(3300, 1800);
	//CreateMonster02(1900, 1900);
	//CreateMonster02(1900, 1900);
	CreateMonster01(1900, 1900);
	CreateMonster02(1900, 1900);
}
void GameManager::stage02()
{
	ReSetStage();
	Load("../SaveMap/Stage02.sav");
	Player::GetPlayer()->Pos.cx = 250;
	Player::GetPlayer()->Pos.cy = 2000;
	CreateTrap(1250, 1200,500);

	CreateMonster01(1150, 2100);
	CreateMonster01(1650, 2100);
	CreateMonster01(1150, 2100);


	CreateMonster01(1450, 2100);
	CreateMonster01(1850, 2100);
	CreateMonster01(1550, 2100);

	CreateMonster02(1850, 2100);
	CreateMonster02(1550, 2100);

	CreateMonster01(3150, 1200);
	CreateMonster01(2820, 1200);
	CreateMonster01(2660, 1200);

	CreateMonster01(1720, 500);
	CreateMonster01(2170, 500);
	CreateMonster01(1840, 500);

	CreateMonster01(380,700);
	CreateMonster01(260,700);


	stageDoor[1] =CreateDoor(3650, 200);
}
void GameManager::stage03()
{
	
	ReSetStage();
	Load("../SaveMap/Stage03.sav");
	CreateMap();
	Player::GetPlayer()->Pos.cx = 400;
	Player::GetPlayer()->Pos.cy = 0;

	CreateTrap(2800, 1400, 600);
	CreateMonster01(1000, 700);
	CreateMonster01(1200, 700);
	CreateMonster01(1100, 700);



	CreateMonster01(1000, 2100);
	CreateMonster01(1200, 2100);
	CreateMonster01(1100, 2100);
	CreateMonster01(1250, 2100);

	CreateMonster01(1310, 2100);
	CreateMonster01(1500, 2100);



	CreateTriggerMonster(1100, 2000);

	stageDoor[2] = CreateDoor(3550, 300);
}

int GameManager::GetStage()
{
	return Stage;
}


void GameManager::NextStage()
{
	Stage++;
	if (Stage >= 4)
	{
		GameNum = 3;
	}
	else
	{
		LoadStage(Stage);
	}
}
void GameManager::ReSetStage()
{

	for (int i = 0; i < ObjList.size(); i++)
	{
		delete ObjList[i];
		ObjList[i] = nullptr;
	
	}     
	for (int i = 0; i < ColliderList.size(); i++)
	{
		ColliderList[i] = nullptr;
	}
	for (int i = 0; i < ImPList.size(); i++)
	{
		delete ImPList[i];
		ImPList[i] = nullptr;
	}
	for (int i =0; i < 3; i++)
	{
		MonsterCount[i] = 0;
	}


	//ObjList.clear();
	//ColliderList.clear();
}



