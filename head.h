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
#include <iomanip> 


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
User(string name,string key,string id,short type,short borrownum)
{
    this->name=name;
    this->key=key;
    this->id=id;
    this->type=type;
    this->borrownum=borrownum;
}



    void addBorrowBook(Borrowed_Book& b)
    {
        borrowbook.push_back(b);
    }
    User() :name(""), key(""), borrownum(0){}
    bool operator==(const User& other) const
    {
        return (id == other.id)&&(name==other.name);
    }

    string name;                                //人名
    string key;                                 //登陆密钥
    string id;                                  //借书证号及�?�号
    short type;                                 //0的话�?管理�?1的话�?借书�?
    short borrownum;                            //借书数量                    
    list<Borrowed_Book> borrowbook;             //所借书籍名�?
};


class   Book
{
public:
    int price;       //价格
    int id;    //在书库里的序�?
    int sum_number;     //总数�?
    int io_number;      //借出数量
    int cur_number;         //当前数量
    string bookname;        //书名
    string author;      //作�?
    string publising;       //出版�?
    string publisingdate;       //出版日期
    string kind;        //类别0为书�?1为期�?2为报�?

    Book(){}
    Book(int i):id(i){}
    bool operator==(const Book& other) const
    {
        return id == other.id;
    }
};

