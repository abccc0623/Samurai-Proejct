#pragma once
class GameManager
{
	static GameManager* instance;
	//������Ʈ ����
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
	//���� ������Ʈ�� ������Ʈ
	void Update();
	//���ӿ�����Ʈ���� �÷����´�
	void input_obj(GameObject* obj);
	//Ʈ�� ������Ʈ ����
	void CreateTrap(int PosX, int PosY, int Left, int top, int right, int bottom);
	//���� ����
	void CreateSton(int PosX, int PosY, int Left, int top, int right, int bottom);
	//�浹ó���� ������Ʈ �÷�����
	void pushCollider(GameObject* obj);
	//�浹ó��
	bool Collision(GameObject* obj);

	void CreateMap();
	
};

