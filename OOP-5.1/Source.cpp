//Виртуальные и невиртуальные методы, виртуальный деструктор

#include <iostream>
using namespace std;

class Animal
{
private:
	string name;
public:
	void sound_notvirt()
	{
		printf("basemethod\n");
	}
	virtual void sound_virt()
	{
		printf("basemethod\n");
	}
};

class Cat : public Animal
{
public:
	void sound_notvirt()
	{
		printf("Mew-mew\n");
	}
	void sound_virt()
	{
		cout << "Mew-mew\n";
	}
	void CatchMouse()
	{

	}
};

class Dog : public Animal
{
public:
	void sound_notvirt()
	{
		printf("Wow-wow\n");
	}
	void sound_virt()
	{
		cout << "Wow-wow\n";
	}
	void ChaseCat()
	{

	}
};


class Base
{
public:
	Base()
	{
		printf("Base()\n");
	}
	virtual ~Base()
	{
		printf("~Base()\n");
	}
};

class Desc : public Base
{
private:
	int* arr;
public:
	Desc()
	{
		arr = new int[50];
		printf("Desc()\n");
	}
	~Desc() override
	{
		delete arr;
		printf("~Desc()\n");
	}
};


int main()
{
	setlocale(LC_ALL, "Russian");
	const int ZOO_SIZE = 10;
	Animal* zoo[ZOO_SIZE];
	for (int i = 0; i < ZOO_SIZE; i++)
	{
		int r = rand() % 2;
		if (r == 0)
			zoo[i] = new Cat();
		else if (r == 1)
			zoo[i] = new Dog();
	}
	printf("Вызов невиртуальных методов:\n");
	//Вызов невиртуальных методов
	for (int i = 0; i < ZOO_SIZE; i++)
	{
		zoo[i]->sound_notvirt();
	}
	printf("\nВызов виртуальных методов:\n");
	//Вызов виртуальных методов
	for (int i = 0; i < ZOO_SIZE; i++)
	{
		zoo[i]->sound_virt();
	}

	printf("Пример использования виртуального деструктора\n");
	//Пример использования виртуального деструктора
	Base* x = new Desc();
	delete x;

	return 0;
}