#pragma comment(lib,"winmm")
#include <windows.h>
#include <digitalv.h>
#include "sound.h"
#include "../hsEngine/pch.h"
#include "GameManager.h"
#include "Eclass.h"
#include "Impact.h"
#include "Player.h"

extern hsEngine* Engine;
Player* Player::instance = nullptr;



Player::Player()
{
	AP			= 100;
	dir			= 0;
	isMove		= false;
	jumping		= false;
	isGround	= false;
	isAttack	= false;
	isBaseAttack = false;
	isMoveAttack = false;


	isRender	= true;
	isDebug		= true;
	isShadow	= false;
	APUP_Speed = 30;
	//�����Ӻκ�
	Pos.cx = 400;
	Pos.cy = 1200;
	Speed	= 300;

	DownSpeed = 1;
	//���� �κ�
	jumpCount = 0;
	jumping = false;
	jumpSpeed = 1200;

	for (int i = 0; i < 12; i++)
	{
		Anime[i] = nullptr;
	}

	//��������Ʈ
	playerAnime = nullptr;
	
	imgAlpha = 1;
	isCollider = true;
	Speed = 200;

}
Player::~Player()
{

	//��� �̹��� ������ ������ ����
	delete instance;
	for (int i = 0; i < 12; i++)
	{
		delete Anime[i];
	}
}


void Player::Dead()
{
	if (isDead == false && isCollider == true)
	{
		if (dir > 0)
		{
			playerAnime = Anime[(int)PLAYER::DEAD_R];
			GameManager::GetGM()->PlayGameSound((int)SOUND::PLAYER_HIT);
			Impact* temp03 = GameManager::GetGM()->CreateImpact(Pos.cx, Pos.cy - 100);
			temp03->ChoiceNumber((int)IMPACT::Blood_01);
			
			Impact* temp01 = GameManager::GetGM()->CreateImpact(Pos.cx, Pos.cy - 100);
			temp01->ChoiceNumber((int)IMPACT::Blood_R);
		}
		else
		{
			playerAnime = Anime[(int)PLAYER::DEAD_L];
			GameManager::GetGM()->PlayGameSound((int)SOUND::PLAYER_HIT);
			Impact* temp03 = GameManager::GetGM()->CreateImpact(Pos.cx, Pos.cy - 100);
			temp03->ChoiceNumber((int)IMPACT::Blood_01);
			
			Impact* temp01 = GameManager::GetGM()->CreateImpact(Pos.cx, Pos.cy - 100);
			temp01->ChoiceNumber((int)IMPACT::Blood_L);
		}
		isDead = true;
	}


}

Player* Player::GetPlayer()
{
	if (instance == nullptr)
	{
		instance = new Player();
	}
	return instance;
}

void Player::Update()
{
	static bool isApON = true;
	if (Engine->key.KeyDown(VK_F1))
	{
		if (isApON == true)
		{
			APUP_Speed = 300;
			isApON = false;
		}
		else
		{
			APUP_Speed = 30;
			isApON = true;
		}
	
	}
	




	if (Anime[(int)PLAYER::DEAD_R]->isEndAnime == true)
	{
		playerAnime = Anime[(int)PLAYER::Idle_R];
		Anime[(int)PLAYER::DEAD_R]->nowCount = 0;
		Anime[(int)PLAYER::DEAD_R]->isEndAnime = false;
		Start();
		GameManager::GetGM()->RetrunStage();
		isDead = false;
	}
	else if (Anime[(int)PLAYER::DEAD_L]->isEndAnime == true)
	{
		playerAnime = Anime[(int)PLAYER::Idle_L];
		Anime[(int)PLAYER::DEAD_L]->nowCount = 0;
		Anime[(int)PLAYER::DEAD_L]->isEndAnime = false;
		Start();
		GameManager::GetGM()->RetrunStage();
		isDead = false;
	}


	if (isDead == true) { return; }
	
	
	//����
	BaseAttack();
	//������
	Move();
	//����
	Jump();
	//��ų
	MoveAttack(500);
	//�߷�
	Gravity();

	ShadowSkill(6);



	SilderUI();
	Collider.SetCenter(Pos.cx, Pos.cy, 25, 100, 25, 30);
	//GameManager::GetGM()->Collision(this);
	
}

