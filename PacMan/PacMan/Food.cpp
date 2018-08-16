#include "stdafx.h"
#include "Food.h"


Food::Food()
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 20; j++)
		{
			food[i][j] = -1;
		}
	}
}


Food::~Food()
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 20; j++)
		{
			food[i][j] = -1;
		}
	}
}

void Food::Eat(int i, int j)
{
	food[i][j] = 1;
}

bool Food::IsEat(int i, int j)
{
	if (food[i][j] == 1)return true;
	else return false;
}

void Food::Eated(int i, int j)
{
	food[i][j] = 0;
}

bool Food::IsEated(int i, int j)
{
	if (food[i][j] == 0)return true;
	else return false;
}
