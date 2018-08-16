#include "stdafx.h"
#include "Box.h"


Box::Box()
{
	IsMe = -1;
}

Box::operator int()
{
	return IsMe;
}

void Box::Isme()
{
	IsMe = 0;
}

void Box::IsNotme()
{
	IsMe = 1;
}


Box::~Box()
{
	IsMe = -1;
}
