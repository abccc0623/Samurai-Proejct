#pragma once
class MapManager
{
	static MapManager* instance;

	int stage = 0;
public:
	static MapManager* GetMap();
	//�⺻ Ÿ�� �ҷ�����
	void init();

	void CreateMap();

	MapManager();
	~MapManager();
	

	


private:

	hsSprite* Ground;		//��
	hsSprite* BackGround;	//�޹�� 
	int Stage01[10][10]
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
	
};

