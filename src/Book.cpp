#include "Book.h"

/*********************************************************************************  
 * @brief 读取书籍信息  
 *  
 * 从指定的文本文件中读取书籍信息，并将它们存储在一个Book类型的list中。  
 *  
 * @return 返回一个包含书籍信息的list<Book>  
 *  
 * @note 此函数没有参数，直接读取硬编码的文件路径。  
 *       
 **********************************************************************************/ 
list<Book> b_LordData()
{
    ifstream fp("../data/bookinfo.txt"); // 打开文件以读取模式
    list<Book> p;// 创建一个空的Book类型的list来存储读取的数据
    Book temp;// 创建一个临时Book对象用于读取数据
        string bookname;
        // 循环读取文件中的书籍信息 
    while (fp >> temp.id)
    {

        

         fp>> temp.sum_number;
        fp >> temp.io_number >> temp.cur_number >> temp.kind>>temp.bookname >> temp.author;
        fp>>temp.publising >> temp.publisingdate;

        
        p.push_back(temp);// 将读取的书籍信息添加到list中

    }
    // 关闭文件
    fp.close();
    // 返回包含书籍信息的list
    return p;
}

/*********************************************************************************
 * @brief 添加书籍  
 *  
 * 从用户处获取新的书籍信息，并将其添加到书籍列表中。同时，更新书籍索引，并保存书籍列表和索引。  
 *  
 * @note 此函数没有返回值，也不接受任何参数。它直接操作数据库。  
 *      
 **********************************************************************************/ 
void addBook()
{
    list<Book> havebook=b_LordData();//将现有书目储存到havebook中
    list<Book> p;// 创建一个空的书籍列表 
    Book temp;// 创建一个临时书籍对象用于存储用户输入的信息
    temp.id=havebook.back().id+1;
    cout<<"请输入新增加书籍的名字："<<endl;
    temp.bookname=readUTF8FromConsole();
    cout<<"请输入新增加书籍的作者名字："<<endl;
    temp.author=readUTF8FromConsole();
    cout<<"请输入新增加书籍的出版社名称："<<endl;
    temp.publising=readUTF8FromConsole();
    cout<<"请输入新增加书籍的出版日期(格式示例:20010101):"<<endl;
    cin>> temp.publisingdate;
    temp.sum_number=getValidIntegerInput("请输入新增加书籍的总数:");
    temp.io_number=0;
    temp.cur_number=temp.sum_number;
    cout<<"请输入新增加书籍的种类(0为期刊,1为杂志,2为图书):"<<endl;
    while(1)
    {
        cin>>temp.kind;
        if(temp.kind=="0"||temp.kind=="1"||temp.kind=="2")
        {
            break;
        }
        else
        {
            cout<<"未包含类别，请重新输入"<<endl;
        }
    }
    p.push_back(temp);//把这个赋值好的book放进list
    list<IndexNode> L = i_LordData(); // 加载现有的索引数据
    AddIndexword(temp.bookname, temp.id, L); // 将书添加到词典
    b_SaveData(p);
    i_SaveData_del(L);
    cout<<"添加成功"<<endl;
}
/*********************************************************************************
 * @brief 保存书籍信息到文件  
 *  
 * 将传入的书籍信息列表保存到指定的文本文件中。文件将包含每本书的详细信息，  
 * 包括书籍ID、总数量、输入输出数量、当前数量、种类、书名、作者、出版社和出版日期。  
 *  
 * @note 此函数无返回值，它接受一个对Book类型list容器的引用作为参数。  
 *       文件路径被硬编码为"../data/bookinfo.txt"，并且每次调用此函数时，该文件都会被清空并重新写入。  
 *  
 * @param list<Book>& p 一个包含需要保存的书籍信息的列表。  
 **********************************************************************************/ 

