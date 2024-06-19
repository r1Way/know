#include <iostream>
using namespace std;
class A
{
public:
	A(int num)
	{
		cout << "construct\n";
		value = num;
	}
	A(const A &a)
	{
		cout << "copy construct\n";
		this->value = a.value;
	}
	A &operator=(A &a)
	{
		cout << "operator=\n";
		this->value = a.value;
		return *this;
	}
	int value;
};

int main()
{
	A a1 = 10;
	return 0;
}
