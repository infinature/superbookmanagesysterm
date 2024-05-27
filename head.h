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
class   Book
{
public:
    int cost;       //价格
    int sum_number;     //总数量
    int io_number;      //借出数量
    string bookname;        //书名
    string author;      //作者
    string publising;       //出版社
    string publisingdate;       //出版日期
    string kind;        //类别
    string isbn;        //编号
    Book* prior;//前一个结点
    Book* p_next;//后一个结点
};

class BookList
{
public:
    BookList()//默认构造函数
    {
        this->m_head = new Book;
		this->m_head->prior = m_head;//头结点指向指针
		this->m_head->p_next = NULL;
    }

    ~BookList(); //析构函数  需要把链表中所有结点占用的空间都释放掉

    BookList(int &n);//有参构造

    int getlistsize();//获取该链表的长度
 
	void traverselist();//遍历链表
 
	void insertnode(int  position, int  date);//在链表的指定位置插入结点
 
	void deletenode(int position);//要删除的结点位置
private:
	Book* m_head;
};
BookList::BookList(int& n)//n代表创建链表是插入结点的个数
{
	//首先创建一个头结点，注意如果调用有参构造，就不会调用无参构造
	this->m_head = new Book;
	this->m_head->prior = m_head;
	this->m_head->p_next = NULL;
 
	Book* pnew;//用来存放新结点的值
	Book* ptemp;//这个结点的作用见下面的注释
	ptemp = this->m_head;//头结点
	int i = n;
	while (i--)
	{
		pnew = new Book;//开辟在堆区
		pnew->prior = ptemp;
		//默认的头结点为第0个结点（指针指向第一个结点，头结点无数据）
		// cout << "请输入第" << n - i << "个结点的值" << endl;
		// cin >> pnew->date;
		pnew->p_next = m_head;//最后一个指向头结点
		ptemp->p_next = pnew;
		//ptemp这个结点的作用是一直作为链表最后一个结点
		ptemp = pnew;
	}
	m_head->prior = ptemp;
}
 
//获取链表的长度(头结点不算)
int BookList::getlistsize()
{
	int count = 0;
	int flag = 0;
	Book* p = this->m_head;
	while ((p->p_next != m_head)||flag==0)
	{
		flag = 1;
		count++;
		p = p->p_next;
	}
	return count;
}
//遍历操作 后续添加操作
void BookList::traverselist()
{
	Book* p = this->m_head;
	int flag = 0;
	int i = 0;
	while ((p->p_next != m_head)||flag==0)
	{
		flag = 1;
		//cout << "第" << ++i << "个结点的值为： " << p->p_next->date << endl;
		p = p->p_next;
	}
}
 
//在指定的位置后插入结点
void BookList::insertnode(int  position, int date)
{
	//position代表在第几个结点后面插入新结点
	int len = getlistsize();
	//判断一下插入的位置是否大于现有链表的长度
	if ((position > len) || position < 0)//这里position和len都可以为0
	{
		cout << "插入位置非法！" << endl;
		exit(0);
	}
	else
	{
		Book* pnew = new Book;//要插入的结点
		Book* ptemp = NULL;//
		ptemp = this->m_head;
		//pnew->date = date;
		for (int i = 0; i < position; i++)
		{
			ptemp = ptemp->p_next;//找到要插入的结点位置
		}
		//下面两行是pnew的前后指向
		pnew->prior = ptemp;
		pnew->p_next = ptemp->p_next;
 
		ptemp->p_next->prior = pnew;//
 
		ptemp->p_next = pnew;
	}
}
 
//删除指定的结点
void BookList::deletenode(int position)
{
	int len = getlistsize();
	if ((position > len) || position <= 0)//len都可以为0
	{
		cout << "删除位置非法！" << endl;
		exit(0);
	}
	else
	{
		Book* p = this->m_head;
		for (int i = 0; i < position - 1; i++)
		{
			p = p->p_next;//找到要删除结点的前一个结点
		}
		Book* p1 = p->p_next;//记录要删除的结点
 
		p->p_next->p_next->prior = p;
 
		p->p_next = p->p_next->p_next;
 
		delete p1;
	}
}
 
//析构函数，释放链表占用的空间
BookList::~BookList()
{
	Book* ptemp1=m_head->p_next;//用来记录要删除的结点
	Book* ptemp2=m_head->p_next;//用来遍历链表
	while ((ptemp2 != m_head) )
	{
		ptemp1 = ptemp2;
		ptemp2 = ptemp2->p_next;
		delete ptemp1;
	}
	delete m_head;//释放头结点
}

class IndexNode     //书名索引的词典节点
{
public:
    string word;        //书名中的词语
    IndexNode* prior;//前一个结点
    IndexNode* p_next;//后一个结点
};
class Index
{
public:
    
};

// User 类定义，用于存储用户信息
class User {
public:
    void addBorrowBook(string& bo) {
        borrowbookname.push_back(bo); // 向所借书籍名称的向量中添加书籍
    }
    User() : name(""), key(""), type(0), borrownum(0), sumbooknum(0), next(nullptr) {}
    
    string name; // 用户名
    string key; // 登录密钥
    short type; // 用户类型，0为管理员，1为普通用户
    short borrownum; // 已借书籍数量
    short sumbooknum; // 书籍总数
    vector<string> borrowbookname; // 所借书籍名称的列表
    User* next; // 指向下一个User对象的指针，用于创建链表
};





#endif 