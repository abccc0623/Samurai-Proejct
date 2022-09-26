#pragma once


class Player : public GameObject
{
private:
	static Player* instance;
	
	hsSprite*	Anime[14];
	hsSprite*	playerAnime;
	

	int		APUP_Speed;
	float	AP;				//ĳ���� ��ų AP;
	int		Speed;			//ĳ���� ���ǵ�				
	int		DownSpeed;		//�������¼ӵ�
	int		dir;			//ĳ���Ͱ� ���¹���
	int		jumpCount;		//���� ����Ƚ��
	int		jumpSpeed;		//�����ϴ¼ӵ�

	
	float	imgAlpha;		//�÷��̾ �������ִ� �̹��� ���İ�		

	
	bool	isShadow;
	bool	isMove;			//�̵�������
	bool	jumping;		//���� ����������
	bool	isGround;		//���� ������
	bool	isAttack;
	bool	isBaseAttack;
	bool	isMoveAttack;
	hsKey key;


	hsRect baseAttack_Col;
	hsRect MoveAttack_Col;


public:
	bool	isDead;
	//�÷��̾� ��������
	static Player* GetPlayer();
	//������Ʈ
	virtual void Update();
	//������
	virtual void Render();
	//�ʱⰪ ����
	virtual void init();
	//����밪
	virtual void Debug();
	//�÷��̾ ���� ����
	int GetDir();

	
	//ĳ���� �����
	void Jump();					//����
	void MoveAttack(int movement);	//�����ϼ�
	void Move();					//������
	void BaseAttack();				//�⺻����
	void Gravity();					//�߷�
	void ShadowSkill(float ShadowTime);
	void Start();
	void SilderUI();


	//ĳ���� ���º�ȭ
	void Dead();
	
	Player();
	~Player();
};
