#include "framework.h"
#include "../hsEngine/pch.h"
#include "stdio.h"
#include "obj.h"
#include <iostream>
#include <vector>
using namespace std;
//#pragma comment(lib,"Release/hsEngine")



//배열의 최대크기
const int MaxX = 80;
const int MaxY = 46;

//충돌을 그릴때 
hsSprite* Map01;
hsSprite* Map02;
hsSprite* Map03;
hsSprite* Map04;


int State = 0;


obj* objList[MaxY][MaxX];
extern hsEngine* Engine = new hsEngine();

int CAM_X = 0;
int CAM_Y = 0;

int NowIndex_X;
int NowIndex_Y;

 hsSprite* Tile01;
 hsSprite* Tile02;
 hsSprite* Tile03;
 hsSprite* Tile04;


struct Data
{
	int GameData [MaxY][MaxX];
};

Data hs;
void Save()
{
	FILE* fp = NULL;
	fp = fopen("SaveMap/Stage01.sav", "wb");
	if (fp == NULL)
	{
		MessageBox(Engine->hwnd, L"세이브 실패",L"세이브실패", MB_OK);
		return;
	}

	fwrite(&hs, sizeof(Data), 1, fp);
	fclose(fp);

	MessageBox(Engine->hwnd, L"세이브 완료", L"완료", MB_OK);
}
void Load()
{
	FILE* fp = NULL;
	fp = fopen("SaveMap/Stage01.sav", "rb");
	if (fp == NULL)
	{
		MessageBox(Engine->hwnd, L"로드 실패", L"로드실패", MB_OK);
		return;
	}
	fread(&hs, sizeof(Data), 1, fp);

	fclose(fp);

	MessageBox(Engine->hwnd, L"로드완료", L"로드완료", MB_OK);
}

//마우스 좌표 그려주는 함수
void MousePos()
{
	static bool R_BUTTONUP = false;
	static bool L_BUTTONUP = false;


	hsVector2 mos = Engine->GetMousePos();
	float	numX = ((mos.cx + Engine->CamPos.cx) * 0.01);
	int	whole_X = (int)numX * 100;
	int	minority_X = (int)((numX * 100 - whole_X));


	float	numY = ((mos.cy + Engine->CamPos.cy) * 0.01);
	int	whole_Y = (int)numY * 100;
	int	minority_Y = (int)((numY * 100 - whole_Y));


	if (minority_X >= 50)
	{
		minority_X = whole_X + 99;
		whole_X += 50;
	}
	else
	{
		minority_X = whole_X + 50;
	}

	if (minority_Y >= 50)
	{
		minority_Y = whole_Y + 99;
		whole_Y += 50;
	}
	else
	{
		minority_Y = whole_Y + 50;
	}

	hsRect temp;
	temp.LEFT	= whole_X;
	temp.TOP	= whole_Y;
	temp.RIGHT	= minority_X;
	temp.BOTTOM = minority_Y;

	Engine->DrawRectangle(temp, (255, 0, 0));

	NowIndex_X = whole_X;
	NowIndex_Y = whole_Y;

	TCHAR str[256];
	_swprintf(str, TEXT("배열좌표 %d : %d"), whole_Y/50, whole_X / 50);
	TextOut(Engine->subDC,CAM_X, CAM_Y, str, lstrlen(str));

	_swprintf(str, TEXT("선택 타일 번호: %d"), State);
	TextOut(Engine->subDC, CAM_X, CAM_Y+25 , str, lstrlen(str));

	//마우스 오른쪽은 =0;
	//마우스 왼쪽은 = 1;
	//왼쪽 버튼을 눌렀을때 배열을 1로 바꾸고 해당 타일 생성
	if (GetKeyState(VK_LBUTTON) & 0x8000)
	{
		int X = whole_X / 50;
		int Y = whole_Y / 50;

		hs.GameData[Y][X] = State;
		obj* temp = new obj();
		switch (State)
		{
		case 1:
			temp->Create(Tile01, whole_Y, whole_X);
			break;
		case 2:
			temp->Create(Tile02, whole_Y, whole_X);
			break;
		case 3:
			temp->Create(Tile03, whole_Y, whole_X);
			break;
		case 4:
			temp->Create(Tile04, whole_Y, whole_X);
			break;
		}
		objList[Y][X] = temp;
	}

	//오른쪽 버튼을 눌렀을때 배열을 0으로 바꾸고 있던 타일맵 삭제
	if (GetKeyState(VK_RBUTTON) & 0x8000)
	{
		if (hs.GameData[whole_Y / 50][whole_X / 50] != 0)
		{
			int X = whole_X / 50;
			int Y = whole_Y / 50;
			obj* temp = objList[Y][X];
			//delete temp;
			objList[Y][X] = nullptr;
			hs.GameData[Y][X] = 0;
		}
	}
	


}
//화면 이동 방향
void  Cam()
{
	hsVector2 pos;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
	{
		CAM_X += 5;
	}
	
	if (GetAsyncKeyState(VK_LEFT) & 0x8001)
	{
		CAM_X-= 5;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		CAM_Y-= 5;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		CAM_Y+=5;
	}


	if (GetAsyncKeyState(VK_F1) & 0x0001)
	{
		State = 0;
	}
	if (GetAsyncKeyState(VK_F2) & 0x0001)
	{
		State = 1;
	}
	if (GetAsyncKeyState(VK_F3) & 0x0001)
	{
		State = 2;
	}
	if (GetAsyncKeyState(VK_F4) & 0x0001)
	{
		State = 3;
	}
	if (GetAsyncKeyState(VK_F5) & 0x0001)
	{
		State = 4;
	}

}






