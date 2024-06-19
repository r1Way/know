#include <iostream>
using namespace std;
class Base
{
public:
    void print()
    {
        cout << "base\n";
    }
};
class Derive : public Base
{
public:
    void print()
    {
    cout<<"derive\n";
    }
};
int main()
{
    Derive d;
    d.Base::print();
    return 0;
}