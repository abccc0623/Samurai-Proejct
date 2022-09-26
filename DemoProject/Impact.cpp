
#include "../hsEngine/pch.h"

#include "Eclass.h"
#include "Impact.h"

extern hsEngine* Engine;
void Impact::ChoiceNumber(int num)
{
	switch (num)
	{
	case (int)IMPACT::Blood_R:
		Main = &imgList[(int)IMPACT::Blood_R];
		break;
	case (int)IMPACT::Blood_L:
		Main = &imgList[(int)IMPACT::Blood_L];
		break;
	case (int)IMPACT::HIT_01:
		Main = &imgList[(int)IMPACT::HIT_01];
		break;
	case (int)IMPACT::HIT_02:
		Main = &imgList[(int)IMPACT::HIT_02];
		break;
	case (int)IMPACT::HIT_03:
		Main = &imgList[(int)IMPACT::HIT_03];
		break;
	case (int)IMPACT::DUST_L:
		Main = &imgList[(int)IMPACT::DUST_L];
		break;
	case (int)IMPACT::DUST_R:
		Main = &imgList[(int)IMPACT::DUST_R];
		break;
	case (int)IMPACT::Lightning01:
		Main = &imgList[(int)IMPACT::Lightning01];
		break;
	case (int)IMPACT::Blood_01:
	case (int)IMPACT::Blood_02:
	case (int)IMPACT::Blood_03:
		int num =rand()% 3;
		switch (num)
		{
		case 0:
		Main = &imgList[(int)IMPACT::Blood_01];
			break;
		case 1:
		Main = &imgList[(int)IMPACT::Blood_02];
			break;
		case 2:
		Main = &imgList[(int)IMPACT::Blood_03];
			break;
		}
		break;


	//case (int)IMPACT::Lightning02:
	//	Main = &imgList[(int)IMPACT::Lightning02];
	//	break;
	//case (int)IMPACT::Lightning03:
	//	Main = &imgList[(int)IMPACT::Lightning03];
	//case (int)IMPACT::Lightning04:
	//	Main = &imgList[(int)IMPACT::Lightning04];
	//	break;
	
	}
}
Impact::Impact( int PosX,int PosY)
{
	isRender	= true;
	Pos.cx		= PosX;
	Pos.cy		= PosY;
	Main		= nullptr;
}

Impact::~Impact()
{
	
}


void Impact::Update()
{
	
}

void Impact::Render()
{
	Engine->AnimeRender(Main, Pos.cx, Pos.cy,0.1f);

	if (Main->isEndAnime == true)
	{
		isRender = false;
	}
}

void Impact::init()
{
}

void Impact::Debug()
{
	
}

void Impact::init(hsSprite img[])
{
	for (int i = 0; i < 12; i++)
	{
		imgList[i] = img[i];
	}
	Main = &imgList[0];
}

