#include "User.h"

/*********************************************************************************
 * @brief 存储用户数据到文件  
 *  
 * 将给定的User对象链表写入到文件"../data/userinfo.txt"中，数据以追加方式（append mode）写入文件。  
 *  
 * @param p 包含要存储的User对象的链表  
 * @return 无返回值（void）  
 **********************************************************************************/ 
void u_SaveData(list<User>& p)//存储数据
{
    ofstream fp("../data/userinfo.txt", ios::app);//fp为文件指针，写方式

    for (list<User>::const_iterator it = p.begin(); it != p.end(); it++)
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

/*********************************************************************************
 * @brief 覆盖保存用户数据到文件  
 *  
 * 将给定的User对象链表写入到文件"../data/userinfo.txt"中，并覆盖原有文件内容。  
 *  
 * @param p 包含要存储的User对象的链表  
 * @return 无返回值（void）  
 **********************************************************************************/ 
void u_SaveData_del(list<User>& p)//存储数据
{
    ofstream fp("../data/userinfo.txt", ios::trunc);//fp为文件指针，写方式

    for (list<User>::const_iterator it = p.begin(); it != p.end(); it++)
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
/*********************************************************************************
 * @brief 读取存储的用户数据  
 *  
 * 从文件"../data/userinfo.txt"中读取存储的用户数据，并返回User对象的链表。  
 *  
 * @return 包含读取到的User对象的链表  
 **********************************************************************************/ 
list<User> u_LordData()//读取存储的数据
{
    ifstream fp("../data/userinfo.txt");//读方式
    list<User> p;User temp;
        
    while(fp >> temp.name >> temp.key>> temp.type >> temp.id>>temp.borrownum)
    {
       Borrowed_Book t;
       // 跳过其他可能的分隔符或空格
        

        int num = temp.borrownum;
        temp.borrowbook.clear();// 清空temp的borrowbook链表  
        while (num--)
        {
            fp >> t.borrowbookname >>t.id >> t.data;
            temp.borrowbook.push_back(t);
        }
        
        p.push_back(temp);//把这个赋值好的user放进list
        
    }
    fp.close();// 关闭文件流
    return p;// 返回用户链表
}
/*********************************************************************************
 * @brief 添加新用户  
 *  
 * 提示用户输入新用户的信息，并将其保存到文件中。  
 *  
 * @return 无返回值（void）  
 **********************************************************************************/ 
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
/********************************************************************************* 
 * @brief 用户登录  
 *  
 * 提示用户输入用户名和密钥，并检查是否存在于已存储的用户数据中。  
 * 如果存在，则返回对应的User对象。  
 *  
 * @return 登录成功的User对象  
 **********************************************************************************/ 
//输入密码时不显示在屏幕上的辅助函数
string getPassword() {  
    char ch;  
    std::string password = "";  
  
    std::cout << "Enter password: ";  
    while (true) {  
        ch = _getch(); // 不回显地读取一个字符  
        if (ch == 13) // 回车键的ASCII码是13  
            break;  
        std::cout << "*"; // 输出一个星号作为占位符  
        password.push_back(ch);  
    }  
    std::cout << std::endl; // 输出换行符，以便用户可以继续看到命令行的输出  
  
    return password;  
}  
User logIn()
{
    string n,k;
    
    list<User> p =u_LordData();
    
    while(1)
    {
        cout<<"请输入您的用户名："<<endl;
        cin>>n;
        cout<<"请输入您的密码"<<endl;
        k=getPassword();
        for (list<User>::const_iterator it = p.begin(); it != p.end(); it++)
        {

            if((*it).name==n&&(*it).key==k)
            {
                return (*it);
            }
       
        }
    }
}
/*********************************************************************************
 * @brief 查看用户信息  
 *  
 * 遍历用户数据链表，并输出每个用户的详细信息到控制台。  
 *  
 * @return 无返回值（void）  
 **********************************************************************************/
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
/*********************************************************************************
 * @brief 删除用户  
 *  
 * 根据用户名从用户数据链表中删除用户，并将更新后的链表保存到文件中。  
 *  
 * @return 无返回值（void）  
 **********************************************************************************/ 
void deleteUser()
{
    string n;
    cin>>n;
    
    list<User> p =u_LordData();

    for (list<User>::const_iterator it = p.begin(); it != p.end(); it++)
        {
            if((*it).name ==n)
            {
                if((*it).borrownum!=0)
                {
                    cout<<"请先确保账户无借书"<<endl;
                    return;
                }
                p.erase(it);
                break;
            }
        }
    u_SaveData_del(p);

}
/*********************************************************************************
 * @brief 用户借阅书籍  
 *  
 * 将指定书籍信息添加到指定用户的已借阅书籍列表中，并更新用户的借阅数量。  
 * 同时，将更新后的用户数据链表保存（覆盖保存）到文件中。  
 *  
 * @param p 用户对象引用，表示要借阅书籍的用户  
 * @param b 书籍对象，表示被借阅的书籍  
 * @param borrowdata 借阅日期，表示书籍的借阅时间  
 * @return 无返回值（void）  
 **********************************************************************************/
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

int deadline=14;//截止日期
int finenum=0.5;//罚款金额
/*********************************************************************************
 * @brief 用户还书  
 *  
 * 展示指定用户的借阅书籍列表，然后接收用户输入的书名和ID进行还书操作。  
 * 若还书成功，输出罚款金额（如有）并将书籍放回书库。  
 *  
 * @param uk 要还书的用户对象  
 * @return 无返回值（void）  
 **********************************************************************************/ 
void returnBook(User &uk)
{
    // 展示用户借阅的书籍
    if(uk.borrownum==0)
    {
        cout<<"暂无借书捏"<<endl;
        return;
    }
    lookBorrowbook_stu(uk);

    int returnid;
    returnid=getValidIntegerInput("请输入你想还的书的id：");
    // 检查还书ID是否在用户的借书ID列表中
    bool found = false;
    for(auto it =uk.borrowbook.begin();it!=uk.borrowbook.end();++it)
    {
        if(it->id==returnid)
        {
            found=true;
            break;
        }
    }

    // if (!found)
    // {
    //     cout << "错误：你没有借阅ID为 " << returnid << " 的书籍。" << endl;
    //     return;
    // }

    list<User> users = u_LordData();
    for (User& user : users)
    {
        if (uk == user)
        {
            for (auto it = user.borrowbook.begin(); it != user.borrowbook.end(); ++it)
            {
                if (it->id == returnid)
                {
                    // 获取当前日期
                    string returnDate = getCurrentDateTime();
                    int overdueDays = daysBetweenDates(it->data, returnDate) - deadline;
                    if (overdueDays > 0)
                    {
                        cout << "您逾期 " << overdueDays << " 天未还书, 罚款 " << overdueDays*finenum << " 元！" << endl;
                    }
                    else
                    {
                        cout << "您已按期完成还书。" << endl;
                    }

                    // 从用户的借书列表中删除该书
                    user.borrowbook.erase(it);
                    user.borrownum--;
                    break;
                }
            }
        }
    }

    // 保存更新后的用户数据
    u_SaveData_del(users);

    // 更新图书馆库存
    list<Book> books = b_LordData();
    for (Book& book : books)
    {
        if (book.id == returnid)
        {
            book.io_number -= 1;
            book.cur_number += 1;
            break;
        }
    }

    // 保存更新后的图书馆数据
    b_SaveData_del(books);
}
/*********************************************************************************
 * @brief 查看学生借阅的书籍  
 *  
 * 遍历用户数据，查找指定学生（User x）的借阅记录，并输出到控制台。  
 *  
 * @param x 要查看借阅记录的学生对象  
 * @return 无返回值（void）  
 **********************************************************************************/ 
void lookBorrowbook_stu(User x)
{
    list<User> p =u_LordData();
    for (list<User>::const_iterator it = p.begin(); it != p.end(); it++)
    {
        if(x==(*it))
        {
            for (list<Borrowed_Book>::const_iterator it2 = (*it).borrowbook.begin(); it2 != (*it).borrowbook.end(); it2++)//利用迭代器来遍历book的list容器的元素并且输出到文件中
            {
                cout<<(*it2).borrowbookname<<" " <<(*it2).id<<" "<<(*it2).data<<endl;
                
            }
        }
    }
}
/*********************************************************************************
 * @brief 查看所有借阅了书籍的用户及其借阅记录  
 *  
 * 遍历用户数据，查找所有借阅了书籍的用户，并输出他们的借阅记录到控制台。  
 *  
 * @param x 未使用的参数（在此函数中不需要）  
 * @return 无返回值（void）  
 **********************************************************************************/
void lookBorrowbook_man(User x)
{
    
    list<User> p =u_LordData();
    
    for (list<User>::const_iterator it = p.begin(); it != p.end(); it++)//利用迭代器来遍历book的list容器的元素并且输出到文件中
    {
        if((*it).borrownum!= 0){
            for (list<Borrowed_Book>::const_iterator it2 = (*it).borrowbook.begin(); it2 != (*it).borrowbook.end(); it2++)//利用迭代器来遍历book的list容器的元素并且输出到文件中
            {
                cout<<(*it2).borrowbookname<<" " <<(*it2).id<<" "<<(*it2).data<<endl;
            }
        }
    }
}
/*********************************************************************************
 * @brief 修改账户密码 
 *  
 * 修改管理员或用户的账号密码
 *  
 * @param x 用户信息 
 * @return 无返回值（void）  
 **********************************************************************************/
void changePassword(User x)
{
    list<User> p =u_LordData();
    cout<<"请输入原密码："<<endl;
    string n,m;
    cin>>n;
    cout<<"请输入新密码："<<endl;
    cin>>m;
    for (list<User>::iterator it = p.begin(); it != p.end(); it++)
    {
        if((*it).name==x.name&&n==(*it).key)
        {
            (*it).key=m;
            cout<<"修改成功！"<<endl;
        }
        else 
        {
            cout<<"修改失败，原密码错误！"<<endl;
        }
    }
    u_SaveData_del(p);
}