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
	
	/*
	���ӿ� ���� ����
	z �뽬
	x ����1
	c ����
	v ����2
	
	�׸��� �����̽�
	*/

	void Update(float time);
private:
	
};

