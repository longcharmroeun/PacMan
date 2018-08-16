#pragma once
class Food1
{

private:
	short food[3][3];
public:
	Food1();
	~Food1();
	bool IsEat(int i ,int j);
	void Eat(int i, int j);
	void Eated(int i, int j);
	bool IsEated(int i, int j);
};

