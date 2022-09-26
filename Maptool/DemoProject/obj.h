#pragma once
class obj
{
public:
	hsVector2 Pos;
	hsSprite img;
	obj();
	~obj();


	void Render();
	void Create(hsSprite* img, int PosY,int PosX);

	
	
};