void b_SaveData_del(list<Book>& p)   
{  
    // 创建一个输出文件流，指向../data/bookinfo.txt文件，并清空文件内容  
    ofstream fp("../data/bookinfo.txt", ios::trunc);  
  
    // 使用const迭代器遍历书籍信息列表  
    for (list<Book>::const_iterator it = p.begin(); it != p.end(); it++)  
    {  
        // 写入书籍的id  
        fp << (*it).id << " ";  
        // 写入书籍的总数量  
        fp << (*it).sum_number << " ";  
        // 写入书籍的输入输出数量（可能是入库出库数量）  
        fp << (*it).io_number << " ";  
        // 写入书籍的当前数量  
        fp << (*it).cur_number << " ";  
        // 写入书籍的种类、书名、作者、出版社和出版日期  
        fp << (*it).kind << " " << (*it).bookname << " " << (*it).author << " " << (*it).publising << " " << (*it).publisingdate;  
        
        fp << endl;  
    }  
  
    // 关闭文件流  
    fp.close();  
}
/*********************************************************************************
 * @brief 从书籍列表中删除指定书名的书籍  
 *  
 * 从传入的书籍信息列表中删除具有指定书名的书籍。如果找到匹配的书籍，  
 * 则从列表中移除它，并可能更新到某个数据源（如文件或数据库）。  
 *  
 * @note 此函数无返回值，它接受一个对Book类型list容器的引用作为参数。  
 *  
 * @param list<Book>& p 包含需要搜索和可能删除的书籍信息的列表。  
 **********************************************************************************/ 
void deleteBook()
{
    string n;
    cin>>n; // 从用户处获取要删除的书籍的书名 
    list<IndexNode> L=i_LordData();
    list<Book> p =b_LordData();
    for (list<Book>::const_iterator it = p.begin(); it != p.end(); it++)
        {
            if((*it).bookname ==n)
            {
                //DelIndexword((*it).bookname,(*it).id);//词典删除
                p.erase(it); // 从列表中删除书籍，并更新迭代器 
                break;
            }
        }
    b_SaveData_del(p);// 保存更新后的书籍列表到数据源  

}
/*********************************************************************************
 * @brief 查阅所有书籍信息  
 *  
 * 列出所有书籍的详细信息到控制台。信息包括书籍ID、总数量、输入输出数量、当前数量、  
 * 种类、书名、作者、出版社和出版日期。  
 *  
 * @note 此函数无返回值  
 *  
 * @param 无参数，该函数直接访问数据源获取书籍信息。  
 **********************************************************************************/ 
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
/*********************************************************************************
 * @brief 查阅所有期刊信息  
 *  
 * 列出所有书籍的详细信息到控制台。信息包括书籍ID、总数量、输入输出数量、当前数量、  
 * 种类、书名、作者、出版社和出版日期。  
 *  
 * @note 此函数无返回值  
 *  
 * @param 无参数，该函数直接访问数据源获取书籍信息。  
 **********************************************************************************/ 
void lookBook_0() {  
    list<Book> booksList = b_LordData(); // 假设这个函数存在并返回书的列表  
    cout<<"目前查询的是书库里所有的期刊"<<endl;
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
    for (list<Book>::const_iterator it = booksList.begin(); it != booksList.end(); it++)//利用迭代器来遍历book的list容器的元素并且输出到文件中
    {
        if((*it).kind=="0")
        {
    
  
     // 使用范围for循环简化代码  
        cout << setw(FIELD_WIDTH) << (*it).id  
             << setw(FIELD_WIDTH) << (*it).sum_number  
             << setw(FIELD_WIDTH) << (*it).io_number  
             << setw(FIELD_WIDTH) << (*it).cur_number  
             << setw(FIELD_WIDTH) << (*it).kind  
             << setw(FIELD_WIDTH * 4) << (*it).bookname  
             << setw(FIELD_WIDTH*4) << (*it).author  
             << setw(FIELD_WIDTH*4) <<(*it).publising  
             << setw(FIELD_WIDTH*4) << (*it).publisingdate  
             << endl;  
    }  
}
}

