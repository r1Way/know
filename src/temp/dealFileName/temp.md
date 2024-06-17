```c++
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
string deal(string str)
{
	int len=str.length();
	int pos=0;
	for(int i=0;i<len;i++)
	{
		if(str[i]=='.')
		{
			pos=i;
		}
	}
	return str.substr(0,pos);
}

int main()
{
	string txtName; 
	cout<<"输入txt名字如file.txt :";
	cin>>txtName; 
	fstream fcin(txtName.c_str(),ios::in);
	string str;
	string category;
	fstream fcout("fileout.txt",ios::app);
	cout<<"输入文件夹名:";
	cin>>category; 
	while(getline(fcin,str))
	{
		fcout<<"    - ["<<deal(str)<<"]("<<category<<"/"<<str<<")"<<"\n";
	}
	return 0;
} 
```

