#pragma once
class Player : public GameObject
{
private:
	static Player* instance;
	
	hsSprite* playerAnime;

	hsSprite*	Idle_L;
	hsSprite*	Idle_R;
	hsSprite*	Walking_R;
	hsSprite*	Walking_L;

	hsSprite	Dead_img;
	hsSprite	Jump_img;
	hsSprite	Attack01;
	hsSprite	Attack02;

	
	//나의 좌표를 배열좌표로 바꿔준다
	hsRect GetPosRect();
	int dir = 1;
public:
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

	void Jump();


	Player();
	~Player();
};
