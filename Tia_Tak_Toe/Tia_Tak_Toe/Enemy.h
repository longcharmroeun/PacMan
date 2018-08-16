#pragma once
#include "Box.h"
#include <cstdlib>
#include <ctime>

class Enemy
{
public:
	Enemy();
	~Enemy();
private:
	const static int size = 3;
	Box box[size][size];
	int x, y;
public:
	bool IsEmpty(int, int y);
	int Check(int x = 0, int y = 0);
	void Easy();
	int Getbox(int i = 0, int j = 0);
	void Isme(int i = 0, int j = 0);
	int Getsize();
	void outtext(HWND hwnd);
	void Hard();
	bool IsNearLose();
	bool IsFirst();
	bool IsCenter();
	bool IsNearWin();
};

