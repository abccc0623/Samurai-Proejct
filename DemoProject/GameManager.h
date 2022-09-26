#pragma once

class General;
class Impact;
class Door;
class GameManager
{
private:
	
	static GameManager* instance;
	//������Ʈ ����

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
	

	//Map[��������][�� 4��Ȱ��]
	hsSprite* Map01[4];
	hsSprite* Map02[4];
	hsSprite* Map03[4];
	hsSprite* Intro[4];

	//�̺� 1 �̹���
	hsSprite Monster01[12];
	//�̺� 2 �̹���
	hsSprite Monster02[8];
	//����Ʈ ����
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
	//���� ������Ʈ�� ������Ʈ
	void Update();
	//���ӿ�����Ʈ���� �÷����´�
	void input_obj(GameObject* obj);
		
	//�浹ó���� ������Ʈ �÷�����
	void pushCollider(GameObject* obj);
	//�浹ó��
	bool Collision(GameObject* obj);
	bool Collision(hsRect rect);
	//Ÿ�ϸ� �����ϱ�
	void CreateMap();
	//Ÿ�ϸ� �ҷ�����
	void Load(const char* path);
	//��������Ʈ �ҷ�����
	void LoadSprite();
	//������ǥ�� Ÿ���� �ִ���
	bool MapCheck(int PosX, int PosY);
	//���� �����ϱ�
	void CreateMonster01(int PosX, int PosY);
	General* CreateMonster02(int PosX, int PosY);
	void CreateTriggerMonster(int PosX, int PosY);

	//�������� �ε�
	void LoadStage(int stageNum);
	//��������Ʈ �����ϱ�
	Door* CreateDoor(int PosX,int PosY);
	//������Ʈ ���� ���Ϳ� ������Ʈ�� �ִ´�
	void ObjInput(GameObject* temp);
	//�ݶ��̴� ���� ���Ϳ� ������Ʈ�� �ִ´�
	void ColliderInput(GameObject* temp);
	void RetrunStage();
	void CreateTrap(int PosX, int PosY, int Dis);
	void MonsterCountDown();
	

	//���� �÷����ϱ�
	void PlayGameSound(int num);
	//���� �÷��� ����
	Sound* PlayGameSound_Loop(int num);

	
	int GetStage();
	Impact* CreateImpact(int PosX, int PosY);
	void NextStage();
	void ReSetStage();
};

