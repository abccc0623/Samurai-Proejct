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

	
	//���� ��ǥ�� �迭��ǥ�� �ٲ��ش�
	hsRect GetPosRect();
	int dir = 1;
public:
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

	void Jump();


	Player();
	~Player();
};
