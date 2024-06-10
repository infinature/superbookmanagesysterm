#include "Book.h"
list<Book> b_LordData()//读取存储的数据
{
    ifstream fp("../data/bookinfo.txt");//读方式
    list<Book> p;
    Book temp;
        string bookname;
    while (fp >> temp.id)//peek是看一眼下一个输入是什么但不更改数据
    {

        

         fp>> temp.sum_number;
        fp >> temp.io_number >> temp.cur_number >> temp.kind>>temp.bookname >> temp.author;
        fp>>temp.publising >> temp.publisingdate;//先把除了借书名字的内容读过来

        
        p.push_back(temp);//把这个赋值好的user放进list

    }
    fp.close();
    return p;
}
void addBook()
{
    list<Book> p;
    Book temp;
    
    cin>> temp.id >> temp.sum_number;
    cin >> temp.io_number >> temp.cur_number >> temp.kind>>temp.bookname >> temp.author;
    cin>>temp.publising >> temp.publisingdate;
    p.push_back(temp);//把这个赋值好的user放进list
    list<IndexNode> L = i_LordData(); // 加载现有的索引数据
    AddIndexword(temp.bookname, temp.id, L); // 将书添加到词典
    b_SaveData(p);
}
void b_SaveData_del(list<Book>& p)//存储数据
{
    ofstream fp("../data/bookinfo.txt", ios::trunc);//fp为文件指针，写方式


    for (list<Book>::const_iterator it = p.begin(); it != p.end(); it++)//利用迭代器来遍历book的list容器的元素并且输出到文件中
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
// void deleteBook()
// {
//     string n;
//     cin>>n;
//     list<IndexNode> L=i_LordData();
//     list<Book> p =b_LordData();
//     for (list<Book>::const_iterator it = p.begin(); it != p.end(); it++)
//         {
//             if((*it).bookname ==n)
//             {
//                 DelIndexword((*it).bookname,(*it).id);//词典删除
//                 p.erase(it);
//                 break;
//             }
//         }
//     b_SaveData_del(p);

// }
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
void b_SaveData(list<Book>& p)//存储数据
{
    ofstream fp("../data/bookinfo.txt", ios::app);//fp为文件指针，写方式


    for (list<Book>::const_iterator it = p.begin(); it != p.end(); it++)//利用迭代器来遍历book的list容器的元素并且输出到文件中
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
