#pragma once
class General :public GameObject
{
	//�ִϸ��̼� ����ü��
	hsSprite* NowAnime;
	hsSprite Anime[8];
	int State;
	//��������
	hsRect SearchRect;
	//������ ���ݹ���
	hsRect AttackRect;

	hsRect R_Attack;
	hsRect L_Attack;

	float AttackTime;
	float R_At;
	float L_At;

	bool isAttacking;
	//���ǹ���
	//�÷��̾��ǹ���
	int P_dir;
	//���ǵ�
	int Speed;
	//����
	int M_State;
	//HP
	int Hp;
	
	bool isDead;
public:

	int M_dir;
	General(int PosX, int PosY);
	General();
	virtual~General();
	virtual void Update();
	virtual void Render();
	virtual void Debug();
	virtual void init();
	virtual void init(hsSprite img[]);
	void Damage();
	void Hit();
	void Dead();
	void Run();
	void Attack();
	void GroundCheck();
};

