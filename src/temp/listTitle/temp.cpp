#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;
int main()
{
    string filename;// example: file1, temp1
    cout<<"请输入文件名字，如:temp1  :";
    cin>>filename;
    ifstream fcin(filename.c_str(),ios::in);
    if(!fcin.fail())
    {
        cout<<"open fail\n";
    }
    cout<<"hello world\n";
    vector<string> titles;
    vector<string> draft;
    string temp;
    while(getline(fcin,temp))
    {
        draft.push_back(temp);
        if(temp[0]=='#')
        {
            titles.push_back(temp);
        }
    }
    
    ofstream fcout("titles.txt",ios::out);
    for(auto &it:titles)
    {
        fcout<<it<<"\n";
    }
    return 0;
}