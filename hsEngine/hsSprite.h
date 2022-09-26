#pragma once

class hsSprite
{
private:

public:
	hsSprite();
	~hsSprite();
	HDC		imgDC;
	HBITMAP imgbit;

	//애니메이션을 무한재생할것인지
	bool isLoop;
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
	//한번 재생하는 애니메이션이라면 재생이 끝났는지
	bool isEndAnime;

	float	spTime;
	int		nowCount;

	//옵션 입력 사이즈 피벗 위치
	void SetOption(float m_size, float m_pivotX, float m_pivotY);
	//해당되는 프레임이 된다면 true 내보내줌
	bool GetFrame(int FrameCount);
};