void Player::Render()
{
	if (isAttack == false && jumping == false && isDead ==false)
	{
		if (Engine->GetHorizontalKey() == 1)
		{
			playerAnime = Anime[(int)PLAYER::RUN_R];
		}
		else if (Engine->GetHorizontalKey() == -1)
		{
			playerAnime = Anime[(int)PLAYER::RUN_L];
		}
		else
		{
			if (dir == 1)
			{
				playerAnime = Anime[(int)PLAYER::Idle_R];
			}
	
			if (dir == -1)
			{
				playerAnime = Anime[(int)PLAYER::Idle_L];
			}
		}
	}
	
	Engine->AnimeRender(playerAnime, Pos.cx, Pos.cy + 25, 0.07f, imgAlpha);
}

void Player::init()
{
	////���� ������
	Anime[(int)PLAYER::Idle_L] = Engine->LoadSprite("../GameData/player/Idle_L.bmp");
	Anime[(int)PLAYER::Idle_L]->SetOption(0.5f, 0.4f, 0.7f);
	Engine->CreateAnime(Anime[(int)PLAYER::Idle_L], 21);
	////������ ������
	Anime[(int)PLAYER::Idle_R] = Engine->LoadSprite("../GameData/player/Idle_R.bmp");
	Anime[(int)PLAYER::Idle_R]->SetOption(0.5f, 0.5f, 0.7f);
	Engine->CreateAnime(Anime[(int)PLAYER::Idle_R], 21);
	//���� �ȱ�
	Anime[(int)PLAYER::RUN_L] = Engine->LoadSprite("../GameData/player/Walking_L.bmp");
	Anime[(int)PLAYER::RUN_L]->SetOption(0.5f, 0.5f, 0.7f);
	Engine->CreateAnime(Anime[(int)PLAYER::RUN_L], 3);
	//������ �ȱ�
	Anime[(int)PLAYER::RUN_R] = Engine->LoadSprite("../GameData/player/Walking_R.bmp");
	Anime[(int)PLAYER::RUN_R]->SetOption(0.5f, 0.5f, 0.7f);
	Engine->CreateAnime(Anime[(int)PLAYER::RUN_R], 3);

	//MoveAttack_R
	Anime[(int)PLAYER::MOVE_ATTACK_R] = Engine->LoadSprite("../GameData/player/MoveAttack_R.bmp");
	Anime[(int)PLAYER::MOVE_ATTACK_R]->SetOption(0.5f, 0.8f, 0.7f);
	Engine->CreateAnime(Anime[(int)PLAYER::MOVE_ATTACK_R], 7,false);

	//MoveAttack_L
	Anime[(int)PLAYER::MOVE_ATTACK_L] = Engine->LoadSprite("../GameData/player/MoveAttack_L.bmp");
	Anime[(int)PLAYER::MOVE_ATTACK_L]->SetOption(0.5f, 0.1f, 0.7f);
	Engine->CreateAnime(Anime[(int)PLAYER::MOVE_ATTACK_L], 7,false);


	//������ �⺻����
	Anime[(int)PLAYER::ATTACK_R] = Engine->LoadSprite("../GameData/player/Attack_R.bmp");
	Anime[(int)PLAYER::ATTACK_R]->SetOption(0.65f, 0.575f, 0.65f);
	Engine->CreateAnime(Anime[(int)PLAYER::ATTACK_R], 8, false);
	//���� �⺻����
	Anime[(int)PLAYER::ATTACK_L] = Engine->LoadSprite("../GameData/player/Attack_L.bmp");
	Anime[(int)PLAYER::ATTACK_L]->SetOption(0.65f, 0.4f, 0.65f);
	Engine->CreateAnime(Anime[(int)PLAYER::ATTACK_L], 8, false);


	//���� �ٱ� ������
	Anime[(int)PLAYER::JUMP_UP_R] = Engine->LoadSprite("../GameData/player/jump_Up_R.bmp");
	Anime[(int)PLAYER::JUMP_UP_R]->SetOption(0.5f, 0.7f, 1);
	Engine->CreateAnime(Anime[(int)PLAYER::JUMP_UP_R], 20);
	
	//���� �ٱ� ����
	Anime[(int)PLAYER::JUMP_UP_L] = Engine->LoadSprite("../GameData/player/jump_Up_L.bmp");
	Anime[(int)PLAYER::JUMP_UP_L]->SetOption(0.5f, 0.3f, 1);
	Engine->CreateAnime(Anime[(int)PLAYER::JUMP_UP_L], 20);

	//���� ���� ����
	Anime[(int)PLAYER::JUMP_DOWN_L] = Engine->LoadSprite("../GameData/player/Jump_Down_L.bmp");
	Anime[(int)PLAYER::JUMP_DOWN_L]->SetOption(0.5f, 0.3f, 1);
	Engine->CreateAnime(Anime[(int)PLAYER::JUMP_DOWN_L], 3);

	//���� ���� ������
	Anime[(int)PLAYER::JUMP_DOWN_R] = Engine->LoadSprite("../GameData/player/Jump_Down_R.bmp");
	Anime[(int)PLAYER::JUMP_DOWN_R]->SetOption(0.5f, 0.7f, 0.8f);
	Engine->CreateAnime(Anime[(int)PLAYER::JUMP_DOWN_R], 3);

	Anime[(int)PLAYER::DEAD_L] = Engine->LoadSprite("../GameData/player/Dead_L.bmp");
	Anime[(int)PLAYER::DEAD_L]->SetOption(0.5f, 0.6f, 0.7f);
	Engine->CreateAnime(Anime[(int)PLAYER::DEAD_L],16, false);

	Anime[(int)PLAYER::DEAD_R] = Engine->LoadSprite("../GameData/player/Dead_R.bmp");
	Anime[(int)PLAYER::DEAD_R]->SetOption(0.5f, 0.7f, 0.7f);
	Engine->CreateAnime(Anime[(int)PLAYER::DEAD_R], 16, false);


	//���� �⺻����
	playerAnime = Anime[(int)PLAYER::Idle_L];
}

