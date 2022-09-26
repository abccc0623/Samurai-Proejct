#pragma once

class hsEngine
{
private:

	HDC mainDC;			//메인 DC
	
	HBITMAP	SubBit;		//서브 비트맵

	HDC uiDC;			//UI_DC;
	HBITMAP	uiBit;		//ui비트맵

	HDC debugDC;		//디버깅용 DC
	HBITMAP debugBit;	//디버깅용 bit

	
	HINSTANCE	hInstan;

	SIZE		Resolution;	//클라이언트 화면 해상도
	SIZE		ClientSize; //클라이언트 화면사이즈


	hsVector2	mosPos;		//마우스 포지션
	int  SubBufferSize = 0; //게임맵 크기
	hsKey key;



	float GetTime(); //내부적으로 시간을 돌리는 함수
	float DeltaTime; //dTime 바꾸지못하게 함수로 내보내줌
public:
	HWND hwnd;			//메인 비트맵
	hsVector2	CamPos;		//카메라 위치 왼쪽위 좌표이다
	HDC subDC;			//서브 DC
	
	hsEngine();
	~hsEngine();


	void init(HWND hWnd, HINSTANCE hInstance, int ClientSizeX, int ClientSizeY, int MapSize);
	void Update();

	////////////////////////////////////////////////////////////그리는 함수들
	//선을그리는 함수
	void DrawLine(int Start_X, int Start_Y, int End_X, int End_Y, COLORREF rgb);

	//사각형을 그리는함수(x)
	void DrawRectangle(int Left, int UP, int Right, int bottom, COLORREF rgb);
	void DrawRectangle(hsRect rect, COLORREF rgb);
	
	
	///////////////////////////////////////////////////////////스프라이트 함수
	//비트맵을 로드하는 함수 (경로를 설정해준다)
	hsSprite* LoadSprite(LPCUWSTR path);
	//스프라이트를 렌더링해주는 함수
	void SpriteRender(hsSprite* spr, int posX, int posY);
	//스프라이트를 애니메이션으로 나눠주는 함수
	void CreateAnime(hsSprite* spr, int animeCount, bool loop = true);
	void AnimeRender(hsSprite* spr, int posX, int posY, float Speed);
	//그리기를 끝냈을때 실행 해야하는 함수(중요)
	void EndRender(float pos_X, float pos_Y);

	///////////////////////////////////////////////////////////키입력함수
	//마우스 포지션을 가져오는 함수
	void SetMousePos(float L_Pos, float R_Pos);
	hsVector2 GetMousePos();

	///////////////////////////////////////////////////////////디버깅함수
	//게임 제작에 필요한정보들을 보여주거나 그려주는 함수들
	//화면에 바둑판처럼 그리드를 그려준다 
	void DebugGrid(int X, int Y, int Width, int Height, COLORREF rgb);
	//게임 옵션들은 화면에 뿌려준다
	void DebugGameOption(COLORREF rgb);
	
	//////////////////////////////////////////////////////////시간함수
	float GetDeltaTime();
	//방향키버튼 오른쪽 : x , 왼쪽 : y
	hsVector2 GetHorizontalKey();

	hsVector2 GetVirticalKey();
	//void hsEngine::StartRender();
	
};



