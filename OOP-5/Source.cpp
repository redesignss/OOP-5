#include <iostream>
using namespace std;
//Проверка механизмов возврата объектов из функции, проверка передачи объектов в функцию

class Base
{
protected:
	int id;
public:
	Base()
	{
		cout << "Base()\n";
		id = 0;
	}
	Base(const Base* object)
	{
		this->id = object->id;
		cout << "Base(Base* object)\n";
	}
	Base(const Base& object)
	{
		this->id = object.id;
		cout << "Base(Base& object)\n";
	}
	virtual string className()
	{
		return "Class Base";
	}
	bool isA(const string& classname)
	{
		return (classname == "Base");
	}
	~Base()
	{
		cout << "~Base()\n";
	}
};

class Desc : public Base
{
public:
	Desc()
	{
		cout << "Desc()\n";
		id = 0;
	}
	Desc(const Desc* object)
	{
		this->id = object->id;
		cout << "Desc(Desc* object)\n";
	}
	Desc(const Desc& object)
	{
		this->id = object.id;
		cout << "Desc(Desc& object)\n";
	}
	string className()
	{
		return "Class Desc";
	}
	bool isA(const string& classname)
	{
		return (classname == "Desc") || Base::isA(classname);
	}
	~Desc()
	{
		cout << "~Desc()\n";
	}
};

//Проверка механизма возврата объектов из функции
Base out1() {
	Base b;
	return b;
}
Base out2() {
	Base* b = new Base();
	return *b;
};
Base* out3() {
	Base b;
	return &b;
};
Base* out4() {
	Base* b = new Base(); //Возможна утечка!
	return b; 
};
Base& out5() {
	Base b;
	return b;
};
Base& out6() {
	Base* b = new Base(); //Возможна утечка!
	return *b;
};


//Проверка передачи объектов в функцию как параметров
void function1(Base object)
{
	cout << "func1(Base object)\n";
}
void function2(Base* object)
{
	cout << "func2(Base* object)\n";
}
void function3(Base& object)
{
	cout << "func3(Base& object)\n";
}

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Проверка передачи объектов в функцию как параметров:\n\n";
	cout << "При статическом создании объектов\n";
	{
		cout << "Base functions:\n";
		Base b1;
		function1(b1);
		function2(&b1);
		function3(b1);
	}
	{
		cout << "\nDesc functions:\n";
		Desc d1;
		function1(d1);
		function2(&d1);
		function3(d1);
	}
	cout << "\n\nПри динамическом создании объектов\n";
	cout << "Base functions:\n";
	Base* b2 = new Base();
	function1(*b2);
	function2(b2);
	function3(*b2);
	delete b2;
	cout << "\nDesc functions:\n";
	Desc* d2 = new Desc();
	function1(*d2);
	function2(d2);
	function3(*d2);
	delete d2;

	cout << "\nПроверка механизмов возврата объекта из функции:\n\n";
	{
		Base b1 = out1();
		cout << endl;
		Base b2 = out2();
		cout << endl;
		Base* b3 = out3();
		cout << endl;
		Base* b4 = out4();
		cout << endl;
		Base& b5 = out5();
		cout << endl;
		Base& b6 = out6();
	}

	return 0;
}