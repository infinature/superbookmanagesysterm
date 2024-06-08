#ifndef _USER_H
#define _USER_H

//#include <bits/stdc++.h>
#include "head.h"

using namespace std;
class Book;
// class Borrowed_Book
// {
// public:
//     string data;
//     int id;
//     string borrowbookname;
// };
class Borrowed_Book
{
public:
    Borrowed_Book(){}
    string data;
    int id;
    string borrowbookname;
};
class User
{
public:
User(){}
User(string name,string key,string id,short type,short borrownum)
{
    this->name=name;
    this->key=key;
    this->id=id;
    this->type=type;
    this->borrownum=borrownum;
}
    bool operator==(const User& other) const
    {
        return (id == other.id)&&(name==other.name);
    }

    string name;                                //人名
    string key;                                 //登陆密钥
    string id;                                  //借书证号及学号
    short type;                                 //0的话是管理员1的话是借书人
    short borrownum;                            //借书数量                    
    list<Borrowed_Book> borrowbook;             //所借书籍名称
};


void userborrowbook(User& p, Book b,string borrowdata);

void u_SaveData(list<User>& p);
list<User> u_LordData();
void addUser();
User logIn();
void lookUser();
void deleteUser();
void returnBook(User uk);
list<string> lookBorrowbook_stu(User x);
list<string> lookBorrowbook_man(User x);
#endif //_USER_H