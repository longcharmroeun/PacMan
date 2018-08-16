#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
	srand(time(NULL));
	x = 0;
	y = 0;
}


Enemy::~Enemy()
{
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			box[i][j].~Box();
		}
	}
}


int Enemy::Check(int x, int y)
{
	int counter = 0;
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (box[0][j] == 0 && box[1][j] == 0 && box[2][j] == 0) return 2;
			else if (box[0][j] == 1 && box[1][j] == 1 && box[2][j] == 1) return 3;
			if (box[i][j] != -1)counter++;
			else counter = 0;
		}
		if (box[i][0] == 0 && box[i][1] == 0 && box[i][2] == 0) return 2;
		else if (box[i][0] == 1 && box[i][1] == 1 && box[i][2] == 1) return 3;
	}
	if (box[0][0] == 0 && box[1][1] == 0 && box[2][2] == 0) return 2;
	else if (box[0][0] == 1 && box[1][1] == 1 && box[2][2] == 1) return 3;
	if (box[0][2] == 0 && box[1][1] == 0 && box[2][0] == 0) return 2;
	else if (box[0][2] == 1 && box[1][1] == 1 && box[2][0] == 1) return 3;
	if (counter >= size * size) return 4;
}

void Enemy::Easy()
{
	int counter = 0;
	while (true) {
		int i = rand() % size;
		int j = rand() % size;
		if (IsEmpty(i,j)) {
			box[i][j].IsNotme();
			break;
		}
		counter++;
		if (counter >= 50) {
			break;
		}
	}
}

int Enemy::Getbox(int i, int j)
{
	return box[i][j];
}

void Enemy::Isme(int i, int j)
{
	box[i][j].Isme();
}

int Enemy::Getsize()
{
	return size;
}

void Enemy::outtext(HWND hwnd)
{
	TCHAR text[100];
	wsprintf(text, TEXT("[%d][%d][%d]  [%d][%d][%d]  [%d][%d][%d]"), box[0][0], box[0][1], box[0][2], box[1][0], box[1][1], box[1][2], box[2][0], box[2][1], box[2][2]);
	SetWindowText(hwnd, text);
	//if (IsCenter())MessageBox(hwnd, TEXT("Center"), 0, 0);
}

void Enemy::Hard()
{
	bool Center = false;
	int counterCenter = 0;
	int counter = 0;
	while (true) {
		if (IsNearWin()) {
			box[x][y].IsNotme();
			break;
		}
		if (IsNearLose()) {
			box[x][y].IsNotme();
			break;
		}
		if (IsFirst()) {
			if (IsEmpty(1, 1)) {
				box[1][1].IsNotme();
				break;
			}
		}
		if (IsCenter()) {
			while (true) {
				int i = rand() % size;
				int j = rand() % size;
				if ((i == 0 || i == 2) && (j == 0 || j == 2)) {
					counterCenter++;
					if (IsEmpty(i, j)) {
						box[i][j].IsNotme();
						Center = true;
						break;
					}
					else if (counterCenter >= 50)break;
				}
			}
		}
		if (Center) break;
		int i = rand() % size;
		int j = rand() % size;
		if (IsEmpty(i, j)) {
			box[i][j].IsNotme();
			break;
		}
		counter++;
		if (counter >= 50) {
			break;
		}
	}
}

bool Enemy::IsNearLose()
{
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++)
		{
			if (box[0][j] == 0 && box[2][j] == 0 && box[1][j] == -1) {
				x = 1;
				y = j;
				return true;
			}
			else if (box[0][j] == 0 && box[1][j] == 0 && box[2][j] == -1) {
				x = 2;
				y = j;
				return true;
			}
			else if (box[1][j] == 0 && box[2][j] == 0 && box[0][j] == -1) {
				x = 0;
				y = j;
				return true;
			}
		}
		if (box[i][0] == 0 && box[i][1] == 0 && box[i][2] == -1) {
			x = i;
			y = 2;
			return true;
		}
		else if (box[i][0] == 0 && box[i][2] == 0 && box[i][1] == -1) {
			x = i;
			y = 1;
			return true;
		}
		else if (box[i][2] == 0 && box[i][1] == 0 && box[i][0] == -1) {
			x = i;
			y = 0;
			return true;
		}
    }
	if (box[0][0] == 0 && box[1][1] == 0 && box[2][2] == -1) {
		x = 2;
		y = 2;
		return true;
	}
	else if (box[0][0] == 0 && box[2][2] == 0 && box[1][1] == -1) {
		x = 1;
		y = 1;
		return true;
	}
	else if (box[2][2] == 0 && box[1][1] == 0 && box[0][0] == -1) {
		x = 0;
		y = 0;
		return true;
	}
	if (box[0][2] == 0 && box[1][1] == 0 && box[2][0] == -1) {
		x = 2;
		y = 0;
		return true;
	}
	else if (box[0][2] == 0 && box[2][0] == 0 && box[1][1] == -1) {
		x = 1;
		y = 1;
		return true;
	}
	else if (box[2][0] == 0 && box[1][1] == 0 && box[0][2] == -1) {
		x = 0;
		y = 2;
		return true;
	}
	return false;
}

bool Enemy::IsFirst()
{
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			if (box[i][j] == 1)return false;
			else if (box[i][j] == 0)return true;
		}
	}
	return false;
}

bool Enemy::IsCenter()
{
	if (box[1][1] == 0)return true;
	else return false;
}

bool Enemy::IsNearWin()
{
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++)
		{
			if (box[0][j] == 1 && box[2][j] == 1 && box[1][j] == -1) {
				x = 1;
				y = j;
				return true;
			}
			else if (box[0][j] == 1 && box[1][j] == 1 && box[2][j] == -1) {
				x = 2;
				y = j;
				return true;
			}
			else if (box[1][j] == 1 && box[2][j] == 1 && box[0][j] == -1) {
				x = 0;
				y = j;
				return true;
			}
		}
		if (box[i][0] == 1 && box[i][1] == 1 && box[i][2] == -1) {
			x = i;
			y = 2;
			return true;
		}
		else if (box[i][0] == 1 && box[i][2] == 1 && box[i][1] == -1) {
			x = i;
			y = 1;
			return true;
		}
		else if (box[i][2] == 1 && box[i][1] == 1 && box[i][0] == -1) {
			x = i;
			y = 0;
			return true;
		}
	}
	if (box[0][0] == 1 && box[1][1] == 1 && box[2][2] == -1) {
		x = 2;
		y = 2;
		return true;
	}
	else if (box[0][0] == 1 && box[2][2] == 1 && box[1][1] == -1) {
		x = 1;
		y = 1;
		return true;
	}
	else if (box[2][2] == 1 && box[1][1] == 1 && box[0][0] == -1) {
		x = 0;
		y = 0;
		return true;
	}
	if (box[0][2] == 1 && box[1][1] == 1 && box[2][0] == -1) {
		x = 2;
		y = 0;
		return true;
	}
	else if (box[0][2] == 1 && box[2][0] == 1 && box[1][1] == -1) {
		x = 1;
		y = 1;
		return true;
	}
	else if (box[2][0] == 1 && box[1][1] == 1 && box[0][2] == -1) {
		x = 0;
		y = 2;
		return true;
	}
	return false;
}


bool Enemy::IsEmpty(int x, int y)
{
	if (box[x][y] == -1)return true;
	else return false;
}
