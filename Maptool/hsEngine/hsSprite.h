#pragma once

class hsSprite
{
public:
	hsSprite();
	~hsSprite();
	HDC		imgDC;
	HBITMAP imgbit;

	//�̹����� ������
	float	size;
	//���� �̹��� ũ��
	SIZE Original_Size;
	//����������� ���̰ų� �ø� �̹��� ũ��
	SIZE Re_Size;

	float pivotX;
	float pivotY;

	float pivotSizeX;
	float pivotSizeY;

	//���� �������ִ� ��Ʈ�� �̹����� �ִϸ��̼��̹�������
	bool isAnime;
	//�ִϸ��̼��� ���� ī����
	int AnimeCount;
	//�ִϸ��̼��� ��������Ұ�����
	bool isLoop;

	float	spTime;
	int		nowCount;

	void SetOption(float m_size, float m_pivotX, float m_pivotY);
	//������ ���� 0~1 ����
	

	
};

