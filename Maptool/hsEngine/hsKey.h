#pragma once
class hsKey
{
public:
	hsKey();
	~hsKey();

	//수평 
	float Horizontal;
	//수직
	float Vertical;

	
	bool Key_F5;
	
	/*
	게임에 사용될 내용
	z 대쉬
	x 공격1
	c 점프
	v 공격2
	
	그림자 스페이스
	*/

	void Update(float time);
private:
	
};

