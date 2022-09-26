#pragma once

class GameObject
{
public:
	hsVector2	Pos;			//��ü�� ��ġ
	hsRect		Collider;		//�浹����

	//�̰�ü ������������
	bool isRender;
	//�̰�ü�� ������������
	bool isDebug;
	//�̰�ü�� ���������
	bool isDelete;
	//�́�ü�� �浹ü ����
	bool isCollider;
	//�浹�ߴ���
	bool ishit;
	

	
	GameObject();
	virtual ~GameObject();
	virtual void Update()	=0;
	virtual void Render()	=0;
	virtual void Debug()	=0;
	virtual void init()		=0;
};

