#include "stdafx.h"
#include "Food1.h"


Food1::Food1()
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			food[i][j] = -1;
		}
	}
}


Food1::~Food1()
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			food[i][j] = -1;
		}
	}
}

bool Food1::IsEat(int i ,int j)
{
	if (food[i][j] == 1)return true;
	else return false;
}

void Food1::Eat(int i, int j)
{
	food[i][j] = 1;
}

void Food1::Eated(int i, int j)
{
	food[i][j] = 0;
}

bool Food1::IsEated(int i, int j)
{
	if (food[i][j] == 0)return true;
	else return false;
}



