#include "pch.h"


hsKey::hsKey()
{
	Key_F5 = false;
}

hsKey::~hsKey()
{
}

void hsKey::Update(float time)
{
	int Speed = 2;

	//오른쪽이 눌리면 서서히 1까지 올라간다
	if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
	{
		Horizontal += time* Speed;
		if (Horizontal >= 1)
		{
			Horizontal = 1;
		}
	}//왼쪽키를 눌리면 -1까지 내려간다
	else if (GetAsyncKeyState(VK_LEFT) & 0x8001)
	{
		Horizontal -= time * Speed;
		if (Horizontal <= -1)
		{
			Horizontal = -1;
		}
	}
	else //둘다아니라면 1은 점점 내려가서 0까지 -1은 점점올라가서 0까지
	{
		if (Horizontal > 0) 
		{
			Horizontal -= time * Speed;
			if (Horizontal <= 0)
			{
				Horizontal = 0;
			}
		}
		else if (Horizontal < 0)
		{
			Horizontal += time * Speed;
			if (Horizontal >= 0)
			{
				Horizontal = 0;
			}
		}
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		Vertical += time * Speed;
		if (Vertical >= 1)
		{
			Vertical = 1;
		}
	}//왼쪽키를 눌리면 -1까지 내려간다
	else if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		Vertical -= time * Speed;
		if (Vertical <= -1)
		{
			Vertical = -1;
		}
	}
	else //둘다아니라면 1은 점점 내려가서 0까지 -1은 점점올라가서 0까지
	{
		if (Vertical > 0)
		{
			Vertical -= time * Speed;
			if (Horizontal <= 0)
			{
				Horizontal = 0;
			}
		}
		else if (Vertical < 0)
		{
			Vertical += time * Speed;
			if (Vertical >= 0)
			{
				Vertical = 0;
			}
		}
	}






	
}
