#pragma once

class GameObject
{
public:
	hsVector2	Pos;			//객체의 위치
	hsRect		Collider;		//충돌범위

	//이객체 랜더링중인지
	bool isRender;
	//이객체가 디버깅상태인지
	bool isDebug;
	//이객체를 지울것인지
	bool isDelete;
	//이겍체가 충돌체 인지
	bool isCollider;
	//충돌했는지
	bool ishit;
	

	
	GameObject();
	virtual ~GameObject();
	virtual void Update()	=0;
	virtual void Render()	=0;
	virtual void Debug()	=0;
	virtual void init()		=0;
};

