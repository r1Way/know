## 未用初始化列表时是否会构造成员对象

```c++
#include <iostream>
using namespace std;
class Member
{
public:
    Member()
    {
        age=0;
        cout << "construction Memer()\n";
    }
    Member(int age)
    {
        this->age=age;
        cout << "construction Member(int age)\n";
    }
    ~Member()
    {
        cout<<age<<"  destruct\n";
    }
    int age;
};
class Team
{
public:
    Team()
    {
        m = Member(120);
        cout << "construct Team\n";
    }
    Member m;
};
int main()
{
    Team t;
    return 0;
}
```