#include "../hsEngine/pch.h"
#include "GameManager.h"
#include "Player.h"



extern hsEngine* Engine;
Player* Player::instance = nullptr;

Player::Player()
{
	isRender	= true;
	isDebug		= true;

	Pos.cx = 525;
	Pos.cy = 575;
}


Player::~Player()
{
	delete instance;

}

hsRect Player::GetPosRect()
{
	//ÁÂÇ¥³ª´©±â

	hsRect temp;

	float	numX = (Pos.cx * 0.01);
	int	whole_X = (int)numX * 100;
	int	minority_X = (int)((numX * 100 - whole_X));


	float	numY = (Pos.cy * 0.01);
	int	whole_Y = (int)numY * 100;
	int	minority_Y = (int)((numY * 100 - whole_Y));


	if (minority_X >= 50)
	{
		minority_X = whole_X + 99;
		whole_X += 50;
	}
	else
	{
		minority_X = whole_X + 50;
	}

	if (minority_Y >= 50)
	{
		minority_Y = whole_Y + 99;
		whole_Y += 50;
	}
	else
	{
		minority_Y = whole_Y + 50;
	}

	temp.LEFT = whole_X;
	temp.TOP = whole_Y;
	temp.RIGHT = minority_X;
	temp.BOTTOM = minority_Y;

	return temp;
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
	Pos.cx += Engine->GetHorizontalKey().cx *5;
	Pos.cy += Engine->GetVirticalKey().cy *5;
	Collider.SetCenter(Pos.cx, Pos.cy, 25, 125, 25, 0);

	GameManager::GetGM()->Collision(this);
}
void Player::Render()
{
	if (Engine->GetHorizontalKey().cx > 0.1f)
	{
		playerAnime = Walking_R;
		dir = 1;
	}
	else if(Engine->GetHorizontalKey().cx < -0.1f)
	{
		playerAnime = Walking_L;
		dir = -1;
	}
	else
	{
		if (dir == 1)
		{
			playerAnime = Idle_R;
		}
		else
		{
			playerAnime = Idle_L;
		}
	}

	
	Engine->AnimeRender(playerAnime, Pos.cx, Pos.cy,0.1f);

	
}
void Player::init()
{
	isCollider = false;

	////¿ÞÂÊ ¼û½¬±â
	Idle_L = Engine->LoadSprite(L"../../4_Resources/GameData/Idle_L.bmp");
	Idle_L->SetOption(0.5f, 0.4f, 0.9f);
	Engine->CreateAnime(Idle_L, 5);
	////¿À¸¥ÂÊ ¼û½¬±â
	Idle_R = Engine->LoadSprite(L"../../4_Resources/GameData/Idle_R.bmp");
	Idle_R->SetOption(0.5f, 0.5f, 0.9f);
	Engine->CreateAnime(Idle_R, 5);
	//¿ÞÂÊ °È±â
	Walking_L = Engine->LoadSprite(L"../../4_Resources/GameData/Walking_L.bmp");
	Walking_L->SetOption(0.5f, 0.5f, 0.9f);
	Engine->CreateAnime(Walking_L, 7);
	//¿À¸¥ÂÊ °È±â
	Walking_R = Engine->LoadSprite(L"../../4_Resources/GameData/Walking_R.bmp");
	Walking_R->SetOption(0.5f, 0.5f, 0.9f);
	Engine->CreateAnime(Walking_R, 7);


	playerAnime = Idle_L;
}
void Player::Debug()
{
	if (isCollider == false) 
	{
		Engine->DrawRectangle(Collider,RGB(0,0,255));
	}
	else
	{
		Engine->DrawRectangle(Collider, RGB(255, 0, 0));
	}

	Engine->DrawRectangle
	(
		Pos.cx - 5,
		Pos.cy - 5,
		Pos.cx + 5,
		Pos.cy + 5,
		RGB(255, 0, 0)
	);

	//Á¤¼öÀÚ¸®°¡ ÇöÀçÀÖ´Â Ä­
	//¼ÒÁÖÁ¡ ÀÚ¸®°¡ ±×Ä­¿¡ ¿ÞÂÊ¿À¸¥ÂÊÆÇº°
	
	 hsRect temp = GetPosRect();


	 Engine->DrawRectangle
	 (
		 temp.LEFT,
		 temp.TOP,
		 temp.RIGHT,
		 temp.BOTTOM,
		 RGB(255, 0, 255)
	 );
	

}



