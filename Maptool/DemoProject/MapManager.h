#pragma once
class MapManager
{
	static MapManager* instance;

	int stage = 0;
public:
	static MapManager* GetMap();
	//기본 타일 불러오기
	void init();

	void CreateMap();

	MapManager();
	~MapManager();
	

	


private:

	hsSprite* Ground;		//땅
	hsSprite* BackGround;	//뒷배경 
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

