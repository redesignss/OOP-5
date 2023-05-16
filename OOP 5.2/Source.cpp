#include <iostream>
using namespace std;


//static и dynamic cast + isA



class ClassA
{
public:
	ClassA()
	{
		printf("ClassA()\n");
	}
	string className() //Плохой метод (нарушение инкапсуляции) 
	{
		return "Class ClassA";
	}
	virtual bool isA(const string& classname)
	{
		return classname == "ClassA";
	}
	virtual ~ClassA()
	{
		printf("~ClassA()\n");
	}
};

class ClassB : public ClassA
{
public:
	ClassB()
	{
		printf("ClassB()\n");
	}
	string className() //Плохой метод (нарушение инкапсуляции)
	{
		return "Class ClassB";
	}
	bool isA(const string& classname)
	{
		return (classname == "ClassB") || ClassA::isA(classname);
	}
	void BFunc()
	{
		printf("do BFunc\n");
	}
	~ClassB()
	{
		printf("~ClassB()\n");
	}
};

class ClassC : public ClassB
{
public:
	ClassC()
	{
		printf("ClassC()\n");
	}
	bool isA(const string& classname)
	{
		return (classname == "ClassC") || ClassB::isA(classname);
	}
};

int main()
{
	const int ARR_SIZE = 10;
	ClassA* arr[ARR_SIZE];
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	printf("Создание объектов:\n");
	for (int i = 0; i < ARR_SIZE; i++)
	{
		int r = rand() % 3;
		if (r == 0)
			arr[i] = new ClassA();
		else if (r == 1)
			arr[i] = new ClassB();
		else if (r == 2)
			arr[i] = new ClassC();
		cout << endl;
	}

	printf("\nВызов функций с static_cast\n");
	for (int i = 0; i < ARR_SIZE; i++)
	{
		if (arr[i]->isA("ClassB")) //"являющийся (под)классом определенного типа"
			static_cast<ClassB*>(arr[i])->BFunc(); //статическое преобразование
	}
	printf("\nВызов функций с dynamic_cast\n");
	for (int i = 0; i < ARR_SIZE; i++)
	{
		ClassB* b = dynamic_cast<ClassB*>(arr[i]); //динамическое преобразоание
		if (b != nullptr)
			b->BFunc();
	}
	return 0;
}

