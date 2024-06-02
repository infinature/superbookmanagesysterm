#ifndef _HEAD_
#define _HEAD_

#include <iostream>
#include <windows.h>
#include <cstring>
#include <fstream>
#include <sstream>
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

    Book(){}
    Book(int i):id(i){}
    bool operator==(const Book& other) const
    {
        return id == other.id;
    }
};

class IndexNode     //书名索引的词典节点
{
public:
    char word;        //书名中的词语   
    vector <int> bookid;             //所借书籍序号
    
    IndexNode(){}
    IndexNode(char s):word(s){}
    bool operator==(const IndexNode& other) const
    {
        return word == other.word;
    }
    void addBooks(int i)
    {
        bookid.push_back(i);
    }
};
void DelIndexword(string name,int id);
void userborrowbook(User& p, Book& b,string borrowdata);
vector<int> searchBook(string name);
void b_SaveData(list<Book>& p);//存储数据
void AddIndexword(string name,int id);
void u_SaveData(list<User>& p)//存储数据
{
    ofstream fp("userinfo.txt", ios::app);//fp为文件指针，写方式

    for (list<User>::const_iterator it = p.begin(); it != p.end(); it++)//利用迭代器来遍历user的list容器的元素并且输出到文件中
    {
        fp << (*it).name << " ";
        fp << (*it).key << " ";
        fp << (*it).type << " ";
        fp << (*it).id << " ";
        fp << (*it).borrownum << " ";
        for (list <Borrowed_Book> ::const_iterator a = (*it).borrowbook.begin(); a != (*it).borrowbook.end(); a++)
        {
            fp << (*a).borrowbookname << " "<<(*a).id<<" "<<(*a).data<<" ";
        }
        fp << endl;
    }

    fp.close();
}
void u_SaveData_del(list<User>& p)//存储数据
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
            fp << (*a).borrowbookname << " "<<(*a).id<<" "<<(*a).data<<" ";
        }
        fp << endl;
    }

    fp.close();
}