/*********************************************************************************
 * @brief 查阅所有报刊信息  
 *  
 * 列出所有书籍的详细信息到控制台。信息包括书籍ID、总数量、输入输出数量、当前数量、  
 * 种类、书名、作者、出版社和出版日期。  
 *  
 * @note 此函数无返回值  
 *  
 * @param 无参数，该函数直接访问数据源获取书籍信息。  
 **********************************************************************************/ 
void lookBook_1() {  
    list<Book> booksList = b_LordData(); // 假设这个函数存在并返回书的列表  
    cout<<"目前查询的是书库里所有的报刊"<<endl;
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
    for (list<Book>::const_iterator it = booksList.begin(); it != booksList.end(); it++)//利用迭代器来遍历book的list容器的元素并且输出到文件中
    {
        if((*it).kind=="1")
        {
    
  
     // 使用范围for循环简化代码  
        cout << setw(FIELD_WIDTH) << (*it).id  
             << setw(FIELD_WIDTH) << (*it).sum_number  
             << setw(FIELD_WIDTH) << (*it).io_number  
             << setw(FIELD_WIDTH) << (*it).cur_number  
             << setw(FIELD_WIDTH) << (*it).kind  
             << setw(FIELD_WIDTH * 4) << (*it).bookname  
             << setw(FIELD_WIDTH*4) << (*it).author  
             << setw(FIELD_WIDTH*4) <<(*it).publising  
             << setw(FIELD_WIDTH*4) << (*it).publisingdate  
             << endl;  
    }  
}
}
/*********************************************************************************
 * @brief 查阅所有书籍信息  
 *  
 * 列出所有书籍的详细信息到控制台。信息包括书籍ID、总数量、输入输出数量、当前数量、  
 * 种类、书名、作者、出版社和出版日期。  
 *  
 * @note 此函数无返回值  
 *  
 * @param 无参数，该函数直接访问数据源获取书籍信息。  
 **********************************************************************************/ 
void lookBook_2() {  
    list<Book> booksList = b_LordData(); // 假设这个函数存在并返回书的列表  
    cout<<"目前查询的是书库里所有的书籍"<<endl;
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
    for (list<Book>::const_iterator it = booksList.begin(); it != booksList.end(); it++)//利用迭代器来遍历book的list容器的元素并且输出到文件中
    {
        if((*it).kind=="2")
        {
    
  
     // 使用范围for循环简化代码  
        cout << setw(FIELD_WIDTH) << (*it).id  
             << setw(FIELD_WIDTH) << (*it).sum_number  
             << setw(FIELD_WIDTH) << (*it).io_number  
             << setw(FIELD_WIDTH) << (*it).cur_number  
             << setw(FIELD_WIDTH) << (*it).kind  
             << setw(FIELD_WIDTH * 4) << (*it).bookname  
             << setw(FIELD_WIDTH*4) << (*it).author  
             << setw(FIELD_WIDTH*4) <<(*it).publising  
             << setw(FIELD_WIDTH*4) << (*it).publisingdate  
             << endl;  
    }  
}
}
/*********************************************************************************
 * @brief 存储书籍信息  
 *  
 * 将传入的书籍列表中的所有书籍信息保存到指定的文本文件中。每本书的信息包括书籍ID、总数量、  
 * 输入输出数量、当前数量、种类、书名、作者、出版社和出版日期。  
 *  
 * @note 此函数无返回值，直接操作文件以保存数据。  
 *  
 * @param p 包含书籍信息的列表的引用，用于遍历并保存书籍数据。  
 **********************************************************************************/ 
void b_SaveData(list<Book>& p)//存储数据
{
    ofstream fp("../data/bookinfo.txt", ios::app);// fp为文件指针，以追加模式打开文件  


    for (list<Book>::const_iterator it = p.begin(); it != p.end(); it++) // 利用迭代器遍历书籍列表 ··
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