void Player::Debug()
{
	
	//ĳ������ �浹������ �Ķ�������
	//�浿�ߴٸ� ����������
	if (isCollider == false) 
	{
		Engine->DrawRectangle(Collider,RGB(0,0,255));
	}
	else
	{
		Engine->DrawRectangle(Collider, RGB(255, 0, 0));
	}

	//ĳ���� ��ǥ�� ������ ����
	Engine->DrawRectangle
	(
		Pos.cx -5,
		Pos.cy -5,
		Pos.cx +5,
		Pos.cy +5,
		RGB(255, 0, 0)
	);


	//ĳ���Ͱ� �����ִ� �迭�� ĭ�� ���������
	int X = Pos.cx / 50;
	int Y = Pos.cy / 50;
	Engine->DrawRectangle
	(
		X*50,
		Y*50,
		(X+1) * 50,
		(Y+1)* 50,
		RGB(255, 255, 0)
	);

	if (isAttack == true)
	{
		if (dir == 1)
		{
			if (isMoveAttack)
			{
				//�̵�����
				Engine->DrawRectangle
				(
					Pos.cx - 500,
					Pos.cy - 100,
					Pos.cx,
					Pos.cy + 20,
					RGB(0, 255, 0)
				);
			}
			
			if (isBaseAttack)
			{
				hsRect temp;
				temp.SetCenter(Pos.cx, Pos.cy, 0, 100, 85, 55);
				//�⺻����
				Engine->DrawRectangle
				(
					temp,
					RGB(0, 255, 0)
				);
			}
			
			
			
		}
		else
		{
			if (isMoveAttack)
			{
				Engine->DrawRectangle
				(
					Pos.cx + 500,
					Pos.cy - 100,
					Pos.cx,
					Pos.cy + 20,
					RGB(0, 255, 0)
				);
			}
			if (isBaseAttack)
			{
				hsRect temp;
				temp.SetCenter(Pos.cx, Pos.cy, 85, 100, 0, 55);
				Engine->DrawRectangle
				(
					temp,
					RGB(0, 255, 0)
				);
			}
		}
	}
	


}

