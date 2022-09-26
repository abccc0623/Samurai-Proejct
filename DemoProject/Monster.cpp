#pragma comment(lib,"winmm")
#include <windows.h>
#include <digitalv.h>
#include "sound.h"

#include "../hsEngine/pch.h"
#include "Player.h"
#include "GameManager.h"
#include "Impact.h"
#include "Eclass.h"
#include "Monster.h"


extern hsEngine* Engine;
Monster::Monster(int PosX,int PosY)
{
	M_State = 0;
	dir		= 1;
	Pos.cx = PosX;
	Pos.cy = PosY;

	isCollider  = true;
	isDead		= false;
	Speed		= 100;
	Hp			= 3;
}

Monster::~Monster()
{
}

void Monster::Update()
{
	//충돌범위 셋팅
	Collider.SetCenter(Pos.cx, Pos.cy, 25, 100, 25, 0);
	//플레이어 체크
	SearchRect.SetCenter(Pos.cx, Pos.cy, 700, 500, 700, 30);
	R_Attack.SetCenter(Pos.cx, Pos.cy, 0, 100, 80, 0);
	L_Attack.SetCenter(Pos.cx, Pos.cy, 80, 100, 0, 0);

	//대기 상태였다가 공격모드로
	if (ishit == false)
	{

		dir = Player::GetPlayer()->Pos.cx - Pos.cx;
	}
	if (M_State == 0 && SearchRect == Player::GetPlayer()->Collider)
	{
		M_State = 1;
	}

	if (dir > 0)
	{
		if (GameManager::GetGM()->MapCheck(Pos.cx + 25, Pos.cy + 50))
		{
			Speed = 0;
		}
		else
		{
			Speed = 100;
		}
	}
	else
	{
		if (GameManager::GetGM()->MapCheck(Pos.cx - 25, Pos.cy + 50))
		{
			Speed = 0;
		}
		else
		{
			Speed = 100;
		}
	}

	Damage();
	AttackRect.SetCenter(Pos.cx, Pos.cy, 80, 110, 80, 20);
}

