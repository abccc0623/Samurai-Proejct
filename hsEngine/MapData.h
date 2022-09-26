#pragma once

struct Data
{
	int SaveMap[50][50];
};

class MapData
{

	Data data;

	MapData();
	~MapData();

	void Save(HWND hwnd);
	void Load(HWND hwnd);

};