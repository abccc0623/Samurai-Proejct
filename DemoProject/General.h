#pragma once
class General :public GameObject
{
	//애니메이션 구조체들
	hsSprite* NowAnime;
	hsSprite Anime[8];
	int State;
	//수색범위
	hsRect SearchRect;
	//오른쪽 공격범위
	hsRect AttackRect;

	hsRect R_Attack;
	hsRect L_Attack;

	float AttackTime;
	float R_At;
	float L_At;

	bool isAttacking;
	//나의방향
	//플레이어의방향
	int P_dir;
	//스피드
	int Speed;
	//상태
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

