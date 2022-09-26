#pragma comment(lib,"winmm")
#include <windows.h>
#include <digitalv.h>
#include "sound.h"
#include "../hsEngine/pch.h"
#include "Player.h"
#include "GameManager.h"
#include "Impact.h"
#include "Eclass.h"
#include "General.h"

#define GM GameManager::GetGM()
extern hsEngine* Engine;
General::General(int PosX,int PosY)
{
	Pos.cx		= PosX;
	Pos.cy		= PosY;
	isCollider	= true;
	isRender	= true;
	State		= 0;
	P_dir		= 0;
	M_dir		= 1;
	M_State		= 0;
	Hp			= 3;
	Speed		= 100;
	AttackTime = 0;


	int num = rand() % 2;
	if (num == 0)
	{
		M_dir = 1;
	}
	else
	{
		M_dir = -1;
	}

}

General::General()
{
	Pos.cx		= 0;
	Pos.cy		= 0;
	isCollider	= true;
	isRender	= true;
	State		= 0;
	P_dir		= 0;
	M_dir		= -1;
	Speed		= 100;
}

General::~General()
{

}

void General::Update()
{
	//죽지 않은 상태일때
	if (isDead == false)
	{
		//충돌 박스들을 업데이트
		R_Attack.SetCenter(Pos.cx, Pos.cy, 0, 90, 110, -50);
		L_Attack.SetCenter(Pos.cx, Pos.cy, 110, 90, 0, -50);
		AttackRect.SetCenter(Pos.cx, Pos.cy, 110, 110, 110, 20);
		SearchRect.SetCenter(Pos.cx, Pos.cy, 400, 300, 400, 30);
		Collider.SetCenter(Pos.cx, Pos.cy, 25, 110, 25, 0);


		//죽지 않고 수색범위에 들어왔을떄
		if (Player::GetPlayer()->Collider == SearchRect)
		{

			//방향 변경
			P_dir = Player::GetPlayer()->Pos.cx - Pos.cx;
			if (P_dir > 0)
			{
				M_dir = 1;
			}
			else
			{
				M_dir = -1;
			}

			//공격범위에 들어왔을때
			if (Player::GetPlayer()->Collider == AttackRect)
			{
				M_State = (int)M_STATE::ATTACK;
				Speed = 0;
			}	
		}

		//땅 체크
		GroundCheck();
		//플레이어 공격에 맞았는지 체크
		Damage();
		Pos.cx += Engine->GetDeltaTime() * Speed * M_dir;
	}
	else
	{
		return;
	}
}

void General::Render()
{
	switch (M_State)
	{
	case (int)M_STATE::RUN:
		Run();
		break;
	case (int)M_STATE::ATTACK:
		Attack();
		break;
	case (int)M_STATE::HIT:
		Hit();
		break;
	case (int)M_STATE::DEAD:
		Dead();
		break;
	}
	Engine->AnimeRender(NowAnime, Pos.cx, Pos.cy, 0.1f);
}

void General::Debug()
{
	if (isDead == true) { return; }

	//공겨범위 디버깅
	Engine->DrawRectangle(AttackRect, RGB(255, 255, 0));
	Engine->DrawRectangle(Pos.cx-5,Pos.cy-5, Pos.cx+5, Pos.cy+5, RGB(255,0, 0));
	//수색범위 디버깅
	hsRect dirRect[4];
	dirRect[0].SetCenter(Pos.cx + 50, Pos.cy + 50, 25, 25, 25, 25);
	Engine->DrawRectangle(dirRect[0], RGB(255, 255, 0));
	dirRect[1].SetCenter(Pos.cx - 50, Pos.cy + 50, 25, 25, 25, 25);
	Engine->DrawRectangle(dirRect[1], RGB(255, 255, 0));
	dirRect[2].SetCenter(Pos.cx + 50, Pos.cy - 50, 25, 25, 25, 25);
	Engine->DrawRectangle(dirRect[2], RGB(255, 255, 0));
	dirRect[3].SetCenter(Pos.cx - 50, Pos.cy - 50, 25, 25, 25, 25);
	Engine->DrawRectangle(dirRect[3], RGB(255, 255, 0));


	Engine->DrawRectangle(R_Attack, RGB(255, 0, 0));
	Engine->DrawRectangle(L_Attack, RGB(255, 0, 0));
	

	if (Player::GetPlayer()->Collider == SearchRect)
	{
		Engine->DrawRectangle(SearchRect, RGB(255, 0, 0));
	}
	else
	{
		Engine->DrawRectangle(SearchRect, RGB(0, 0, 255));
	}



	if (ishit == false)
	{
		Engine->DrawRectangle(Collider, RGB(0, 0, 255));
	}
	else
	{
		Engine->DrawRectangle(Collider, RGB(255, 0, 0));
	}
}

void General::init()
{

}

void General::init(hsSprite img[])
{
	for (int i = 0; i < 8; i++)
	{
		Anime[i] = img[i];
	}
	NowAnime = &Anime[(int)MONSTER::RUN_R];
}

