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
	if (GetAsyncKeyState(keynum) ) //z�� ���ȴ�
	{
		isCurrent[keynum] = true; //����� ���ȴ�
		if (isPrev[keynum] == false) //����� ���Ȱ� ���Ŵ� �ȴ�������
		{
			Check = true;
		}
		else if(isPrev[keynum] == true)//����� ���Ȱ� ���ſ��� ��������
		{
			Check = false;
		}
	}
	else//���翡 �ȴ�������
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

	if (GetAsyncKeyState(keynum)) //z�� ���ȴ�
	{
		current = true; //����� ���ȴ�
		if (current == true && prev == false) //����� ���Ȱ� ���Ŵ� �ȴ�������
		{
			Check = false;
		}
		else if (current == true && prev == true)//����� ���Ȱ� ���ſ��� ��������
		{
			Check = false;
		}
	}
	else//���翡 �ȴ�������
	{
		current = false;
		if (current == false && prev == false) //����� �ȴ��Ȱ� ���ſ��� �ȴ�������
		{
			Check = false;
		}
		else if (current == false && prev == true) //����� �ȴ��Ȱ� ���ſ��� ��������
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

	//�������� ������ ������ 1���� �ö󰣴�
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		Horizontal = 1;
		
	}//����Ű�� ������ -1���� ��������
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		Horizontal = -1;
		
	}
	else
	{
		Horizontal = 0;
	}
	
	//������ ������ ������ -1 ���� ��������
	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		Vertical = 1;
	}//����Ű�� ������ -1���� ��������
	else if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		Vertical = -1;
	}
	

}
