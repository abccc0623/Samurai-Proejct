﻿// hsEngine.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//
#include "pch.h"
#include "framework.h"
#include "windows.h"
#include "stdio.h"
#pragma comment(lib,"Msimg32")

hsEngine::hsEngine()
{
	mainDC		= NULL;

	subDC		= NULL;
	SubBit		= NULL;

	hwnd		= NULL;
	hInstan		= NULL;
	ClientSize	= {0,0};

	Resolution = { 1920, 1080 };

	mosPos = hsVector2();
	mosPos.zore();

	CamPos = hsVector2();
	CamPos.zore();
	
}

hsEngine::~hsEngine()
{
	//메인DC 삭제
	ReleaseDC(hwnd,mainDC);
	//서브 DC삭제
	DeleteObject(SubBit);
	DeleteDC(subDC);
		
}

//사각형 그리기
void hsEngine::DrawRectangle(int Left,int UP, int Right,int bottom,COLORREF rgb)
{
	HPEN pen = CreatePen(PS_COSMETIC, 5, rgb);
	SelectObject(subDC, pen);
	//Rectangle(subDC, Left, UP, Right, bottom);

	MoveToEx(subDC, Left, UP, NULL);
	LineTo(subDC, Right, UP);

	MoveToEx(subDC, Right, UP, NULL);
	LineTo(subDC, Right, bottom);

	MoveToEx(subDC, Right, bottom, NULL);
	LineTo(subDC, Left, bottom);

	MoveToEx(subDC, Left, bottom, NULL);
	LineTo(subDC, Left, UP);


	DeleteObject(pen);
}
void hsEngine::DrawRectangle(hsRect rect, COLORREF rgb)
{
	HPEN pen = CreatePen(PS_COSMETIC, 2, rgb);
	SelectObject(subDC, pen);

	MoveToEx(subDC, rect.LEFT, rect.TOP,NULL);
	LineTo(subDC, rect.RIGHT, rect.TOP);

	MoveToEx(subDC, rect.RIGHT, rect.TOP, NULL);
	LineTo(subDC, rect.RIGHT, rect.BOTTOM);

	MoveToEx(subDC, rect.RIGHT, rect.BOTTOM, NULL);
	LineTo(subDC, rect.LEFT, rect.BOTTOM);

	MoveToEx(subDC, rect.LEFT, rect.BOTTOM, NULL);
	LineTo(subDC, rect.LEFT, rect.TOP);


	DeleteObject(pen);
}

//선그리기
void hsEngine::DrawLine(int Start_X,int Start_Y,int End_X,int End_Y,COLORREF rgb)
{
	HPEN pen = CreatePen(PS_COSMETIC, 1, rgb);
	SelectObject(subDC, pen);

	MoveToEx(subDC,Start_X,Start_Y,NULL);
	LineTo(subDC,End_X,End_Y);
	
	DeleteObject(pen);
}

//스프라이트 로딩
hsSprite* hsEngine::LoadSprite(LPCSTR path)
{
	hsSprite* img = new hsSprite();
	
	//여기까지 비트맵 불러오기
	img->imgDC = CreateCompatibleDC(mainDC);
	

	img->imgbit = 
		(HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0,
			 LR_LOADFROMFILE);

	SelectObject(img->imgDC, img->imgbit);

	BITMAP bit;
	GetObject(img->imgbit, sizeof(BITMAP), &bit);

	img->Original_Size.cx = bit.bmWidth;
	img->Original_Size.cy = bit.bmHeight;
	img->Re_Size.cx = bit.bmWidth;
	img->Re_Size.cy = bit.bmHeight;
	
	
	return img;
}
//스프라이트 랜더
void hsEngine::SpriteRender(hsSprite* spr, int posX, int posY)
{
	//스프라이트를 받아와서 그려준다 
	//이떄 스프라이트 사이즈 비율로 인해 이미지를 줄이거나 늘린다
	
	float imgSizeX = spr->Re_Size.cx * spr->size;
	float imgSizeY = spr->Re_Size.cy * spr->size;

	float lerpX = (1 * (1.0f - spr->pivotX)) + (imgSizeX * (spr->pivotX));
	float lerpY = (1 * (1.0f - spr->pivotY)) + (imgSizeY * (spr->pivotY));

	TransparentBlt
	(
		subDC,
		posX - lerpX,
		posY - lerpY,
		imgSizeX,
		imgSizeY,
		spr->imgDC,
		0,
		0,
		spr->Original_Size.cx,
		spr->Original_Size.cy,
		RGB(0,255,0)
	);
}
//스프라이트 를 애니메이션으로 
void hsEngine::CreateAnime(hsSprite* spr, int animeCount,bool loop)
{
	//스프라이트를 에니메이션을 할수있도록 바꿔준다
	//
	spr->Re_Size.cx = spr->Original_Size.cx/ animeCount;
	spr->Re_Size.cy = spr->Original_Size.cy;
	spr->Original_Size.cx = spr->Original_Size.cx/ animeCount;
	//s->r.Original_Size.cy = spr.Original_Size.cy/ animeCount;
	spr->isLoop = loop;
	spr->isAnime = true;
	spr->AnimeCount = animeCount;
}

