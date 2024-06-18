## 未用初始化列表时是否会构造成员对象

* 代码

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

* 输出结果

```shell
construction Memer()
construction Member(int age)
120  destruct
construct Team
120  destruct
```

* 结论

可以看出初始化列表未赋值时，成员变量会调用默认构造函数。