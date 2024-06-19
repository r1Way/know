#include <iostream>
using namespace std;
class Base
{
public:
    Base(int v)
    {
        value = v;
    }

protected:
    int value;
};
class Derive : public Base
{
public:
    Derive(int v) : Base(v)
    {
    }
};

int main()
{
    Base b1(2);
    Derive d1(10);
    cout<<d1.value;
    return 0;
}