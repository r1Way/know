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
	fstream fcin("file.txt",ios::in);
	string str;
	fstream fcout("fileout.txt",ios::app);
	while(getline(fcin,str))
	{
		fcout<<"["<<deal(str)<<"](ideas"<<char(47)<<str<<")"<<"\n";
	}
	return 0;
} 
