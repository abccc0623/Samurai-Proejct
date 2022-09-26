#pragma once


enum State
{
	Idle,
	Fighting,
	Search,
	Attack,
	Hit,
};
class Monster: public GameObject
{
	//�ִϸ��̼� ����ü��
	hsSprite* NowAnime;
	hsSprite Anime[12];

	//��������
	hsRect SearchRect;
	//������ ���ݹ���
	hsRect AttackRect;


	hsRect R_Attack;
	hsRect L_Attack;

	
public:

	int Hp;
	int Speed;
	
	//���� ����
	int M_State;
	//���Ͱ� ���� ����
	int dir;

	bool isDead;
	Monster(int PosX, int PosY);
	virtual~Monster();
	virtual void Update();
	virtual void Render();
	virtual void Debug();
	virtual void init();
	virtual void init(hsSprite img[]);
	void Damage();
	

	
};

