#include "head.h"


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