list<User> u_LordData()//读取存储的数据
{
    ifstream fp("userinfo.txt");//读方式
    list<User> p;User temp;
        
    while(fp >> temp.name >> temp.key>> temp.type >> temp.id>>temp.borrownum)
    {
       Borrowed_Book t;

        ;//先把除了借书名字的内容读过来

        int num = temp.borrownum;
        temp.borrowbook.clear();
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

list<Book> b_LordData()//读取存储的数据
{
    ifstream fp("bookinfo.txt");//读方式
    list<Book> p;
    while (fp.peek() != EOF)//peek是看一眼下一个输入是什么但不更改数据
    {

        Book temp;
        string bookname;

        fp >> temp.id >> temp.sum_number;
        fp >> temp.io_number >> temp.cur_number >> temp.kind>>temp.bookname >> temp.author;
        fp>>temp.publising >> temp.publisingdate;//先把除了借书名字的内容读过来

        
        p.push_back(temp);//把这个赋值好的user放进list

    }
    fp.close();
    return p;
}
list<IndexNode> i_LordData()//读取存储的数据
{
    ifstream fp("index.txt");//读方式
    list<IndexNode> p;
    IndexNode temp;
    string line;  
    vector<int> numbers;  
     while (getline(fp, line))
    {  
        istringstream iss(line);  
        int num;  
        IndexNode temp;
        iss>> temp.word;
        // 尝试从行中读取整数，直到无法读取为止  
        while (iss >> num) 
        {  
            temp.bookid.push_back(num);  
  
            // 尝试读取下一个字符（可能是非整数字符） 
        }  
    }
    fp.close();
    return p;
}
void b_SaveData_del(list<Book>& p)//存储数据
{
    ofstream fp("bookinfo.txt", ios::trunc);//fp为文件指针，写方式

    for (list<Book>::const_iterator it = p.begin(); it != p.end(); it++)//利用迭代器来遍历user的list容器的元素并且输出到文件中
    {
        fp << (*it).id << " ";
        fp << (*it).sum_number << " ";
        fp << (*it).io_number << " ";
        fp << (*it).cur_number << " ";
        fp << (*it).kind << " "<<(*it).bookname<<" "<<(*it).author<<" "<<(*it).publising<<" "<< (*it).publisingdate;
        fp << endl;
    }

    fp.close();
}
void addUser()
{
    list<User> p;
    User temp;
    string bookname;
    Borrowed_Book t;
   
        cin>>temp.name;
        cin>>temp.key;
        cin>>temp.type>>temp.id;
        temp.borrownum=0;//先把除了借书名字的内容读过来
    p.push_back(temp);//把这个赋值好的user放进list
    
    u_SaveData(p);
}
void addBook()
{
    list<IndexNode> L=i_LordData();
    list<Book> p;
    Book temp;
    
    cin>> temp.id >> temp.sum_number;
    cin >> temp.io_number >> temp.cur_number >> temp.kind>>temp.bookname >> temp.author;
    cin>>temp.publising >> temp.publisingdate;
    p.push_back(temp);//把这个赋值好的user放进list
    AddIndexword(temp.bookname,temp.id);//将书添加到词典
    b_SaveData(p);
}
void deleteBook()
{
    string n;
    cin>>n;
    list<IndexNode> L=i_LordData();
    list<Book> p =b_LordData();
    for (list<Book>::const_iterator it = p.begin(); it != p.end(); it++)
        {
            if((*it).bookname ==n)
            {
                DelIndexword((*it).bookname,(*it).id);//词典删除
                p.erase(it);
                break;
            }
        }
    b_SaveData_del(p);

}
User logIn()
{
    string n,k;
    
    list<User> p =u_LordData();
    
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
            cout<< (*a).borrowbookname << " "<<(*a).id<<" "<<(*a).data<<" ";
        }
        cout<< endl;
    }

}
void lookBook()
{
    list<Book> p=b_LordData();
    for (list<Book>::const_iterator it = p.begin(); it != p.end(); it++)
    {
        cout<< (*it).id << " ";
        cout<< (*it).sum_number << " ";
        cout<< (*it).io_number << " ";
        cout<< (*it).cur_number << " ";
        cout<< (*it).kind << " ";
        cout<< (*it).bookname << " ";
        cout<< (*it).author << " ";
        cout<< (*it).publising << " ";
        cout<< (*it).publisingdate << " ";
        cout<< endl;
    }

}
void deleteUser()
{
    string n;
    cin>>n;
    
    list<User> p =u_LordData();
    for (list<User>::const_iterator it = p.begin(); it != p.end(); it++)
        {
            if((*it).name ==n)
            {
                p.erase(it);
                break;
            }
        }
    u_SaveData_del(p);

}



void b_SaveData(list<Book>& p)//存储数据
{
    ofstream fp("bookinfo.txt", ios::trunc);//fp为文件指针，写方式


    for (list<Book>::const_iterator it = p.begin(); it != p.end(); it++)//利用迭代器来遍历book的list容器的元素并且输出到文件中
    {
        fp << (*it).id << " ";
        fp << (*it).sum_number << " ";
        fp << (*it).io_number << " ";
        fp << (*it).cur_number << " ";
        fp << (*it).kind << " " << (*it).bookname << " " << (*it).author << " " << (*it).publising << " " << (*it).publisingdate;
    }

    fp.close();
}
void userborrowbook(User& p, Book& b,string borrowdata)
{

    Borrowed_Book bb;
    bb.data = borrowdata;
    bb.id = b.id;
    bb.borrowbookname=b.bookname;
    p.borrowbook.push_back(bb);    

}
string BorrowBook()
{
    list<IndexNode> L=i_LordData();
    list<Book> p=b_LordData();
    string name;
    int bid;
    User uk;
    string borrowdata;//未定义时间
    vector<int> idList;
    cin>>name;
    idList.clear();
    copy((searchBook(name)).begin(),(searchBook(name)).end(),back_inserter(idList));
    for(vector<int>::iterator it=idList.begin();it !=idList.end();it++) 
    {
        list<Book>::iterator temp = find(p.begin(),p.end(),*it);
        cout<<"name:"<<(*temp).bookname<<" id: "<<(*temp).id<<endl;
    }
    cout<<"输入想借书的id:"<<endl;
    cin>>bid;
    list<Book>::iterator temp = find(p.begin(),p.end(),bid);
    userborrowbook(uk,*temp,borrowdata);
        std::string output = "输出信息"; // 这里应该是BorrowBook函数实际的输出

    return output;
}

