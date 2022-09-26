#pragma once


class Player : public GameObject
{
private:
	static Player* instance;
	
	hsSprite*	Anime[14];
	hsSprite*	playerAnime;
	

	int		APUP_Speed;
	float	AP;				//캐릭터 스킬 AP;
	int		Speed;			//캐릭터 스피드				
	int		DownSpeed;		//내려가는속도
	int		dir;			//캐릭터가 보는방향
	int		jumpCount;		//현재 점프횟수
	int		jumpSpeed;		//점프하는속도

	
	float	imgAlpha;		//플레이어가 가지고있는 이미지 알파값		

	
	bool	isShadow;
	bool	isMove;			//이동중인지
	bool	jumping;		//현제 점프중인지
	bool	isGround;		//현재 땅인지
	bool	isAttack;
	bool	isBaseAttack;
	bool	isMoveAttack;
	hsKey key;


	hsRect baseAttack_Col;
	hsRect MoveAttack_Col;


public:
	bool	isDead;
	//플레이어 가져오기
	static Player* GetPlayer();
	//업데이트
	virtual void Update();
	//렌더링
	virtual void Render();
	//초기값 지정
	virtual void init();
	//디버깅값
	virtual void Debug();
	//플레이어가 보는 방향
	int GetDir();

	
	//캐릭터 기술들
	void Jump();					//점프
	void MoveAttack(int movement);	//벽력일섬
	void Move();					//움직임
	void BaseAttack();				//기본공격
	void Gravity();					//중력
	void ShadowSkill(float ShadowTime);
	void Start();
	void SilderUI();


	//캐릭터 상태변화
	void Dead();
	
	Player();
	~Player();
};