// 윈도 프로시저의 전방선언
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


// 메인 함수
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow)
{
	/// 윈도를 등록한다.
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL; // LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL; // MAKEINTRESOURCEW(IDC_PROJECT1);
	wcex.lpszClassName = L"PROJECT1";
	wcex.hIconSm = NULL;// LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassExW(&wcex);


	int iMonitorWidth = GetSystemMetrics(SM_CXSCREEN);    // 모니터 가로 해상도
	int iMonitorHeight = GetSystemMetrics(SM_CYSCREEN);    // 모니터 세로 해상도


	// 애플리케이션 초기화를 수행합니다:
	 HWND hWnd = CreateWindowW(L"PROJECT1", L"My blade seeks vengeance!", WS_OVERLAPPEDWINDOW,
		0, 0, iMonitorWidth, iMonitorHeight, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	
	//엔진 만들기
	Engine->init(hWnd, hInstance, iMonitorWidth, iMonitorHeight,5000);
	

	Tile01 = Engine->LoadSprite(L"img/Tile01.bmp");
	Tile01->SetOption(1, 0, 0);

	Tile02 = Engine->LoadSprite(L"img/Tile02.bmp");
	Tile02->SetOption(1, 0, 0);

	Tile03 = Engine->LoadSprite(L"img/Tile03.bmp");
	Tile03->SetOption(1, 0, 0);

	Tile04 = Engine->LoadSprite(L"img/Tile04.bmp");
	Tile04->SetOption(1, 0, 0);

	

	Map01 = Engine->LoadSprite(L"img/Map01.bmp");
	Map02 = Engine->LoadSprite(L"img/Map02.bmp");
	Map03 = Engine->LoadSprite(L"img/Map03.bmp");
	Map04 = Engine->LoadSprite(L"img/Map04.bmp");

	Map01->SetOption(1, 0, 0);
	Map02->SetOption(1, 0, 0);
	Map03->SetOption(1, 0, 0);
	Map04->SetOption(1, 0, 0);
	
	Load();


	for (int i = 0; i < MaxY; i++)
	{
		for (int j = 0; j < MaxX; j++)
		{
			if (hs.GameData[i][j] == 1)
			{
				obj* temp = new obj();
				temp->Create(Tile01, i*50, j*50);
				objList[i][j] = temp;
			}
			else if (hs.GameData[i][j] == 2)
			{
				obj* temp = new obj();
				temp->Create(Tile02, i * 50, j * 50);
				objList[i][j] = temp;
			}
			else if (hs.GameData[i][j] == 3)
			{
				obj* temp = new obj();
				temp->Create(Tile03, i * 50, j * 50);
				objList[i][j] = temp;
			}
			else if (hs.GameData[i][j] == 4)
			{
				obj* temp = new obj();
				temp->Create(Tile04, i * 50, j * 50);
				objList[i][j] = temp;
			}
		}
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	MSG msg;

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				break;
			}
		}
		else
		{
			

			Engine->SpriteRender(Map01, 0, 0);
			Engine->SpriteRender(Map02, 1920, 0);
			Engine->SpriteRender(Map03, 0, 1080);
			Engine->SpriteRender(Map04, 1920, 1080);

			for (int i = 0; i < MaxY; i++)
			{
				for (int j = 0; j < MaxX; j++)
				{
					if (hs.GameData[i][j] != 0)
					{
						objList[i][j]->Render();
					}	
				}
			}


			MousePos();
			Cam();
			//Engine->DebugGameOption(RGB(0, 0, 0));
			Engine->DebugGrid(4000, 4000, 50, 50, RGB(0, 100, 0));
			//게임 업데이트 부분
			Engine->Update();
			Engine->EndRender(CAM_X,CAM_Y);
		}
	}

	delete Tile01;
	delete Tile02;
	delete Tile03;
	delete Tile04;

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		Save();
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		PAINTSTRUCT pr;
		BeginPaint(hWnd, &pr);


		EndPaint(hWnd, &pr);
		break;
	case WM_MOUSEMOVE:
		Engine->SetMousePos(LOWORD(lParam), HIWORD(lParam));
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

