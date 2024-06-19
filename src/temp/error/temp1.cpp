#include <iostream>
#include <exception>
using namespace std;
class Error : public runtime_error
{
public:
    Error() : runtime_error("throw error")
    {
    }
};
void func()
{
    throw Error();
}

int main()
{
    try
    {
        func();
    }
    catch (runtime_error &error)
    {
        cout<<"runtime_error error\n";
    }
    catch (Error &error)
    {
        cout<<"Error error\n";
    }
    catch (...)
    {
        cout<<"... error\n";
    }
    return 0;
}