//애니메이션 랜더
void hsEngine::AnimeRender(hsSprite* spr, int posX, int posY,float Speed,float Alpha)
{
	spr->spTime += DeltaTime;
	if (spr->spTime >= Speed)
	{
		spr->nowCount++;

		if (spr->isLoop == true) 
		{
			//카운터가 끝이되었을때 다시0으로
			if (spr->nowCount >= spr->AnimeCount)
			{
				spr->nowCount = 0;
			}
		}
		else if(spr->isLoop == false)
		{
			//카운터가 끝이되었을때 그냥그대로
			if (spr->nowCount >= spr->AnimeCount)
			{
				spr->nowCount = spr->AnimeCount-1;
				spr->isEndAnime = true;
			}
		}
		spr->spTime = 0;
	}


	float imgSizeX = spr->Re_Size.cx * spr->size;
	float imgSizeY = spr->Re_Size.cy * spr->size;

	float lerpX = (1 * (1.0f - spr->pivotX)) + (imgSizeX * (spr->pivotX));
	float lerpY = (1 * (1.0f - spr->pivotY)) + (imgSizeY * (spr->pivotY));


	BLENDFUNCTION BlendOption;
	BlendOption.BlendOp = AC_SRC_OVER;
	BlendOption.BlendFlags = 0;
	BlendOption.SourceConstantAlpha = (BYTE)(255 * Alpha);	//혼합 비율.30%. 255=100% 불투명 (원본). 0=완전 투명★
	BlendOption.AlphaFormat = 0;								//알파블렌딩 형식.
	BlendOption.AlphaFormat = AC_SRC_ALPHA;					//비트멥이 알파채널이 있는 경우 (32비트 A8R8G8B8) 설정가능★
	
	int res = AlphaBlend
	(
		subDC,
		posX - lerpX,
		posY - lerpY,
		imgSizeX,
		imgSizeY,
		spr->imgDC,
		spr->Re_Size.cx * spr->nowCount,
		0,
		spr->Original_Size.cx,
		spr->Original_Size.cy,
		BlendOption
	);
}
void hsEngine::TileRender(hsSprite* spr, int posX, int posY)
{
	float imgSizeX = spr->Re_Size.cx * spr->size;
	float imgSizeY = spr->Re_Size.cy * spr->size;

	float lerpX = (1 * (1.0f - spr->pivotX)) + (imgSizeX * (spr->pivotX));
	float lerpY = (1 * (1.0f - spr->pivotY)) + (imgSizeY * (spr->pivotY));

	BitBlt
	(
		subDC,
		posX - lerpX,
		posY - lerpY,
		imgSizeX,
		imgSizeY,
		spr->imgDC,
		0,
		0,
		SRCCOPY
	);
}


//모든 랜더링을 끝냈다
void hsEngine::EndRender(int pos_X,int pos_Y)
{
	//캐릭터가 왼쪽으로 이동할때
	//그려질 영역을 선택한다 왼쪽위 기준으로
	//0보다 작아지면 더이상이동하는걸 멈춘다
	//캐릭터가 오른쪽으로 이동할때
	//현재 좌표에서 클라이언트 사이즈 - 빽버퍼 사이즈만큼뺀값이 널어가질안도록한다
	//int X = CamPos.cx  + pos_X;

	//카메라 워크...
	float CamMoveSpeed = 0.9f;


	//선형 보간법
	//플레이어 위치 * (1 - 알고싶은 좌표) + (카메라 위치 * (알고싶은좌표 ));
	
	//왼쪽위 카메라에서 클라이언트 사이즈/2 한기준값으로
	//플레이어왕 나의 선형보간법을 계속구한다 그걸다시
	//왼쪽위 카메라 좌표에 넣어준다



	float MoveSpeed = 0.5f;
	float LEFT	= pos_X - ClientSize.cx/2;
	float RIGHT = (ClientSize.cx / 2) ;
	if (LEFT <= 0) 
	{
		LEFT = 0;
	}

 	float x = ClientSize.cx - 1920;
	RIGHT = (1920*2) - ClientSize.cx;
	if(LEFT >= RIGHT)
	{
		LEFT = RIGHT;
	}

	float UP	= pos_Y - 1080/2;
	if (UP <= 0)
	{
		UP = 0;
	}

	int Y = (ClientSize.cy - 1080);
	float DOWN = 1080 - Y;
	if (UP > DOWN) 
	{
		UP = DOWN;
	}

	//플레이어 위치 = pos_x
	//카메라 게임좌표 (왼쪽위) = LEFT
	//Left + ClientSize.cy/2 == 카메라 중앙점?
	//RIGHT +ClientSize.cy/2 == 카메라 중앙점?

	

	BitBlt(mainDC,
		0,
		0,
		ClientSize.cx, 
		ClientSize.cy,
		subDC,
		LEFT ,
		UP, 
		SRCCOPY);

	CamPos.cx = LEFT;
	CamPos.cy = UP;
	
	Rectangle(subDC, LEFT, UP, LEFT +ClientSize.cx,UP + +ClientSize.cy);
}

