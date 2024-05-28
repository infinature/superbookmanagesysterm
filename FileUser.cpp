#include "head.h"

void u_SaveData(list<User>&p)
{
    ofstream fp("userinfo.txt",ios::trunc);
    

    int length = p.size();


    for(list<User>::const_iterator it =p.begin();it!=p.end();it++)
    {
         fp<<endl<<(*it).name<<" ";
        fp<<(*it).key<<" ";
        fp<<(*it).type<<" ";
        fp<<(*it).borrownum<<" ";
        fp<<(*it).sumbooknum;
        int booknum = (*it).borrowbookname.size();

      
    }

    fp.close();
}

list<User> u_LordData ()
{
    ifstream fp("userinfo.txt");
    list<User> p;
    while(fp.peek() != EOF)
    {
        

        User temp;

        string bookname;

        fp>>temp.name>>temp.key;
        fp>>temp.iden>>temp.borrownum>>temp.sumbooknum;

        int num = temp.borrownum;

        while(num--)
        {
            fp>>bookname;
            temp.borrowbookname.push_back(bookname);
        }
        p.push_back(temp);

    }
    fp.close();
    return p;
}