## 三层继承成员变量生成顺序

```c++
class A{
public:
	A(int a){ cout << "A ctor!" << endl; }
	A(){ cout << "A default ctor!"<< endl; }
	~ A() { cout << "A dtor!" << endl; }
};
class B{
public:
	B(int a, int b){ cout<<"B ctor!"<<endl; }
	B(): m(0) { cout<<"B default ctor!"<<endl;}
	~B(){ cout<<"B dtor!"<<endl;}
private:
	A m;
};
class C: public B{
public:
	C(int a, int b) { cout<<"C ctor!"<<endl; }
	~C(){ cout<<"C dtor!"<<endl;}
private:
	A m;
};
int main()
{
	C obj(0, 0);     
	return 0;
}
```

