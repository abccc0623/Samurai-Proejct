#pragma once
class GameManager
{
	static GameManager* instance;
	//오브젝트 관리
	std::vector<GameObject*>	ObjList;
	std::vector<GameObject*>	ColliderList;

	GameManager();
	~GameManager();



	hsSprite* Ground;
	int stage01[20][20]
	{
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1},
	};
	

public:
	bool isDebug;
	
	
	static GameManager* GetGM();

	void init();
	//게임 오브젝트들 업데이트
	void Update();
	//게임오브젝트들을 올려놓는다
	void input_obj(GameObject* obj);
	//트랩 오브젝트 생성
	void CreateTrap(int PosX, int PosY, int Left, int top, int right, int bottom);
	//지형 생성
	void CreateSton(int PosX, int PosY, int Left, int top, int right, int bottom);
	//충돌처리할 오브젝트 올려놓기
	void pushCollider(GameObject* obj);
	//충돌처리
	bool Collision(GameObject* obj);

	void CreateMap();
	
};

