#pragma once
class hsKey
{
public:
	hsKey();
	~hsKey();

	//���� 
	float Horizontal;
	//����
	float Vertical;


	
	bool Key_F5;
	
	

	bool isCurrent[256];
	bool isPrev[256];


	bool KeyDown(int keynum);
	bool KeyUP(int keynum);
	void Update(float time);
private:
	
};

