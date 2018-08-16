#pragma once
class Food
{
private:
	short food[4][20];
public:
	Food();
	~Food();
	void Eat(int i, int j);
	bool IsEat(int i, int j);
	void Eated(int i, int j);
	bool IsEated(int i, int j);
};

