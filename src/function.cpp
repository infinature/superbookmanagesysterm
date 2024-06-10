#include "function.h"

void BorrowBook(User uk ,string borrowdata )
{
    list<Book> p = b_LordData(); // 加载书籍数据
    string name;
    int bid;
    
    vector<int> idList;
    cout<<"输入关键词查找：";
    getline(cin,name);
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
        if((*temp).cur_number==0)
        {
            cout<<"无存书！"<<endl;
        }
        else
        {
        (*temp).io_number+=1;
        (*temp).cur_number-=1;
        //userborrowbook(uk, *temp, borrowdata);
        }
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
string getCurrentDateTime() {  
     // 获取当前时间（秒自从1970-01-01 00:00:00 UTC）
    time_t rawtime;
    time(&rawtime);
    
    // 转换为本地时间
    struct tm * timeinfo = localtime(&rawtime);
    
    // 使用stringstream来构造日期字符串
    std::ostringstream oss;
    oss << (timeinfo->tm_year + 1900)
    << std::setfill('0') << std::setw(2) << (timeinfo->tm_mon + 1)
    << std::setfill('0') << std::setw(2) << timeinfo->tm_mday;
    
    return oss.str();
}

int daysBetweenDates(const std::string& date1, const std::string& date2) {
    // 将字符串转换为tm结构体
    std::tm tm1 = {}, tm2 = {};
    std::istringstream ss1(date1), ss2(date2);
    ss1 >> std::get_time(&tm1, "%Y%m%d");
    ss2 >> std::get_time(&tm2, "%Y%m%d");

    // 转换为time_t类型
    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);

    // 计算时间差并转换为天数
    double seconds = difftime(time2, time1);
    int days = static_cast<int>(seconds / (60 * 60 * 24)); // 秒转换为天

    return days;
}
vector<string> chinese_io(char* ori_c) {
    int size = strlen(ori_c); // 获取字符串长度
    int index = 0; // 初始化索引
    char zi_c[3]; // 用于存储单个汉字字符的数组，每个汉字占3个字节
    vector<string> res_str; // 用于存储不重复汉字的结果向量

    // 循环遍历原始字符串中的每个汉字
    while (index < size) {
        // 将单个汉字的三个字节拷贝到 zi_c 数组中
        zi_c[0] = ori_c[index++];
        zi_c[1] = ori_c[index++];
        zi_c[2] = ori_c[index++];
        string zi_str(zi_c, 3); // 将字符数组转为字符串

        // 如果结果向量中没有该汉字，则添加
        if (find(res_str.begin(), res_str.end(), zi_str) == res_str.end()) {
            res_str.push_back(zi_str);
        }
    }

    return res_str;
}

char* strToChar(string strSend)
{
    char* ConvertData;
    const int len2 = strSend.length();
    ConvertData = new char[len2 + 1];
    strcpy(ConvertData, strSend.c_str());
    return ConvertData;
}