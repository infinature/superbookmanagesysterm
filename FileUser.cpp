#include "head.h"

void u_SaveData(list<User>&p)//存储数据
{
    ofstream fp("userinfo.txt",ios::trunc);//fp为文件指针，写方式
    

    for(list<User>::const_iterator it =p.begin();it!=p.end();it++)//利用迭代器来遍历user的list容器的元素并且输出到文件中
    {
        fp<<endl<<(*it).name<<" ";
        fp<<(*it).key<<" ";
        fp<<(*it).iden<<" ";
        fp<<(*it).borrownum<<" ";
        fp<<(*it).sumbooknum;
    }

    fp.close();
}

list<User> u_LordData ()//读取存储的数据
{
    ifstream fp("userinfo.txt");//读方式
    list<User> p;
    while(fp.peek() != EOF)//peek是看一眼下一个输入是什么但不更改数据
    {
        
        User temp;
        string bookname;

        fp>>temp.name>>temp.key;
        fp>>temp.iden>>temp.borrownum>>temp.sumbooknum;//先把除了借书名字的内容读过来

        int num = temp.borrownum;

        while(num--)
        {
            fp>>bookname;
            temp.borrowbookname.push_back(bookname);//把书名放进user类里的vector
        }
        p.push_back(temp);//把这个赋值好的user放进list

    }
    fp.close();
    return p;
}