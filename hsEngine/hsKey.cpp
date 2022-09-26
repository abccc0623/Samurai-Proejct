#include "pch.h"


hsKey::hsKey()
{
	Key_F5 = false;
	Horizontal	= 0;
	Vertical	= 0;

	for (int i = 0; i < 256; i++)
	{
		isCurrent[i]	= false;
		isPrev[i]		= false;
	}
}

hsKey::~hsKey()
{


}

bool hsKey::KeyDown(int keynum)
{
	bool Check = false;
	if (GetAsyncKeyState(keynum) ) //z가 눌렸다
	{
		isCurrent[keynum] = true; //현재는 눌렸다
		if (isPrev[keynum] == false) //현재는 눌렸고 과거는 안눌렸을때
		{
			Check = true;
		}
		else if(isPrev[keynum] == true)//현재는 눌렸고 과거에도 눌렸을때
		{
			Check = false;
		}
	}
	else//현재에 안눌렸을때
	{
		Check = false;
		isCurrent[keynum] = false;
	}
	isPrev[keynum] = isCurrent[keynum];

	return Check;
}
bool hsKey::KeyUP(int keynum)
{
	bool Check = false;
	static bool current = false;
	static bool prev = false;

	if (GetAsyncKeyState(keynum)) //z가 눌렸다
	{
		current = true; //현재는 눌렸다
		if (current == true && prev == false) //현재는 눌렸고 과거는 안눌렸을때
		{
			Check = false;
		}
		else if (current == true && prev == true)//현재는 눌렸고 과거에도 눌렸을때
		{
			Check = false;
		}
	}
	else//현재에 안눌렸을때
	{
		current = false;
		if (current == false && prev == false) //현재는 안눌렸고 과거에도 안눌렸을때
		{
			Check = false;
		}
		else if (current == false && prev == true) //현재는 안눌렸고 과거에는 눌렸을때
		{
			Check = true;
		}
	}
	prev = current;

	return Check;
}


void hsKey::Update(float time)
{
	int Speed = 2;

	//오른쪽이 눌리면 서서히 1까지 올라간다
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		Horizontal = 1;
		
	}//왼쪽키를 눌리면 -1까지 내려간다
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		Horizontal = -1;
		
	}
	else
	{
		Horizontal = 0;
	}
	
	//왼쪽이 눌리면 서서히 -1 까지 내려간다
	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		Vertical = 1;
	}//왼쪽키를 눌리면 -1까지 내려간다
	else if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		Vertical = -1;
	}
	

}
