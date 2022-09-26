#pragma once
class trap : public GameObject
{
	hsSprite* img;
	
	hsVector2 MoveRange;
	int MoveSpeed;
	bool isRight;
public:
	trap(int PosX, int PosY);
	~trap();

	
	virtual void Update();
	virtual void Render();
	virtual void init();
	virtual void Debug();
};