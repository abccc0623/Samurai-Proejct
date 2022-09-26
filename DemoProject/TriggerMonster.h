#pragma once
class TriggerMonster : public GameObject
{
private:
	float CreateTime;
	int WaveCount;


public:
	TriggerMonster(int PosX, int PosY);
	~TriggerMonster();


	virtual void Update();
	virtual void Render();
	virtual void Debug();
	virtual void init();
	void hit();
};

