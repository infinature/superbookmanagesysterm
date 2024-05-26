#ifndef _HEAD_
#define _HEAD_

#include <iostream>
#include <windows.h>
#include <cstring>
#include <fstream>
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <map>
#include <list>

using namespace std;


class User
{
public:
    void addBorrowBook(string& bo)
    {
        borrowbookname.push_back(bo);
    }
    User() :name(""), key(""), borrownum(0), sumbooknum(0){}

    string name;                                //人名
    string key;                                 //登陆密钥
    short iden;                                 //0的话是管理员1的话是借书人
    short borrownum;                            //借书数量
    short sumbooknum;                           //书总数
    vector <string> borrowbookname;             //所借书籍名称
};

void u_SaveData(list<User>&p);//存储数据
list<User> u_LordData ();//读取存储的数据
list<User> addUser();//输入新的用户信息


#endif 