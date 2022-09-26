#pragma once

class hsSprite
{
public:
	hsSprite();
	~hsSprite();
	HDC		imgDC;
	HBITMAP imgbit;

	//이미지의 사이즈
	float	size;
	//원본 이미지 크기
	SIZE Original_Size;
	//사이즈비율로 줄이거나 늘린 이미지 크기
	SIZE Re_Size;

	float pivotX;
	float pivotY;

	float pivotSizeX;
	float pivotSizeY;

	//내가 가지고있는 비트맵 이미지가 애니메이션이미지인지
	bool isAnime;
	//애니메이션을 나눌 카운터
	int AnimeCount;
	//애니메이션을 무한재생할것인지
	bool isLoop;

	float	spTime;
	int		nowCount;

	void SetOption(float m_size, float m_pivotX, float m_pivotY);
	//사이즈 비율 0~1 사이
	

	
};