void AddIndexword(string name,int id)
{
    list<IndexNode> L=i_LordData();
    for (auto ch : name)         //ch依次取的是str里面的字符,直到取完为止
    {
        IndexNode searchword(ch);//需要删除么
        list<IndexNode>::iterator temp = find(L.begin(),L.end(),searchword);
        if(temp!=L.end())
        {  
            (*temp).addBooks(id);
        }
        else if(temp==L.end())
        {
            (*temp).word=ch;
            (*temp).addBooks(id);
            L.push_back(*temp);
        }
        
    }
}
void DelIndexword(string name,int id)
{
    list<IndexNode> L=i_LordData();
    for (auto ch : name)         //ch依次取的是str里面的字符,直到取完为止
    {
        IndexNode searchword(ch);//需要删除么
        list<IndexNode>::iterator temp = find(L.begin(),L.end(),searchword);
        if(temp!=L.end())
        {  
            ((*temp).bookid).erase(std::remove(((*temp).bookid).begin(),((*temp).bookid).end(),id),((*temp).bookid).end());
        } 
        if(temp==L.end())
        {
            cout<<"无法删除，无存储信息"<<endl;
        }
    }
}
list<IndexNode> BuildIndex()//建立书名词典
{
    list<Book> p=b_LordData();
    list<IndexNode> L;
    //IndexNode temp;
    for(list<Book>::const_iterator it = p.begin();it !=p.end();it++)
    {
        AddIndexword((*it).bookname,(*it).id);
    //     for (auto ch : (*it).bookname)         //ch依次取的是str里面的字符,直到取完为止
    // {
    //     IndexNode searchword(ch);//需要删除么
    //     list<IndexNode>::iterator temp = find(L.begin(),L.end(),searchword);
    //     if(temp!=L.end())
    //     {  
    //         (*temp).addBooks((*it).id);
    //     }
    //     else if(temp==L.end())
    //     {
    //         (*temp).word=ch;
    //         (*temp).addBooks((*it).id);
    //         L.push_back(*temp);
    //     }
        
    // }
    }
    return L;
}
vector<int> searchBook(string name)
{
    list<IndexNode> L=i_LordData();
    vector<int> idList;
    for (auto ch : name)         //ch依次取的是str里面的字符,直到取完为止
    {
        IndexNode searchword(ch);//需要删除么
        list<IndexNode>::iterator temp = find(L.begin(),L.end(),searchword);
        if(temp!=L.end())
        {  
            copy(((*temp).bookid).begin(),((*temp).bookid).end(),idList.end());
        } 
    }
    sort(idList.begin(),idList.end());//默认从小到大
    idList.erase(unique(idList.begin(),idList.end()),idList.end());//去重
    return idList;
}
void i_SaveData()//存储数据
{
    list<IndexNode> p=i_LordData();
    ofstream fp("index.txt", ios::trunc);//fp为文件指针，写方式


    for (list<IndexNode>::const_iterator it = p.begin(); it != p.end(); it++)//利用迭代器来遍历book的list容器的元素并且输出到文件中
    {
        fp << (*it).word << " ";
        for (vector<int>::const_iterator it2 = (*it).bookid.begin(); it2 != (*it).bookid.end(); it2++)
        {
            fp<<(*it2)<<" ";
        }
        fp<<endl;
    }
    

    fp.close();
}

#endif 