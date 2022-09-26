#include "pch.h"

hsVector2::hsVector2()
{
	cx = 0;
	cy = 0;
}

hsVector2::~hsVector2()
{
}

void hsVector2::zore()
{
	cx = 0;
	cy = 0;
}

void hsVector2::up()
{
	cx = 0;
	cy = -1;
}

void hsVector2::right()
{
	cx = 1;
	cy = 0;
}

void hsVector2::left()
{
	cx = -1;
	cy = 0;
}

void hsVector2::down()
{
	cx = 0;
	cy = 1;
}

hsVector2 hsVector2::operator+(hsVector2 vector)
{
	hsVector2 temp;
	temp.cx += vector.cx;
	temp.cy += vector.cy;
	return temp;
}

void hsVector2::operator+=(hsVector2 vector)
{
	cx += vector.cx;
	cy += vector.cy;
}

hsVector2 hsVector2::operator-(hsVector2 vector)
{
	hsVector2 temp;
	temp.cx -= vector.cx;
	temp.cy -= vector.cy;
	return temp;
}

void hsVector2::operator-=(hsVector2 vector)
{
	cx += vector.cx;
	cy += vector.cy;
}

hsVector2 hsVector2::operator*(hsVector2 vector)
{
	hsVector2 temp;
	temp.cx *= vector.cx;
	temp.cy *= vector.cy;
	return temp;
}

void hsVector2::operator*=(hsVector2 vector)
{
	cx *= vector.cx;
	cy *= vector.cy;
}
