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
void userborrowbook(User& p, Book& b,string borrowdata);
void u_SaveData(list<User>& p)//存储数据
{
    ofstream fp("userinfo.txt", ios::trunc);//fp为文件指针，写方式


    for (list<User>::const_iterator it = p.begin(); it != p.end(); it++)//利用迭代器来遍历user的list容器的元素并且输出到文件中
    {
        fp << (*it).name << " ";
        fp << (*it).key << " ";
        fp << (*it).type << " ";
        fp << (*it).id << " ";
        fp << (*it).borrownum << " ";
        for (list <Borrowed_Book> ::const_iterator a = (*it).borrowbook.begin(); a != (*it).borrowbook.end(); a++)
        {
            fp << (*a).borrowbookname << " "<<(*a).id<<" "<<(*a).data;
        }
        fp << endl;
    }

    fp.close();
}

list<User> u_LordData()//读取存储的数据
{
    ifstream fp("userinfo.txt");//读方式
    list<User> p;
    while (fp.peek() != EOF)//peek是看一眼下一个输入是什么但不更改数据
    {

        User temp;
        Borrowed_Book t;

        fp >> temp.name >> temp.key;
        fp >> temp.type >> temp.id>>temp.borrownum;//先把除了借书名字的内容读过来

        int num = temp.borrownum;

        while (num--)
        {
            fp >> t.borrowbookname >>t.id >> t.data;//把书名放进user类里的list
            temp.borrowbook.push_back(t);
        }
        
        p.push_back(temp);//把这个赋值好的user放进list

    }
    fp.close();
    return p;
}

void addUser()
{
    list<User> p;
    User temp;
    string bookname;
    Borrowed_Book t;
   
        cin>>temp.name;
        cin>>temp.key;
        cin>>temp.type>>temp.id>>temp.borrownum;//先把除了借书名字的内容读过来
        int num = temp.borrownum;

        while (num--)
        {
            cin >> t.borrowbookname >>t.id >> t.data;//把书名放进user类里的list
            temp.borrowbook.push_back(t);
        }
    p.push_back(temp);//把这个赋值好的user放进list
    
    u_SaveData(p);
}
User logIn()
{
    string n,k;
    
    list<User> p =u_LordData();
    bool flag=false;;
    while(1)
    {
        cin>>n>>k;
        for (list<User>::const_iterator it = p.begin(); it != p.end(); it++)
        {

            if((*it).name==n&&(*it).key==k)
            {
                return (*it);
            }
       
        }
    }
}
void lookUser()
{
    list<User> p=u_LordData();
    for (list<User>::const_iterator it = p.begin(); it != p.end(); it++)
    {
        cout<< (*it).name << " ";
        cout<< (*it).key << " ";
        cout<< (*it).type << " ";
        cout<< (*it).id << " ";
        cout<< (*it).borrownum << " ";
        for (list <Borrowed_Book> ::const_iterator a = (*it).borrowbook.begin(); a != (*it).borrowbook.end(); a++)
        {
            cout<< (*a).borrowbookname << " "<<(*a).id<<" "<<(*a).data;
        }
        cout<< endl;
    }

}




#endif 