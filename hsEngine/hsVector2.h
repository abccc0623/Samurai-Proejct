#pragma once
class hsVector2
{
public:
	int cx;
	int cy;

	

	void zore();
	void up();
	void right();
	void left();
	void down();

	//���ϱ�
	hsVector2 operator+(hsVector2);
	void operator+=(hsVector2);
	//����
	hsVector2 operator-(hsVector2);
	void operator-=(hsVector2);
	//���ϱ�
	hsVector2 operator*(hsVector2);
	void operator*=(hsVector2);


	hsVector2();
	~hsVector2();
private:


};

