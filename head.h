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
class Borrowed_Book
{
public:
    string data;
    int id;
    string borrowbookname;
};



class User
{
public:
    void addBorrowBook(Borrowed_Book& b)
    {
        borrowbook.push_back(b);
    }
    User() :name(""), key(""), borrownum(0){}

    string name;                                //人名
    string key;                                 //登陆密钥
    string id;                                  //借书证号及学号
    short type;                                 //0的话是管理员1的话是借书人
    short borrownum;                            //借书数量                    
    list<Borrowed_Book> borrowbook;             //所借书籍名称
};
void adduser();

class   Book
{
public:
    int price;       //价格
    int id;    //在书库里的序号
    int sum_number;     //总数量
    int io_number;      //借出数量
    int cur_number;         //当前数量
    string bookname;        //书名
    string author;      //作者
    string publising;       //出版社
    string publisingdate;       //出版日期
    string kind;        //类别0为书籍1为期刊2为报刊
};



#endif 