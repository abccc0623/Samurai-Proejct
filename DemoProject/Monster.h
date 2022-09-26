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
	//애니메이션 구조체들
	hsSprite* NowAnime;
	hsSprite Anime[12];

	//수색범위
	hsRect SearchRect;
	//오른쪽 공격범위
	hsRect AttackRect;


	hsRect R_Attack;
	hsRect L_Attack;

	
public:

	int Hp;
	int Speed;
	
	//몬스터 상태
	int M_State;
	//몬스터가 보는 방향
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

