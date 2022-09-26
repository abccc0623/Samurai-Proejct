#pragma once

class General;
class Impact;
class Door;
class GameManager
{
private:
	
	static GameManager* instance;
	//오브젝트 관리

	std::vector<GameObject*>	ObjList;
	std::vector<GameObject*>	ColliderList;
	std::vector<GameObject*>	ImPList;

	GameManager();
	~GameManager();

	
	int Stage;
	int TileCountMax = 5;

	Door* stageDoor[3];
	int nowCount;
	int MonsterCount[3];
	

	//Map[스테이지][맵 4분활맵]
	hsSprite* Map01[4];
	hsSprite* Map02[4];
	hsSprite* Map03[4];
	hsSprite* Intro[4];

	//쫄병 1 이미지
	hsSprite Monster01[12];
	//쫄병 2 이미지
	hsSprite Monster02[8];
	//임팩트 모음
	hsSprite ImpactList[14];
	hsSprite* door;
	hsSprite* trap;

	Sound GameSound[14];

	Data Mapdata;

	hsSprite* Tile[5];
	

	void stage01();
	void stage02();
	void stage03();
public:
	bool isDebug;
	
	
	static GameManager* GetGM();

	void init();
	//게임 오브젝트들 업데이트
	void Update();
	//게임오브젝트들을 올려놓는다
	void input_obj(GameObject* obj);
		
	//충돌처리할 오브젝트 올려놓기
	void pushCollider(GameObject* obj);
	//충돌처리
	bool Collision(GameObject* obj);
	bool Collision(hsRect rect);
	//타일맵 생성하기
	void CreateMap();
	//타일맵 불러오기
	void Load(const char* path);
	//스프라이트 불러오기
	void LoadSprite();
	//현재좌표에 타일이 있는지
	bool MapCheck(int PosX, int PosY);
	//몬스터 생성하기
	void CreateMonster01(int PosX, int PosY);
	General* CreateMonster02(int PosX, int PosY);
	void CreateTriggerMonster(int PosX, int PosY);

	//스테이지 로드
	void LoadStage(int stageNum);
	//문오브젝트 생성하기
	Door* CreateDoor(int PosX,int PosY);
	//오브젝트 관리 벡터에 오브젝트를 넣는다
	void ObjInput(GameObject* temp);
	//콜라이더 관리 벡터에 오브젝트를 넣는다
	void ColliderInput(GameObject* temp);
	void RetrunStage();
	void CreateTrap(int PosX, int PosY, int Dis);
	void MonsterCountDown();
	

	//사운드 플레이하기
	void PlayGameSound(int num);
	//사운드 플레이 무한
	Sound* PlayGameSound_Loop(int num);

	
	int GetStage();
	Impact* CreateImpact(int PosX, int PosY);
	void NextStage();
	void ReSetStage();
};

