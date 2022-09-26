#pragma once

class hsEngine
{
private:

	HDC		mainDC;			//���� DC
	HWND	hwnd;			//���� ��Ʈ��
	
	HDC		subDC;			//���� DC
	HBITMAP	SubBit;		//���� ��Ʈ��

	

	
	HINSTANCE	hInstan;

	SIZE		Resolution;	//Ŭ���̾�Ʈ ȭ�� �ػ�
	SIZE		ClientSize; //Ŭ���̾�Ʈ ȭ�������


	hsVector2	mosPos;		//���콺 ������
	hsVector2	CamPos;		//ī�޶� ��ġ ������ ��ǥ�̴�
	hsVector2  SubBufferSize; //���Ӹ� ũ��



	float GetTime(); //���������� �ð��� ������ �Լ�
	float DeltaTime; //dTime �ٲ������ϰ� �Լ��� ��������
public:
	
	hsKey key;
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
	hsSprite* LoadSprite(LPCSTR path);
	//��������Ʈ�� ���������ִ� �Լ�
	void SpriteRender(hsSprite* spr, int posX, int posY);
	//��������Ʈ�� �ִϸ��̼����� �����ִ� �Լ�
	void CreateAnime(hsSprite* spr, int animeCount, bool loop = true);
	void AnimeRender(hsSprite* spr, int posX, int posY, float Speed,float Alpha = 1);
	void TileRender(hsSprite* spr, int posX, int posY);
	//�׸��⸦ �������� ���� �ؾ��ϴ� �Լ�(�߿�)
	void EndRender(int pos_X, int pos_Y);

	///////////////////////////////////////////////////////////Ű�Է��Լ�
	//���콺 �������� �������� �Լ�
	void SetMousePos(int L_Pos, int R_Pos);
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
	float GetHorizontalKey();
	float GetVirticalKey();
	//void hsEngine::StartRender();
	
};



