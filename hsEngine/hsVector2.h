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

	//´õÇÏ±â
	hsVector2 operator+(hsVector2);
	void operator+=(hsVector2);
	//»©±â
	hsVector2 operator-(hsVector2);
	void operator-=(hsVector2);
	//°öÇÏ±â
	hsVector2 operator*(hsVector2);
	void operator*=(hsVector2);


	hsVector2();
	~hsVector2();
private:


};

