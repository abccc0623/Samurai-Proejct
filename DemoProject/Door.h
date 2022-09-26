#pragma once
class Door:public GameObject
{
public:

	bool Next;
	hsSprite img;
	Door(hsSprite m_img);
	virtual~Door();
	virtual void Update();
	virtual void Render();
	virtual void Debug();
	virtual void init();
};