//마우스 가져오기
void hsEngine::SetMousePos(int L_Pos, int R_Pos)
{
	mosPos.cx = L_Pos;
	mosPos.cy = R_Pos;

}
//마우스 내보내기
hsVector2  hsEngine::GetMousePos()
{
	return mosPos;
}

//디버깅 그리드 출력
void hsEngine::DebugGrid(int X,int Y,int Width,int Height,COLORREF rgb)
{
	HPEN pen = CreatePen(PS_COSMETIC, 1, rgb);
	SelectObject(subDC, pen);
	int sizeX = 0;
	int sizeY = 0;

	while (sizeX < X)
	{
		MoveToEx(subDC, sizeX, 0, NULL);
		LineTo(subDC, sizeX, Y);
		sizeX += Width;
		X++;
	}

	while (sizeY < Y)
	{
		MoveToEx(subDC, 0, sizeY, NULL);
		LineTo(subDC, X, sizeY);
		sizeY += Height;
		Y++;
	}

	DeleteObject(pen);
}

//게임 옵션들을 보여준다
void hsEngine::DebugGameOption(COLORREF rgb)
{
	SetTextColor(subDC, rgb);

	int X = CamPos.cx;
	int Y = CamPos.cy;

	//게임 시간 출력
	static float PlayTime = 0;
	PlayTime += DeltaTime;

	CHAR str[256];
	sprintf(str, TEXT("GamePlayTime:%f"), PlayTime);
	TextOut(subDC, X, Y, str, lstrlen(str));

	sprintf(str, TEXT("-------------------"));
	TextOut(subDC, X, Y + 25, str, lstrlen(str));
	sprintf(str, TEXT("마우스좌표"));
	TextOut(subDC, X, Y + 50, str, lstrlen(str));
	sprintf(str, TEXT("X :%d, Y: %0.2d"), mosPos.cx+X, mosPos.cy +Y);
	TextOut(subDC, X, Y+75, str, lstrlen(str));

	sprintf(str, TEXT("카메라 좌표(왼쪽위 기준)"));
	TextOut(subDC, X, Y + 100, str, lstrlen(str));
	sprintf(str, TEXT("X :%d, Y: %d"),CamPos.cx, CamPos.cy);
	TextOut(subDC, X, Y + 125, str, lstrlen(str));


	sprintf(str, TEXT("현재 모니터 크기"));
	TextOut(subDC, X, Y + 150, str, lstrlen(str));
	sprintf(str, TEXT("X :%d, Y: %d"), ClientSize.cx, ClientSize.cy);
	TextOut(subDC, X, Y + 175, str, lstrlen(str));

	sprintf(str, TEXT("현재 게임 해상도"));
	TextOut(subDC, X, Y + 200, str, lstrlen(str));
	sprintf(str, TEXT("X :%d, Y: %d"), Resolution.cx, Resolution.cy);
	TextOut(subDC, X, Y + 225, str, lstrlen(str));


	sprintf(str, TEXT("Horizontal : %0.2f"),key.Horizontal);
	TextOut(subDC, X, Y + 250, str, lstrlen(str));
	sprintf(str, TEXT("Vertical : %0.2f"), key.Vertical);
	TextOut(subDC, X, Y + 275, str, lstrlen(str));

}

//엔진 생성하기
void hsEngine::init(HWND m_hWnd, HINSTANCE m_hInstance,int ClientSizeX,int ClientSizeY,int MapSize)
{
	hwnd	= m_hWnd;
	hInstan = m_hInstance;
	ClientSize.cx = ClientSizeX;
	ClientSize.cy = ClientSizeY;
	


	//메인버퍼
	mainDC = GetDC(hwnd); 
	
	//서브버퍼 생성
	subDC	= CreateCompatibleDC(mainDC);
	SubBit	= CreateCompatibleBitmap(mainDC, 4000,2200);
	SelectObject(subDC, SubBit);

	SubBufferSize.cx = 4000;
	SubBufferSize.cy = 1080*2;
}
//엔진 자체 업데이트
void hsEngine::Update()
{
	DeltaTime = GetTime();
	key.Update(DeltaTime);

}

float hsEngine::GetTime()
{
	static ULONGLONG oldtime = GetTickCount64();
	ULONGLONG nowtime = GetTickCount64();
	float dTime = ((nowtime - oldtime) % 1000) * 0.001f;
	oldtime = nowtime;
	return dTime;
}
//게임 프레임 내보내기
float hsEngine::GetDeltaTime()
{
	return DeltaTime;
}
//수평이동키 얻어오기
float hsEngine::GetHorizontalKey()
{
	float dir = 0;
	dir = key.Horizontal;
	return dir;
}
float hsEngine::GetVirticalKey()
{
	float dir = 0;
	dir = key.Vertical;
	return dir;
}

