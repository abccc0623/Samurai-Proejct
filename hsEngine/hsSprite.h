#pragma once

class hsSprite
{
private:

public:
	hsSprite();
	~hsSprite();
	HDC		imgDC;
	HBITMAP imgbit;

	//�ִϸ��̼��� ��������Ұ�����
	bool isLoop;
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
	//�ѹ� ����ϴ� �ִϸ��̼��̶�� ����� ��������
	bool isEndAnime;

	float	spTime;
	int		nowCount;

	//�ɼ� �Է� ������ �ǹ� ��ġ
	void SetOption(float m_size, float m_pivotX, float m_pivotY);
	//�ش�Ǵ� �������� �ȴٸ� true ��������
	bool GetFrame(int FrameCount);
};

