#include "function.h"

void BorrowBook(User uk, std::string borrowdata, int kind) {
    std::list<Book> p = b_LordData();
    std::string name;
    int bid;

    std::vector<int> idList;
    std::cout << "输入关键词查找：";
    name = readUTF8FromConsole();

    if (kind == 0)
        idList = searchBookD(name);
    else if (kind == 1)
        idList = searchBookW(name);
    bool flag=0;
    for (int bookId : idList) {
        auto temp = std::find_if(p.begin(), p.end(), [bookId](const Book& book) { return book.id == bookId; });
        if (temp != p.end()) {
            flag=1;
            std::cout << "name: " << temp->bookname << " id: " << temp->id << std::endl;
        }   
    }
    if(!flag)
    {
        cout<<"无存书，自动返回"<<endl;
        return;
    }
    while (true) {
        bid=getValidIntegerInput("输入想借书的id:");
        // 检查输入的bid是否在idList中
        if (std::find(idList.begin(), idList.end(), bid) != idList.end()) {
            auto temp = std::find_if(p.begin(), p.end(), [bid](const Book& book) { return book.id == bid; });
            if (temp != p.end()) {
                if ((*temp).cur_number == 0) {
                    std::cout << "无存书！" << std::endl;
                } else {
                    (*temp).io_number += 1;
                    (*temp).cur_number -= 1;
                    b_SaveData_del(p);
                    userborrowbook(uk, *temp, borrowdata);
                    std::cout << "借书成功！" << std::endl;
                }
            }
            break; // 成功借书后退出循环
        } else {
            std::cout << "输入的id无效,请重新输入." << std::endl;
        }
    }
}

bool compareBook(Book a,Book b)
{
    return a.io_number>b.io_number;
}

void Rank()  
{  
    list<Book> p = b_LordData(); // 假设这个函数返回一个Book的列表  
    p.sort(compareBook);  
    int ranking = 1;  
      
    // 设置输出格式，排名占3个字符宽度，书名占20个字符宽度，ID占10个字符宽度  
    cout << left << setw(10) << "排名" << setw(50) << "书名" <<endl;  
  
    for (list<Book>::const_iterator it = p.begin(); it != p.end(); ++it)  
    {  
        cout << left << setw(10) << ranking << setw(50) << (*it).bookname << endl;  
        ranking++;  
        if(ranking>=21)
        break;
    }  
    return;  
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
string UTF16ToUTF8(const std::wstring& utf16) {
    int count = WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), -1, NULL, 0, NULL, NULL);
    char* buffer = new char[count+1];
    memset(buffer,0,count+1);
    WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), -1, buffer, count, NULL, NULL);
    std::string utf8(buffer);
    delete[] buffer;
    return utf8;
}
bool isValidUTF8(const std::string& str) {
    int len = str.length();
    int i = 0;
    while (i < len) {
        unsigned char c = str[i];
        int num_bytes = 0;
        
        if ((c & 0x80) == 0) {
            // 1-byte character (ASCII)
            num_bytes = 1;
        } else if ((c & 0xE0) == 0xC0) {
            // 2-byte character
            num_bytes = 2;
        } else if ((c & 0xF0) == 0xE0) {
            // 3-byte character
            num_bytes = 3;
        } else if ((c & 0xF8) == 0xF0) {
            // 4-byte character
            num_bytes = 4;
        } else {
            // Invalid UTF-8 start byte
            return false;
        }
        
        if (i + num_bytes > len) {
            // Not enough bytes left
            return false;
        }
        
        // Check continuation bytes
        for (int j = 1; j < num_bytes; ++j) {
            if ((str[i + j] & 0xC0) != 0x80) {
                return false;
            }
        }
        
        i += num_bytes;
    }
    return true;
}
string readUTF8FromConsole() {
    // 获取标准输入的句柄
    HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        return "";
    }

    // 临时缓冲区用于存储宽字符
    wchar_t buffer[256];
    DWORD charsRead;
    
    // 读取输入的宽字符
    if (!ReadConsoleW(hConsole, buffer, 256, &charsRead, NULL)) {
        return "";
    }

    // 去掉缓冲区末尾的换行符（如果有）
    if (charsRead > 0 && buffer[charsRead - 1] == L'\n') {
        buffer[charsRead - 1] = L'\0';
        charsRead--;
    }
    if (charsRead > 0 && buffer[charsRead - 1] == L'\r') {
        buffer[charsRead - 1] = L'\0';
        charsRead--;
    }

    // 转换宽字符为 UTF-8
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, buffer, charsRead, NULL, 0, NULL, NULL);
    std::string utf8String(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, buffer, charsRead, &utf8String[0], size_needed, NULL, NULL);

    return utf8String;
}
// 通用函数：验证并获取有效的整数输入
int getValidIntegerInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::string input;
        std::cin >> input;

        // 检查输入是否为有效的整数
        try {
            size_t pos;
            value = std::stoi(input, &pos);
            if (pos == input.length()) {
                return value;
            } else {
                throw std::invalid_argument("Invalid input");
            }
        } catch (const std::invalid_argument&) {
            std::cerr << "输入无效，请输入一个有效的整数。" << std::endl;
        } catch (const std::out_of_range&) {
            std::cerr << "输入超出范围，请输入一个有效的整数。" << std::endl;
        }

        // 清空错误标志并忽略剩余的输入
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}