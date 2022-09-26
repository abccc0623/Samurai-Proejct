#include "pch.h"
#include "MapData.h"

MapData::MapData()
{
   
}

MapData::~MapData()
{


}


void MapData::Save(HWND hwnd)
{
    FILE* fp = NULL;
    fp = fopen("GameData.sav", "wb");
    if (fp == NULL)
    {
        MessageBox(hwnd, L"세이브실패", L"세이브실패", MB_OK);
        return;
    }
   
    
    fwrite(&data, sizeof(int) * 100 * 100, 1, fp);
    fclose(fp);

}

void MapData::Load(HWND hwnd)
{
    FILE* fp = NULL;
    fp = fopen("GameData.sav", "rb");
    if (fp == NULL)
    {
        MessageBox(hwnd, L"로드실패", L"로드실패", MB_OK);
        return;
    }

    Data map;
    fread(&map, sizeof(int) * 100 * 100, 1, fp);
    fclose(fp);

}
