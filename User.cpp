#include"head.h"
list<User> addUser()
{
    list<User> p;
    User temp;
    string bookname;
   
        cin>>temp.name;
        cin>>temp.key;
        cin>>temp.iden>>temp.borrownum>>temp.sumbooknum;//先把除了借书名字的内容读过来
        int num = temp.borrownum;
        while(num--)
        {
            cin>>bookname;
            temp.borrowbookname.push_back(bookname);//把书名放进user类里的vector
        }
    p.push_back(temp);//把这个赋值好的user放进list
    
    return p;
}