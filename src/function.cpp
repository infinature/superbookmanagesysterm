#include "function.h"

void BorrowBook(User uk ,string borrowdata )
{
    list<Book> p = b_LordData(); // 加载书籍数据
    string name;
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
    for (list<Book>::const_iterator it = p.begin(); it != p.end(); it++)//利用迭代器来遍历book的list容器的元素并且输出到文件中
    {
        b =to_string(ranking) + " " + (*it).bookname + " " + to_string((*it).id); ;
        a.push_back(b);
        ranking++;
    }
    return a;
}
