#ifndef BOOK_H
#define BOOK_H

//#include <bits/stdc++.h>
#include "head.h"
//#include "Index.h"
//#include "User.h"

using namespace std;

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

    Book(){}
    Book(int i):id(i){}
    bool operator==(const Book& other) const
    {
        return id == other.id;
    }
};



list<Book> b_LordData();
void addBook();
void b_SaveData(list<Book>& p);
void b_SaveData_del(list<Book>& p);
void deleteBook();
void lookBook();
void lookBook_0();
void lookBook_1();
void lookBook_2();


#endif //BOOK_H