int Player::GetDir()
{
	int dir = 0;
	if (0 < Engine->GetHorizontalKey())
	{
		dir = 1;
	}
	else if (0 > Engine->GetHorizontalKey())
	{
		dir = - 1;
	}
	else
	{
		dir = 0;
	}
	return dir;
}
//��ų �Լ���
void Player::Jump()
{
	//�����߿��� ������ �Ҽ� ����
	if(isAttack == true)
	{
		return;
	}
	static bool current = false;
	static bool prev	= false;
	
	if (key.KeyDown(VK_SPACE)) 
	{
		if (jumpCount < 2)
		{
			jumpSpeed = 1200;
			jumping = true;
		}
	}

	if (key.KeyUP(VK_SPACE))
	{
		jumpCount++;
	}
	

	if (jumping == true)
	{
		if (GameManager::GetGM()->MapCheck(Pos.cx, Pos.cy-50) == false)
		{
			jumping = false;
			jumpSpeed = 100;
			DownSpeed += Engine->GetDeltaTime() * 100;
			Pos.cy += (600 + DownSpeed) * Engine->GetDeltaTime();

		}
		else
		{
			Pos.cy -= jumpSpeed * Engine->GetDeltaTime();
			jumpSpeed -= 1500 * Engine->GetDeltaTime();
		}

 	    


		if (jumpSpeed > 200) 
		{
			if (dir > 0)
			{
				playerAnime = Anime[(int)PLAYER::JUMP_UP_R];
			}
			else if(dir < 0)
			{
				playerAnime = Anime[(int)PLAYER::JUMP_UP_L];
			}
		}
		else
		{
			if (dir > 0)
			{
				playerAnime = Anime[(int)PLAYER::JUMP_DOWN_R];
			}
			else if(dir < 0)
			{
				playerAnime = Anime[(int)PLAYER::JUMP_DOWN_L];
			}
			
		}

	}
}

