#include <iostream>
#include <memory>

//unique и shared point - умные указатели
using namespace std;

class Base {
public:
	Base() {
		printf("Base()\n");
	}
	Base(Base* object) {
		printf("Base(Base *object)\n");
	}
	Base(Base& object) {
		printf("Base(Base &object)\n");
	}
	Base(const Base& object) {
		printf("Base(const Base &object)\n");
	}
	virtual ~Base() {
		printf("~Base()\n");
	}
	void someMethod() {
		std::cout << "someMethod()" << std::endl;
	}
};

void Func1(unique_ptr<Base> ptr) {
	cout << "Func1(unique_ptr<Base> ptr)" << std::endl;
	ptr->someMethod();
}

void Func1(shared_ptr<Base> ptr) {
	cout << "Func1(shared_ptr<Base> ptr)" << std::endl;
	ptr->someMethod();
}

shared_ptr<Base> Func2() {
	cout << "shared_ptr<Base> Func1()" << endl;
	return make_shared<Base>();
}

int main() {
	setlocale(LC_ALL, "RUS");

	printf("Создаем объект класса с указателем unique_ptr\n");
	unique_ptr<Base> uniquePtr(new Base);

	//Func1(uniquePtr);// нельзя передавать по значению
	//unique_ptr<Base> uniquePtr2 = uniquePtr; нельзя скопировать, ошибка

	printf("\nПередаем uniquePtr объект класса в функцию\n");
	Func1(move(uniquePtr));

	printf("\nСоздаем объект класса с указателем shared_ptr с помощью функции\n");
	shared_ptr<Base> sharedPtr = Func2();

	printf("\nПередаем sharedPtr объект класса в функцию\n");
	Func1(move(sharedPtr));


	printf("\nСоздаем объект класса с указателем shared_ptr\n");
	shared_ptr<Base> sharedPtr1(new Base);
	printf("\nСоздаем второй объект класса с указателем shared_ptr, помещая туда первый объект\n");
	shared_ptr<Base> sharedPtr2 = sharedPtr1;
	printf("\nСоздаем третий объект класса с указателем shared_ptr, помещая туда первый объект\n");
	shared_ptr<Base> sharedPtr3 = sharedPtr1;
	printf("\nВызываем метод объекта класса shared_ptr1\n");
	sharedPtr1->someMethod();

	printf("\nВызываем reset у shared_ptr1\n");
	sharedPtr1.reset();

	printf("\nВызываем reset у shared_ptr2\n");
	sharedPtr2.reset();

	printf("\nВызываем reset у shared_ptr3\n");
	sharedPtr3.reset();

	return 0;
}