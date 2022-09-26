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

	//�������� ������ ������ 1���� �ö󰣴�
	if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
	{
		Horizontal += time* Speed;
		if (Horizontal >= 1)
		{
			Horizontal = 1;
		}
	}//����Ű�� ������ -1���� ��������
	else if (GetAsyncKeyState(VK_LEFT) & 0x8001)
	{
		Horizontal -= time * Speed;
		if (Horizontal <= -1)
		{
			Horizontal = -1;
		}
	}
	else //�Ѵپƴ϶�� 1�� ���� �������� 0���� -1�� �����ö󰡼� 0����
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
	}//����Ű�� ������ -1���� ��������
	else if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		Vertical -= time * Speed;
		if (Vertical <= -1)
		{
			Vertical = -1;
		}
	}
	else //�Ѵپƴ϶�� 1�� ���� �������� 0���� -1�� �����ö󰡼� 0����
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
