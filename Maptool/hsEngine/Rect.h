#pragma once
class hsRect
{
public:
	hsVector2 Center;
	hsRect();
	~hsRect();

	int TOP;
	int BOTTOM;
	int RIGHT;
	int LEFT;

	bool operator==(hsRect rect);
	void SetCenter(int posX, int posY, int Left, int top, int Right, int bottom);
	hsRect GetRect();
private:


};