void General::Damage()
{
	if (ishit == true)
	{
		int num = rand() %3;
		switch (num)
		{
		case 0:
			GameManager::GetGM()->PlayGameSound((int)SOUND::ENEMY_HIT1);
			break;
		case 1:
			GameManager::GetGM()->PlayGameSound((int)SOUND::ENEMY_HIT2);
			break;
		case 2:
			GameManager::GetGM()->PlayGameSound((int)SOUND::ENEMY_HIT3);
			break;
		}

		Hp--;
		if (P_dir > 0)
		{
			Impact* temp03 = GameManager::GetGM()->CreateImpact(Pos.cx, Pos.cy - 100);
			temp03->ChoiceNumber((int)IMPACT::Blood_01);

			Impact* temp01 = GameManager::GetGM()->CreateImpact(Pos.cx, Pos.cy - 100);
			temp01->ChoiceNumber((int)IMPACT::Blood_R);
		}
		else
		{
			Impact* temp03 = GameManager::GetGM()->CreateImpact(Pos.cx, Pos.cy - 100);
			temp03->ChoiceNumber((int)IMPACT::Blood_01);

			Impact* temp01 = GameManager::GetGM()->CreateImpact(Pos.cx, Pos.cy - 100);
			temp01->ChoiceNumber((int)IMPACT::Blood_L);
		}

		if (Hp <= 0)
		{
			M_State = (int)M_STATE::DEAD;
			isCollider = false;
			isDead = true;
			ishit = false;
			GameManager::GetGM()->MonsterCountDown();
		}
		else
 		{
			if (isAttacking == false)
			{
				M_State = (int)M_STATE::HIT;
			}
			ishit = false;
		}
		
	};
}

void General::Hit()
{
	if (P_dir > 0)
	{
		NowAnime = &Anime[(int)MONSTER::HIT_R];
	}
	else
	{
		NowAnime = &Anime[(int)MONSTER::HIT_L];
	}

	if (Anime[(int)MONSTER::HIT_R].isEndAnime == true)
	{
		Anime[(int)MONSTER::HIT_R].isEndAnime = false;
		Anime[(int)MONSTER::HIT_R].nowCount = 0;
		//ishit = false;
		M_State = (int)M_STATE::RUN;
	}
	else if (Anime[(int)MONSTER::HIT_L].isEndAnime == true)
	{
		Anime[(int)MONSTER::HIT_L].isEndAnime = false;
		Anime[(int)MONSTER::HIT_L].nowCount = 0;
		//ishit = false;
		M_State = (int)M_STATE::RUN;
	}

}

void General::Dead()
{
	if (P_dir > 0)
	{
		NowAnime = &Anime[(int)MONSTER::DEAD_R];
		//isDead = true;
		Collider.SetCenter(Pos.cx, Pos.cy, 0, 0, 0, 0);
	}
	else
	{
		NowAnime =&Anime[(int)MONSTER::DEAD_L];
		//isDead = true;
		Collider.SetCenter(Pos.cx, Pos.cy, 0, 0, 0, 0);
	}
}

void General::Run()
{
	if (M_dir > 0)
	{
		NowAnime = &Anime[(int)MONSTER::RUN_R];
	}
	else
	{
		NowAnime = &Anime[(int)MONSTER::RUN_L];
	}
}

void General::Attack()
{
	isAttacking = true;
	if (M_dir > 0)
	{
		NowAnime = &Anime[(int)MONSTER::ATTACK_R];
	}
	else
	{
		NowAnime = &Anime[(int)MONSTER::ATTACK_L];
	}


	
	if (Anime[(int)MONSTER::ATTACK_R].isEndAnime == true)
	{
		R_At += Engine->GetDeltaTime();
		if (R_At > 1)
		{
			Speed = 100;
			Anime[(int)MONSTER::ATTACK_R].nowCount = 0;
			Anime[(int)MONSTER::ATTACK_R].isEndAnime = false;
			M_State = (int)M_STATE::RUN;
			R_At = 0;
			NowAnime = &Anime[(int)MONSTER::RUN_R];
			isAttacking = false;
		}
	}
	else if (Anime[(int)MONSTER::ATTACK_L].isEndAnime == true)
	{

		L_At += Engine->GetDeltaTime();
		if (L_At > 1)
		{
			Speed = 100;
			Anime[(int)MONSTER::ATTACK_L].nowCount = 0;
			Anime[(int)MONSTER::ATTACK_L].isEndAnime = false;
			M_State = (int)M_STATE::RUN;
			L_At = 0;
			NowAnime = &Anime[(int)MONSTER::RUN_L];
			isAttacking = false;
		}
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
}

void General::GroundCheck()
{
	if (SearchRect == Player::GetPlayer()->Collider)
	{
		if (M_dir > 0)
		{
			//오른쪽에 벽이라면
			//발아래에 타일이없다면
			if (GameManager::GetGM()->MapCheck(Pos.cx + 50, Pos.cy - 50) == false ||
				GameManager::GetGM()->MapCheck(Pos.cx + 50, Pos.cy + 50) == true)
			{
				//M_dir = -1;
				Speed = 0;
			}
			else if(isAttacking == false)
			{
				Speed = 100;
			}
		}
		else if (M_dir < 0)
		{
			//왼쪽에 벽이라면
			//발아래에 타일이 없다면
			if (GameManager::GetGM()->MapCheck(Pos.cx - 50, Pos.cy - 50) == false ||
				GameManager::GetGM()->MapCheck(Pos.cx - 50, Pos.cy + 50) == true)
			{
				Speed = 0;
			}
			else if (isAttacking == false)
			{
				Speed = 100;
			}
		}

	}
	else
	{
		if (M_dir > 0)
		{
			//오른쪽에 벽이라면
			//발아래에 타일이없다면
			if (GameManager::GetGM()->MapCheck(Pos.cx + 50, Pos.cy - 50) == false ||
				GameManager::GetGM()->MapCheck(Pos.cx + 50, Pos.cy + 50) == true)
			{
				M_dir = -1;
			}
		}
		else if (M_dir < 0)
		{
			//왼쪽에 벽이라면
			//발아래에 타일이 없다면
			if (GameManager::GetGM()->MapCheck(Pos.cx - 50, Pos.cy - 50) == false ||
				GameManager::GetGM()->MapCheck(Pos.cx - 50, Pos.cy + 50) == true)
			{
				M_dir = 1;
			}
		}
	}
	
	
}