void Player::MoveAttack(int movement)
{	
	hsRect rect;
	//Ű�ٿ�
	if (key.KeyDown('Z') == true && AP >=50)
	{
		isAttack = true;
		//ĳ���� ���� ���ϰ�
		if (Engine->GetHorizontalKey() > 0) 
		{
			
			//��üũ�ؼ� �ڽ��� ���ٸ�
			if (GameManager::GetGM()->MapCheck(Pos.cx, Pos.cy + 500) &&
				GameManager::GetGM()->MapCheck(Pos.cx, Pos.cy + 400) &&
				GameManager::GetGM()->MapCheck(Pos.cx, Pos.cy + 300) &&
				GameManager::GetGM()->MapCheck(Pos.cx, Pos.cy + 200) &&
				GameManager::GetGM()->MapCheck(Pos.cx, Pos.cy + 100)
				)
			{	
				GameManager::GetGM()->PlayGameSound((int)SOUND::PLAYER_SKILL);
				AP -= 50;
				isMoveAttack = true;
				jumpSpeed = -1;
				
				///���� �浹����
				hsRect temp;
				temp.SetCenter(Pos.cx, Pos.cy, 0,100, 500, 20);
				GameManager::GetGM()->Collision(temp);
				///
				
				playerAnime = Anime[(int)PLAYER::MOVE_ATTACK_R];
				Pos.cx += movement;
			}
			else //�ڽ��� �ִٸ��������
			{
				isMoveAttack = false;
				isAttack = false;
				playerAnime = Anime[(int)PLAYER::Idle_R];
			}
		}
		else if(Engine->GetHorizontalKey() < 0)
		{
			if (GameManager::GetGM()->MapCheck(Pos.cx - 500, Pos.cy)&&
				GameManager::GetGM()->MapCheck(Pos.cx - 400, Pos.cy)&&
				GameManager::GetGM()->MapCheck(Pos.cx - 300, Pos.cy)&&
				GameManager::GetGM()->MapCheck(Pos.cx - 200, Pos.cy)&&
				GameManager::GetGM()->MapCheck(Pos.cx - 100, Pos.cy))
			{
				GameManager::GetGM()->PlayGameSound((int)SOUND::PLAYER_SKILL);
				AP -= 50;
				isMoveAttack = true;
				playerAnime = playerAnime = Anime[(int)PLAYER::MOVE_ATTACK_L];

				///���� �浹����
				hsRect temp;
				temp.SetCenter(Pos.cx, Pos.cy, 500, 100, 0, 20);
				GameManager::GetGM()->Collision(temp);
				///

				Pos.cx -= movement;
			}
			else
			{
				isMoveAttack = false;
				isAttack = false;
				playerAnime = Anime[(int)PLAYER::Idle_L];
			}
		}
		else
		{
			isMoveAttack = false;
			isAttack = false;
			playerAnime = Anime[(int)PLAYER::Idle_R];
		}
	}

	if (Anime[(int)PLAYER::MOVE_ATTACK_R]->isEndAnime == true )
	{
		isMoveAttack	= false;
		isAttack		= false;
		Anime[(int)PLAYER::MOVE_ATTACK_R]->isEndAnime = false;
		Anime[(int)PLAYER::MOVE_ATTACK_R]->nowCount = 0;
		playerAnime = Anime[(int)PLAYER::Idle_R];
	}
	else if (Anime[(int)PLAYER::MOVE_ATTACK_L]->isEndAnime == true)
	{
		isMoveAttack	= false;
		isAttack		= false;
		Anime[(int)PLAYER::MOVE_ATTACK_L]->isEndAnime = false;
		Anime[(int)PLAYER::MOVE_ATTACK_L]->nowCount = 0;
		playerAnime = Anime[(int)PLAYER::Idle_L];
	}

}

void Player::Move()
{
	if (isAttack == true) { return; }
	

	//���� ������ ������ �����̰� ���ʿ� Ÿ���� �ִٸ�
	if (GameManager::GetGM()->MapCheck(Pos.cx -25, Pos.cy) == false && Engine->GetHorizontalKey() == -1)
	{
		Speed = 0;
	}
	// ������ ������ �������̰� ���ʿ� Ÿ���� �ִٸ�
	else if (GameManager::GetGM()->MapCheck(Pos.cx + 25, Pos.cy) == false && Engine->GetHorizontalKey() == 1)
	{
		Speed = 0;
	}
	else
	{
		Speed = 400;
		if (Engine->GetHorizontalKey() > 0)
		{	
			dir = 1;
		}
		else if(Engine->GetHorizontalKey() < 0)
		{
			dir = -1;
		}
		
		Pos.cx += Engine->GetDeltaTime() * Speed * Engine->GetHorizontalKey();
		isMove = true;
	}
}

