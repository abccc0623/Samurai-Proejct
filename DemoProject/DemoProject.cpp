#pragma comment(lib,"winmm")
#include <windows.h>
#include <digitalv.h>
#include "sound.h"

#include "framework.h"
#include "stdio.h"
#pragma comment(lib,"Release/hsEngine")
#include "../hsEngine/pch.h"
#include "Player.h"
#include "Eclass.h"
#include "GameManager.h"
#include "assert.h"

#define SAMURAI Player::GetPlayer() 
#define GM		GameManager::GetGM()

//게임 엔진
hsEngine* Engine = new hsEngine();

int GameNum = 0;
//맵 매니저

// 윈도 프로시저의 전방선언
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// 메인 함수
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow)
{
	srand(GetTickCount64());
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
	

	DEVMODE dmSaved;// 현재 해상도를 저장.. 왜냐 게임 끝나면 원래대로 돌려야 하니깐
	DEVMODE dmSelected;// 원하는 해상도를 저장하는 변수
	



	// 애플리케이션 초기화를 수행합니다:
	HWND hWnd = CreateWindowW(L"PROJECT1", L"My blade seeks vengeance!", WS_POPUP,
		0, 0, iMonitorWidth, iMonitorHeight, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	
	

	//엔진 만들기
	Engine->init(hWnd, hInstance, iMonitorWidth, iMonitorHeight,8000);
	GameManager::GetGM(); 
	Player::GetPlayer();
	
	//로고
	hsSprite title_img = *Engine->LoadSprite("../GameData/map/intro/title.bmp");
	title_img.SetOption(1, 0, 0);
	//인트로 부분
	hsSprite intro_img = *Engine->LoadSprite("../GameData/map/intro/scene01.bmp");
	intro_img.SetOption(1, 0,0);
	//엔딩부분
	hsSprite End_img = *Engine->LoadSprite("../GameData/map/intro/EndGame.bmp");
	intro_img.SetOption(1, 0, 0);


	SAMURAI->init();
	GM->init();
	Sound* NowSound =  GM->PlayGameSound_Loop((int)SOUND::BGM_TITLE);
	

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	MSG msg;

	int a = 0;
	assert(a != 0);

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

			if(Engine->key.KeyDown(VK_ESCAPE))
			{
				PostQuitMessage(0);
			}




			switch (GameNum)
			{
			case (int)GAME::LOGO:
				if (Engine->key.KeyDown(VK_RETURN))
				{
					GameNum++;
				}
				Engine->TileRender(&title_img, 0, 0);
				Engine->Update();
				Engine->EndRender(0, 0);
				break;
			case (int)GAME::INTRO:
				if (Engine->key.KeyDown(VK_RETURN))
				{
					NowSound->soundClose();
					NowSound = GM->PlayGameSound_Loop((int)SOUND::BGM_MAIN);
					GameNum++;
				}
				Engine->TileRender(&intro_img, 0, 0);
				Engine->Update();
				Engine->EndRender(0, 0);
				break;
			case (int)GAME::INGAME:
				GM->Update();
				Engine->Update();
				SAMURAI->Update();
				SAMURAI->Render();
				Engine->EndRender(SAMURAI->Pos.cx, SAMURAI->Pos.cy);
				break;
			case (int)GAME::END:
				Engine->TileRender(&End_img, 0, 0);
				Engine->Update();
				Engine->EndRender(0, 0);
				break;
			}


		}
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SIZE:
	{
		int b = 0;
		assert(b != 0);
		break;
	}
	case WM_DESTROY:
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

