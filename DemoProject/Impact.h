#pragma once
class Impact : public GameObject
{
	//����Ʈ ����Ʈ��
	hsSprite imgList[12];
public:
	//���� �����ִ� ����Ʈ
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