#pragma once

class hsEngine
{
private:

	HDC mainDC;			//���� DC
	
	HBITMAP	SubBit;		//���� ��Ʈ��

	HDC uiDC;			//UI_DC;
	HBITMAP	uiBit;		//ui��Ʈ��

	HDC debugDC;		//������ DC
	HBITMAP debugBit;	//������ bit

	
	HINSTANCE	hInstan;

	SIZE		Resolution;	//Ŭ���̾�Ʈ ȭ�� �ػ�
	SIZE		ClientSize; //Ŭ���̾�Ʈ ȭ�������


	hsVector2	mosPos;		//���콺 ������
	int  SubBufferSize = 0; //���Ӹ� ũ��
	hsKey key;



	float GetTime(); //���������� �ð��� ������ �Լ�
	float DeltaTime; //dTime �ٲ������ϰ� �Լ��� ��������
public:
	HWND hwnd;			//���� ��Ʈ��
	hsVector2	CamPos;		//ī�޶� ��ġ ������ ��ǥ�̴�
	HDC subDC;			//���� DC
	
	hsEngine();
	~hsEngine();


	void init(HWND hWnd, HINSTANCE hInstance, int ClientSizeX, int ClientSizeY, int MapSize);
	void Update();

	////////////////////////////////////////////////////////////�׸��� �Լ���
	//�����׸��� �Լ�
	void DrawLine(int Start_X, int Start_Y, int End_X, int End_Y, COLORREF rgb);

	//�簢���� �׸����Լ�(x)
	void DrawRectangle(int Left, int UP, int Right, int bottom, COLORREF rgb);
	void DrawRectangle(hsRect rect, COLORREF rgb);
	
	
	///////////////////////////////////////////////////////////��������Ʈ �Լ�
	//��Ʈ���� �ε��ϴ� �Լ� (��θ� �������ش�)
	hsSprite* LoadSprite(LPCUWSTR path);
	//��������Ʈ�� ���������ִ� �Լ�
	void SpriteRender(hsSprite* spr, int posX, int posY);
	//��������Ʈ�� �ִϸ��̼����� �����ִ� �Լ�
	void CreateAnime(hsSprite* spr, int animeCount, bool loop = true);
	void AnimeRender(hsSprite* spr, int posX, int posY, float Speed);
	//�׸��⸦ �������� ���� �ؾ��ϴ� �Լ�(�߿�)
	void EndRender(float pos_X, float pos_Y);

	///////////////////////////////////////////////////////////Ű�Է��Լ�
	//���콺 �������� �������� �Լ�
	void SetMousePos(float L_Pos, float R_Pos);
	hsVector2 GetMousePos();

	///////////////////////////////////////////////////////////������Լ�
	//���� ���ۿ� �ʿ����������� �����ְų� �׷��ִ� �Լ���
	//ȭ�鿡 �ٵ���ó�� �׸��带 �׷��ش� 
	void DebugGrid(int X, int Y, int Width, int Height, COLORREF rgb);
	//���� �ɼǵ��� ȭ�鿡 �ѷ��ش�
	void DebugGameOption(COLORREF rgb);
	
	//////////////////////////////////////////////////////////�ð��Լ�
	float GetDeltaTime();
	//����Ű��ư ������ : x , ���� : y
	hsVector2 GetHorizontalKey();

	hsVector2 GetVirticalKey();
	//void hsEngine::StartRender();
	
};



