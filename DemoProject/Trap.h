#pragma once
class Trap:public GameObject
{
	hsSprite img;
	int Distance;
	int MaxDir;
	int Speed;
	
	bool isRight;
	bool isLeft;
public:
	Trap();
	~Trap();
	virtual void Update();
	virtual void Render();
	virtual void Debug();
	virtual void init();
	void init(hsSprite m_img, int PosX, int PosY, int Dis);
};