void Monster::Render()
{
	switch (M_State)
	{
	case Idle: //대기 상태
		NowAnime = &Anime[(int)MONSTER::IDLE_R];
		break;

	case Fighting: //공격상태
		if (dir > 0)
		{
			NowAnime = &Anime[(int)MONSTER::ATTACK_READY_R];}
		else
		{
			NowAnime = &Anime[(int)MONSTER::ATTACK_READY_L];
		}

		if (Anime[(int)MONSTER::ATTACK_READY_R].isEndAnime == true)
		{
			M_State = 2;
		}
		else if (Anime[(int)MONSTER::ATTACK_READY_L].isEndAnime == true)
		{
			M_State = 2;
		}
		break;

	case Search: //추격상태
		//플레이어를 쫒아가다가 충돌범위에들어온다면
		if (dir >= 0)
		{
			NowAnime = &Anime[(int)MONSTER::RUN_R];
			Pos.cx += 1 * Speed * Engine->GetDeltaTime();
		}
		else
		{
			NowAnime = &Anime[(int)MONSTER::RUN_L];
			Pos.cx += -1 * Speed * Engine->GetDeltaTime();
		}
		//충돌범위에 들어온다면
		if (Player::GetPlayer()->Collider == AttackRect)
		{
			M_State = 3;
		}
		break;

	case Attack: //공격상태
		if (dir > 0)
		{
			NowAnime = &Anime[(int)MONSTER::ATTACK_R];
		}
		else
		{
			NowAnime = &Anime[(int)MONSTER::ATTACK_L];
		}

		if (Anime[(int)MONSTER::ATTACK_R].isEndAnime == true)
		{
			Anime[(int)MONSTER::ATTACK_R].isEndAnime = false;
			Anime[(int)MONSTER::ATTACK_R].nowCount = 0;
			M_State = 2;
		}
		else if (Anime[(int)MONSTER::ATTACK_L].isEndAnime == true)
		{
			Anime[(int)MONSTER::ATTACK_L].isEndAnime = false;
			Anime[(int)MONSTER::ATTACK_L].nowCount = 0;
			M_State = 2;
		}



		if (Anime[(int)MONSTER::ATTACK_R].GetFrame(6) &&
			Player::GetPlayer()->Collider == R_Attack)
		{

			Player::GetPlayer()->Dead();
		}

		if (Anime[(int)MONSTER::ATTACK_L].GetFrame(6) &&
			Player::GetPlayer()->Collider == L_Attack)
		{

			Player::GetPlayer()->Dead();
		}


		break;
	case Hit:
		if (isDead == false)
		{
			isCollider = false;
			if (dir < 0)
			{
				NowAnime = &Anime[(int)MONSTER::DEAD_L];	
			}
			else
			{
				NowAnime = &Anime[(int)MONSTER::DEAD_R];
			}
			ishit = false;
			
		}

		if (Anime[(int)MONSTER::DEAD_R].isEndAnime == true)
		{
			ishit = false;
			isDead = true;
			
		}
		else if(Anime[(int)MONSTER::DEAD_L].isEndAnime == true)
		{
			Collider.SetCenter(Pos.cx, Pos.cy, 0, 0, 0, 0);
			ishit = false;
			isDead = true;
		}
		
		break;
	}
	
	//공격상태일떄
	Engine->AnimeRender(NowAnime, Pos.cx, Pos.cy,0.07f);
}
void Monster::Debug()
{
	if (isDead == true) { return; }

	if (ishit == false)
	{
		Engine->DrawRectangle(Collider, RGB(0, 0, 255));
	}
	else
	{
		Engine->DrawRectangle(Collider, RGB(255, 0,0));
	}

	//공겨범위 디버깅
	Engine->DrawRectangle(AttackRect, RGB(255, 255, 0));


	//수색범위 디버깅
	if (Player::GetPlayer()->Collider == SearchRect)
	{
		
		Engine->DrawRectangle(SearchRect, RGB(255, 0, 0));
	}
	else
	{
		Engine->DrawRectangle(SearchRect, RGB(0, 0, 255));
	}

	Engine->DrawRectangle(R_Attack, RGB(255, 0, 0));
	Engine->DrawRectangle(L_Attack, RGB(255, 0, 0));
	
	//바닥체크 디버깅

	hsRect Ground;
	//왼쪽아래 땅체크
	Ground.SetCenter(Pos.cx - 50, Pos.cy + 50, 25, 25, 25, 25);
	Engine->DrawRectangle(Ground, RGB(255, 255, 0));

	//오른쪽 아래 땅체크
	Ground.SetCenter(Pos.cx + 50, Pos.cy + 50, 25, 25, 25, 25);
	Engine->DrawRectangle(Ground, RGB(255, 255, 0));
}

void Monster::init()
{

}

void Monster::init(hsSprite img[])
{
	for(int i = 0; i < 12; i++)
	{
		Anime[i] = img[i];
	}
}

void Monster::Damage()
{
	if (ishit == true)
	{
		GameManager::GetGM()->MonsterCountDown();
		if (dir > 0)
		{
			Impact* temp03 = GameManager::GetGM()->CreateImpact(Pos.cx, Pos.cy - 100);
			temp03->ChoiceNumber((int)IMPACT::Blood_01);

			Impact* temp01 = GameManager::GetGM()->CreateImpact(Pos.cx, Pos.cy - 100);
			temp01->ChoiceNumber((int)IMPACT::Blood_R);

			GameManager::GetGM()->PlayGameSound((int)SOUND::ENEMY_HIT1);
		}
		else
		{
			Impact* temp03 = GameManager::GetGM()->CreateImpact(Pos.cx, Pos.cy - 100);
			temp03->ChoiceNumber((int)IMPACT::Blood_01);

			Impact* temp01 = GameManager::GetGM()->CreateImpact(Pos.cx, Pos.cy - 100);
			temp01->ChoiceNumber((int)IMPACT::Blood_L);

			GameManager::GetGM()->PlayGameSound((int)SOUND::ENEMY_HIT1);
		}
		

		M_State = 4;
	}
}