void Player::BaseAttack()
{
	//���������϶��� ���ݾ���
	if (jumping == true && isBaseAttack == true)
	 {
		return;
	}
	//������������ �ѹ��� �����
	if (key.KeyDown('X') == true)
	{
		GameManager::GetGM()->PlayGameSound((int)SOUND::PLAYER_ATTACK);
		isBaseAttack = true;
		isAttack = true;
		hsRect temp;
		if (dir == 1 ) 
		{
	
			playerAnime = Anime[(int)PLAYER::ATTACK_R];;
			//�浹 ���� ���ϱ�
			temp.SetCenter(Pos.cx, Pos.cy, 0, 100, 85, 55);
		}
		else if(dir == -1)
		{
			//�浹 ���� ���ϱ�
			playerAnime = Anime[(int)PLAYER::ATTACK_L];
			temp.SetCenter(Pos.cx, Pos.cy, 85, 100, 0, 55);
		}	
		GameManager::GetGM()->Collision(temp);
	}

	//������ �����ٸ� (��� �˻�)
	if (Anime[(int)PLAYER::ATTACK_R]->isEndAnime == true)
	{
		isAttack		= false;
		isBaseAttack	= false;
		Anime[(int)PLAYER::ATTACK_R]->isEndAnime = false;
		Anime[(int)PLAYER::ATTACK_R]->nowCount = 0;
		playerAnime = Anime[(int)PLAYER::Idle_R];
	}
	else if (Anime[(int)PLAYER::ATTACK_L]->isEndAnime == true)
	{
		isAttack		= false;
		isBaseAttack	= false;
		Anime[(int)PLAYER::ATTACK_L]->isEndAnime = false;
		Anime[(int)PLAYER::ATTACK_L]->nowCount = 0;
		playerAnime = Anime[(int)PLAYER::Idle_L];
	}
}

void Player::Gravity()
{
	
	hsRect rt;
	rt.SetCenter(Pos.cx, Pos.cy, 25, 25, 25,25);
	bool isTile = GameManager::GetGM()->MapCheck(Pos.cx, Pos.cy+50);
	bool ground = GameManager::GetGM()->MapCheck(Pos.cx, Pos.cy);


	int POS_Y = (Pos.cy+50);

	//�Ʒ��ʿ� Ÿ���� ���ٸ� 
	int Y = (Pos.cy) / 50;
	
	if (isTile == false )
	{
		if (Pos.cy > (Y * 50))
		{
			Pos.cy = (Y * 50)+1;	  
		}
		jumping = false;
		DownSpeed = 1;
		jumpSpeed = 1000;
		jumpCount = 0;
	}
	else
	{
		DownSpeed += Engine->GetDeltaTime() * 200;
		Pos.cy += (450 + DownSpeed) * Engine->GetDeltaTime();
	}
}

void Player::ShadowSkill(float ShadowTime)
{
	static bool isOn = false;
	if (key.KeyDown('C') == true)
	{
		GameManager::GetGM()->PlayGameSound((int)SOUND::PLAYER_SHADOW);
		if (isOn == false)
		{
			isOn		= true;
			imgAlpha	= 0.5f;
			isShadow	= false;
			isCollider	= false;
		}
		else
		{
			imgAlpha	= 1;
			isShadow	= true;
			isCollider	= true;
			isOn		= false;
		}
	}

	if (isOn == true)
	{
		if (AP >= 0)
		{
			AP -= Engine->GetDeltaTime() *30;
		}
		else
		{
			isOn = false;
			isShadow	= true;
			isCollider	= true;
			imgAlpha	= 1;
		}
	
	}
	else
	{
		if (AP <= 100)
		{
			AP += Engine->GetDeltaTime() * APUP_Speed;
		}
	}
	
}

void Player::Start()
{
	dir = 1;
	playerAnime = Anime[(int)PLAYER::Idle_R];
	AP = 100;
	isDead = false;
	Speed = 300;
	isAttack = false;
	isBaseAttack = false;
}

void Player::SilderUI()
{
	//�� �����̴�
	Engine->DrawRectangle
	(
		Pos.cx - 50,
		Pos.cy + 70,
		Pos.cx + 50,
		Pos.cy + 75,
		RGB(0, 0, 0)
	);

	//ap �ս����̴�
	Engine->DrawRectangle
	(
		Pos.cx - 50,
		Pos.cy + 70,
		Pos.cx - 50 + AP,
		Pos.cy + 75,
		RGB(255, 255, 255)
	);

	Engine->DrawRectangle
	(
		Pos.cx,
		Pos.cy + 60,
		Pos.cx,
		Pos.cy + 80,
		RGB(0, 0, 0)
	);
}


