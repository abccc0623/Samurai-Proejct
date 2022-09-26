#pragma once
class Impact : public GameObject
{
	//임팩트 리스트들
	hsSprite imgList[12];
public:
	//현재 돌고있는 임팩트
	hsSprite *Main;
	int Random;


	void ChoiceNumber(int num);

	Impact(int PosX, int PosY);
	~Impact();

	
	virtual void Update();
	virtual void Render();
	virtual void init();
	virtual void Debug();
	void init(hsSprite img[]);
};