class IndexNode     //书名索引的词典节�?
{
public:
    char word;        //书名�?的词�?   
    vector <int> bookid;             //所借书籍序�?
    
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
vector<int> searchBook(const string& name);
void b_SaveData(list<Book>& p);//存储数据
void AddIndexword(const string &name,int id,list<IndexNode>& L);
void u_SaveData(list<User>& p)//存储数据
{
    ofstream fp("userinfo.txt", ios::app);//fp为文件指针，写方�?

    for (list<User>::const_iterator it = p.begin(); it != p.end(); it++)//利用�?代器来遍历user的list容器的元素并且输出到文件�?
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
    ofstream fp("userinfo.txt", ios::trunc);//fp为文件指针，写方�?

    for (list<User>::const_iterator it = p.begin(); it != p.end(); it++)//利用�?代器来遍历user的list容器的元素并且输出到文件�?
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

list<User> u_LordData()//读取存储的数�?
{
    ifstream fp("userinfo.txt");//读方�?
    list<User> p;User temp;
        
    while(fp >> temp.name >> temp.key>> temp.type >> temp.id>>temp.borrownum)
    {
       Borrowed_Book t;

        ;//先把除了借书名字的内容�?�过�?

        int num = temp.borrownum;
        temp.borrowbook.clear();
        while (num--)
        {
            fp >> t.borrowbookname >>t.id >> t.data;//把书名放进user类里的list
            temp.borrowbook.push_back(t);
        }
        
        p.push_back(temp);//把这�?赋值好的user放进list
        
    }
    fp.close();
    return p;
}

list<Book> b_LordData()//读取存储的数�?
{
    ifstream fp("bookinfo.txt");//读方�?
    list<Book> p;
    Book temp;
        string bookname;
    while (fp >> temp.id)//peek�?看一眼下一�?输入�?什么但不更改数�?
    {

        

         fp>> temp.sum_number;
        fp >> temp.io_number >> temp.cur_number >> temp.kind>>temp.bookname >> temp.author;
        fp>>temp.publising >> temp.publisingdate;//先把除了借书名字的内容�?�过�?

        
        p.push_back(temp);//把这�?赋值好的user放进list

    }
    fp.close();
    return p;
}
list<IndexNode> i_LordData()//读取存储的数�?
{
    ifstream fp("index.txt");//读方�?
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
        // 尝试从�?�中读取整数，直到无法�?�取为�??  
        while (iss >> num) 
        {  
            temp.bookid.push_back(num);  
  
            // 尝试读取下一�?字�?�（�?能是非整数字符） 
        }  
        p.push_back(temp);
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
        cin>>temp.type>>temp.id;
        temp.borrownum=0;//先把除了借书名字的内容�?�过�?
    p.push_back(temp);//把这�?赋值好的user放进list
    
    u_SaveData(p);
}
void addBook()
{
    list<Book> p;
    Book temp;
    
    cin>> temp.id >> temp.sum_number;
    cin >> temp.io_number >> temp.cur_number >> temp.kind>>temp.bookname >> temp.author;
    cin>>temp.publising >> temp.publisingdate;
    p.push_back(temp);//把这�?赋值好的user放进list
    list<IndexNode> L = i_LordData(); // 加载现有的索引数�?
    AddIndexword(temp.bookname, temp.id, L); // 将书添加到词�?
    b_SaveData(p);
}
void b_SaveData_del(list<Book>& p)//存储数据
{
    ofstream fp("bookinfo.txt", ios::trunc);//fp为文件指针，写方�?


    for (list<Book>::const_iterator it = p.begin(); it != p.end(); it++)//利用�?代器来遍历book的list容器的元素并且输出到文件�?
    {
        fp << (*it).id << " ";
        fp << (*it).sum_number << " ";
        fp << (*it).io_number << " ";
        fp << (*it).cur_number << " ";
        fp << (*it).kind << " " << (*it).bookname << " " << (*it).author << " " << (*it).publising << " " << (*it).publisingdate;
        fp<<endl;
    }

    fp.close();
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
    ofstream fp("bookinfo.txt", ios::app);//fp为文件指针，写方�?


    for (list<Book>::const_iterator it = p.begin(); it != p.end(); it++)//利用�?代器来遍历book的list容器的元素并且输出到文件�?
    {
        fp << (*it).id << " ";
        fp << (*it).sum_number << " ";
        fp << (*it).io_number << " ";
        fp << (*it).cur_number << " ";
        fp << (*it).kind << " " << (*it).bookname << " " << (*it).author << " " << (*it).publising << " " << (*it).publisingdate;
        fp<<endl;
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
vector<int> searchBook(const string& name)
{
    list<IndexNode> L = i_LordData();
    vector<int> idList;
    for (auto ch : name) // ch依�?�取的是str里面的字�?,直到取完为�??
    {
        IndexNode searchword(ch);
        auto temp = find(L.begin(), L.end(), searchword);
        if (temp != L.end())
        {
            copy((*temp).bookid.begin(), (*temp).bookid.end(), back_inserter(idList));
        }
    }
    sort(idList.begin(), idList.end()); // 默�?�从小到大排�?
    idList.erase(unique(idList.begin(), idList.end()), idList.end()); // 去重
    return idList;
}
string getCurrentDateTime() {  
     // 获取当前时间（�?�自�?1970-01-01 00:00:00 UTC�?
    time_t rawtime;
    time(&rawtime);
    
    // �?�?为本地时�?
    struct tm * timeinfo = localtime(&rawtime);
    
    // 使用stringstream来构造日期字符串
    std::ostringstream oss;
    oss << (timeinfo->tm_year + 1900)
    << std::setfill('0') << std::setw(2) << (timeinfo->tm_mon + 1)
    << std::setfill('0') << std::setw(2) << timeinfo->tm_mday;
    
    return oss.str();
}

int daysBetweenDates(const std::string& date1, const std::string& date2) {
    // 将字符串�?�?为tm结构�?
    std::tm tm1 = {}, tm2 = {};
    std::istringstream ss1(date1), ss2(date2);
    ss1 >> std::get_time(&tm1, "%Y%m%d");
    ss2 >> std::get_time(&tm2, "%Y%m%d");

    // �?�?为time_t类型
    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);

    // 计算时间�?并转�?为天�?
    double seconds = difftime(time2, time1);
    int days = static_cast<int>(seconds / (60 * 60 * 24)); // 秒转�?为天

    return days;
}
void BorrowBook(User uk  )
{
    list<Book> p = b_LordData(); // 加载书籍数据
    string name;
    string borrowdata=getCurrentDateTime();
    int bid;
    
    vector<int> idList;

    cin >> name;
    idList = searchBook(name);
    for (int bookId : idList)
    {
        auto temp = find_if(p.begin(), p.end(), [bookId](const Book& book) { return book.id == bookId; });
        if (temp != p.end())
        {
            cout << "name: " << temp->bookname << " id: " << temp->id << endl;
        }
    }

    cout << "输入想借书的id:" << endl;
    cin >> bid;

    auto temp = find_if(p.begin(), p.end(), [bid](const Book& book) { return book.id == bid; });
    if (temp != p.end())
    {
        userborrowbook(uk, *temp, borrowdata);
    }
}
list<string> lookBorrowbook_stu(User x);
void returnBook(User uk)
{
    //先展示借书有哪些然后输入书名和id进�?�还书，最后输出罚款金额并且把所还书放到书库�?
    list<string> p=lookBorrowbook_stu(uk);
for (list<string>::const_iterator it = p.begin(); it != p.end(); it++)
    {
        cout<<(*it)<<endl;
    }
    cout<<"�������������id"<<endl;
    string returnname;
    int returnid;
    
    std::cin>>returnname;
    cin>>returnid;
    list<User> q =u_LordData();
    for (list<User>::iterator it = q.begin(); it != q.end(); it++)//利用�?代器来遍历book的list容器的元素并且输出到文件�?
    {
        if(uk==(*it))
        {
            uk.borrowbook=(*it).borrowbook;
            for (list<Borrowed_Book>::iterator it2 = (*it).borrowbook.begin(); it2 != (*it).borrowbook.end(); it2++)//利用�?代器来遍历book的list容器的元素并且输出到文件�?
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
            cout<<"您逾期 "<<days-14<<" 天未还书,罚�?? "<<(days-14)/2<<" 元！"<<endl;
            else
            {
                cout<<"您已按期完成还书�?"<<endl;
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

void i_SaveData(list<IndexNode> &p)//存储数据
{
    ofstream fp("index.txt", ios::app);//fp为文件指针，写方�?


    for (list<IndexNode>::const_iterator it = p.begin(); it != p.end(); it++)//利用�?代器来遍历book的list容器的元素并且输出到文件�?
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

void AddIndexword(const string& name, int id, list<IndexNode>& L)
{
    for (auto ch : name) // ch依�?�取的是str里面的字�?,直到取完为�??
    {
        IndexNode searchword(ch);
        auto temp = find(L.begin(), L.end(), searchword);
        if (temp != L.end())
        {
            temp->addBooks(id);
        }
        else
        {
            IndexNode newNode(ch);
            newNode.addBooks(id);
            L.push_back(newNode);
        }
    }
}

void DelIndexword(string name,int id)
{
    list<IndexNode> L=i_LordData();
    for (auto ch : name)         //ch依�?�取的是str里面的字�?,直到取完为�??
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


void BuildIndex()//建立书名词典
{
    list<Book> p=b_LordData();
    list<IndexNode> L=i_LordData();
    //IndexNode temp;
    for(list<Book>::const_iterator it = p.begin();it !=p.end();it++)
    {
        AddIndexword((*it).bookname,(*it).id,L);
    //     for (auto ch : (*it).bookname)         //ch依�?�取的是str里面的字�?,直到取完为�??
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
    i_SaveData(L);
}
bool compareBook(Book a,Book b)
{
    return a.io_number>b.io_number;
}

list<string> Rank()
{
    list<Book> p=b_LordData(); 
    list<string> a;
    string b;
    p.sort(compareBook);
    int ranking=1;
    for (list<Book>::const_iterator it = p.begin(); it != p.end(); it++)//利用�?代器来遍历book的list容器的元素并且输出到文件�?
    {
        b =to_string(ranking) + " " + (*it).bookname + " " + to_string((*it).id); ;
        a.push_back(b);
        ranking++;
    }
    return a;
}

list<string> lookBorrowbook_stu(User x)
{
    list<User> p =u_LordData();
    list<string> a;
    string b;
    for (list<User>::const_iterator it = p.begin(); it != p.end(); it++)//利用�?代器来遍历book的list容器的元素并且输出到文件�?
    {
        if(x==(*it))
        {
            for (list<Borrowed_Book>::const_iterator it2 = (*it).borrowbook.begin(); it2 != (*it).borrowbook.end(); it2++)//利用�?代器来遍历book的list容器的元素并且输出到文件�?
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
    for (list<User>::const_iterator it = p.begin(); it != p.end(); it++)//利用�?代器来遍历book的list容器的元素并且输出到文件�?
    {
        if((*it).borrownum!= 0){
            for (list<Borrowed_Book>::const_iterator it2 = (*it).borrowbook.begin(); it2 != (*it).borrowbook.end(); it2++)//利用�?代器来遍历book的list容器的元素并且输出到文件�?
            {
                b=(*it2).borrowbookname+ " " +to_string((*it2).id)+" "+(*it2).data+" "+(*it).name;
                a.push_back(b);
            }
        }
    }
    return a;
}

#endif 