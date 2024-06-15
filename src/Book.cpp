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
    temp.id=getValidIntegerInput("请输入新增加书籍的id:");
    temp.sum_number=getValidIntegerInput("请输入新增加书籍的总数:");
    temp.io_number=getValidIntegerInput("请输入新增加书籍的已借数量:");
    temp.cur_number=getValidIntegerInput("请输入新增加书籍的现有数量:");
    cout<<"请输入新增加书籍的种类(0为期刊,1为杂志,2为图书):"<<endl;
    cin>>temp.kind;
    cout<<"请输入新增加书籍的名字："<<endl;
    temp.bookname=readUTF8FromConsole();
    cout<<"请输入新增加书籍的作者名字："<<endl;
    temp.author=readUTF8FromConsole();
    cout<<"请输入新增加书籍的出版社名称："<<endl;
    temp.publising=readUTF8FromConsole();
    cout<<"请输入新增加书籍的出版日期(格式示例:20010101):"<<endl;
    cin>> temp.publisingdate;

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
                //DelIndexword((*it).bookname,(*it).id);//词典删除
                p.erase(it);
                break;
            }
        }
    b_SaveData_del(p);

}
void lookBook() {  
    list<Book> booksList = b_LordData(); // 假设这个函数存在并返回书的列表  
  
    // 设置输出字段的宽度和对齐方式  
    const int FIELD_WIDTH = 10; // 你可以根据需要调整这个值  
    cout << left; // 左对齐  
    cout << setw(FIELD_WIDTH) << "书籍id"  
         << setw(FIELD_WIDTH) << "书籍总数"  
         << setw(FIELD_WIDTH) << "书籍已借出数"  
         << setw(FIELD_WIDTH) << "书籍现存数"  
         << setw(FIELD_WIDTH) << "书籍种类"  
         << setw(FIELD_WIDTH * 4) << "书籍名" // 如果书名较长，可以增加宽度  
         << setw(FIELD_WIDTH*4) << "作者名"  
         << setw(FIELD_WIDTH*4) << "出版社名称"  
         << setw(FIELD_WIDTH*4) << "出版日期"  
         << endl;  
  
    for (const auto& book : booksList) { // 使用范围for循环简化代码  
        cout << setw(FIELD_WIDTH) << book.id  
             << setw(FIELD_WIDTH) << book.sum_number  
             << setw(FIELD_WIDTH) << book.io_number  
             << setw(FIELD_WIDTH) << book.cur_number  
             << setw(FIELD_WIDTH) << book.kind  
             << setw(FIELD_WIDTH * 4) << book.bookname  
             << setw(FIELD_WIDTH*4) << book.author  
             << setw(FIELD_WIDTH*4) << book.publising  
             << setw(FIELD_WIDTH*4) << book.publisingdate  
             << endl;  
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
