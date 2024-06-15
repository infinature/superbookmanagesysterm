#include "User.h"

void u_SaveData(list<User>& p)//存储数据
{
    ofstream fp("../data/userinfo.txt", ios::app);//fp为文件指针，写方式

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
    ofstream fp("../data/userinfo.txt", ios::trunc);//fp为文件指针，写方式

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
    ifstream fp("../data/userinfo.txt");//读方式
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
void addUser()
{
    list<User> p;
    User temp;
    string bookname;
    Borrowed_Book t;
    cout<<"请输入用户名："<<endl;
        cin>>temp.name;
        cout<<" 请输入新用户密钥"<<endl;
        cin>>temp.key;
        cout<<"请输入新用户类型和id(类型为第一位0或1):"<<endl;
        cin>>temp.type>>temp.id;
        temp.borrownum=0;//先把除了借书名字的内容读过来
    p.push_back(temp);//把这个赋值好的user放进list
    
    u_SaveData(p);
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
void userborrowbook(User& p, Book b,string borrowdata)
{

    Borrowed_Book bb;
    bb.data = borrowdata;
    bb.id = b.id;
    bb.borrowbookname=b.bookname;
     
    list<User> u= u_LordData();
    for (list<User>::iterator it = u.begin(); it != u.end(); it++)
        {
            if((*it) ==p)
            {
                (*it).borrowbook.push_back(bb);   
                (*it).borrownum++;
                break;
            
            }

        }
    u_SaveData_del(u);
}


void returnBook(User uk)
{
    //先展示借书有哪些然后输入书名和id进行还书，最后输出罚款金额并且把所还书放到书库里
    list<string> p=lookBorrowbook_stu(uk);
for (list<string>::const_iterator it = p.begin(); it != p.end(); it++)
    {
        cout<<(*it)<<endl;
    }
    cout<<"请输入你想还的书名和id："<<endl;
    string returnname;
    int returnid;
    
    std::cin>>returnname;
    cin>>returnid;
    list<User> q =u_LordData();
    for (list<User>::iterator it = q.begin(); it != q.end(); it++)//利用迭代器来遍历book的list容器的元素并且输出到文件中
    {
        if(uk==(*it))
        {
            uk.borrowbook=(*it).borrowbook;
            for (list<Borrowed_Book>::iterator it2 = (*it).borrowbook.begin(); it2 != (*it).borrowbook.end(); it2++)//利用迭代器来遍历book的list容器的元素并且输出到文件中
            {
                if((*it2).borrowbookname==returnname&&(*it2).id==returnid)
                {
                    (*it).borrowbook.erase(it2);
                    
                    break;
                }
            }
        }
    }
    u_SaveData_del(q);
    for(list<Borrowed_Book>::const_iterator it = uk.borrowbook.begin(); it != uk.borrowbook.end(); it++)
    {
        if((*it).borrowbookname==returnname&&(*it).id==returnid)
        {
            string returndata=getCurrentDateTime();
            int days=daysBetweenDates((*it).data,returndata);
            if(days>=15)
            cout<<"您逾期 "<<days-14<<" 天未还书,罚款 "<<(days-14)/2<<" 元！"<<endl;
            else
            {
                cout<<"您已按期完成还书。"<<endl;
            }
            uk.borrowbook.erase(it);
            
            list<Book> b =b_LordData();
    for (list<Book>::iterator it2 = b.begin(); it2 != b.end(); it2++)
        {
            if((*it2).bookname ==returnname&&(*it2).id==returnid)
            {
                (*it2).io_number-=1;
                (*it2).cur_number+=1;
                break;
            }
        }
    b_SaveData_del(b);
        }
    }
}
list<string> lookBorrowbook_stu(User x)
{
    list<User> p =u_LordData();
    list<string> a;
    string b;
    for (list<User>::const_iterator it = p.begin(); it != p.end(); it++)//利用迭代器来遍历book的list容器的元素并且输出到文件中
    {
        if(x==(*it))
        {
            for (list<Borrowed_Book>::const_iterator it2 = (*it).borrowbook.begin(); it2 != (*it).borrowbook.end(); it2++)//利用迭代器来遍历book的list容器的元素并且输出到文件中
            {
                b=(*it2).borrowbookname+ " " +to_string((*it2).id)+" "+(*it2).data;
                a.push_back(b);
            }
        }
    }

    return a;
}
list<string> lookBorrowbook_man(User x)
{
    
    list<User> p =u_LordData();
    list<string> a;
    string b;
    for (list<User>::const_iterator it = p.begin(); it != p.end(); it++)//利用迭代器来遍历book的list容器的元素并且输出到文件中
    {
        if((*it).borrownum!= 0){
            for (list<Borrowed_Book>::const_iterator it2 = (*it).borrowbook.begin(); it2 != (*it).borrowbook.end(); it2++)//利用迭代器来遍历book的list容器的元素并且输出到文件中
            {
                b=(*it2).borrowbookname+ " " +to_string((*it2).id)+" "+(*it2).data+" "+(*it).name;
                a.push_back(b);
            }
        }
    }
    return a;
}