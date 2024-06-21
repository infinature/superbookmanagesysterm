#include "function.h"

extern int deadline;
extern double finenum;

/*********************************************************************************
 * @brief 借书函数  
 *  
 * 根据用户输入的关键词和类型，搜索并借阅书籍。  
 *  
 * @param uk 用户对象，包含用户信息  
 * @param borrowdata 借书数据（可能是借书时间、地点等额外信息）  
 * @param kind 搜索类型（0代表按书名搜索，1代表按作者搜索）  
 *  
 * @return 无返回值（void）  
 **********************************************************************************/ 
void BorrowBook(User uk, std::string borrowdata) {
    std::list<Book> p = b_LordData();// 获取所有书籍的列表
    std::string name; // 初始化变量
    int bid;
    int kind=1;
    string bookkind="3";
    std::vector<int> idList;// 用于存储搜索到的书籍ID的列表 
    // 根据搜索类型进行搜索
    kind=getValidIntegerInput("请输入搜索方式(0为精确搜索,1为模糊搜索,默认为模糊搜索):");
    if(kind!=0&&kind!=1)kind=1;

    cout<<"请输入书籍类型(0为书籍，1为期刊，2为报刊，3为全部类型，默认为全部类型):";
    cin>>bookkind;
    if(bookkind!="0"&&bookkind!="1"&&bookkind!="2")bookkind="3";

    std::cout << "输入关键词查找：";// 提示用户输入关键词进行搜索
    name = readUTF8FromConsole();
    if (kind == 0)
        idList = searchBookD(name);
    else if (kind == 1)
        idList = searchBookW(name);
    bool flag=0;// 标志位，用于判断是否找到了书籍
    // 遍历搜索到的书籍ID列表，检查书籍是否存在
    for (int bookId : idList) {
        auto temp = std::find_if(p.begin(), p.end(), [bookId](const Book& book) { return book.id == bookId; });
        if (temp != p.end()) {
            if(bookkind=="3"){
                flag=1;
            std::cout << "name: " << temp->bookname << " 类型: " << temp->kind <<" id: " << temp->id << std::endl;}
            else if(bookkind==temp->kind){
                flag=1;
            std::cout << "name: " << temp->bookname << " 类型: " << temp->kind <<" id: " << temp->id << std::endl;}
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
                if ((*temp).cur_number <= 0) {
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
/*用于排序的辅助函数*/
bool compareBook(Book a,Book b)
{
    return a.io_number>b.io_number;
}

/*********************************************************************************
 * @brief 书籍排名函数  
 *  
 * 从书籍列表中获取所有书籍，并按一定规则对书籍进行排序，  
 * 然后输出前20名的书籍名称及其排名。  
 *  
 * @return 无返回值（void）  
 **********************************************************************************/ 
void Rank()  
{  
    list<Book> p = b_LordData(); // 获取所有书籍的列表 
    p.sort(compareBook);  // 使用compareBook函数对书籍列表进行排序 
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
/*********************************************************************************
 * @brief 获取当前日期（不含时间）  
 *  
 * 该函数获取当前的系统时间，并将其转换为本地时间，然后提取出日期部分（年、月、日）  
 * 并将它们格式化为一个字符串返回。  
 *  
 * @return 当前日期的字符串表示，格式为YYYYMMDD  
 **********************************************************************************/ 
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

/*********************************************************************************
 * @brief 计算两个日期之间的天数差  
 *  
 * 此函数接受两个日期字符串作为参数，并计算它们之间的天数差。  
 * 日期字符串应为 "YYYYMMDD" 格式。  
 *  
 * @param date1 第一个日期字符串，格式为 "YYYYMMDD"  
 * @param date2 第二个日期字符串，格式为 "YYYYMMDD"  
 *  
 * @return 两个日期之间的天数差  
 **********************************************************************************/ 
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
/*********************************************************************************
 * @brief 提取字符串中的不重复汉字  
 *  
 * 从给定的 C 风格字符串中提取所有不重复的汉字  
 * 假设每个汉字由连续的三个字节表示（GBK、GB2312 或类似编码）。  
 *  
 * @param ori_c C 风格字符串，包含待处理的汉字字符  
 *  
 * @return 包含所有不重复汉字的vector容器  
 **********************************************************************************/ 
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

/*********************************************************************************
 * @brief 将字符串转换为字符数组  
 *  
 * 将输入的 `string` 类型数据转换为字符数组（`char*`），并返回该字符数组的指针。  
 * 注意：返回的字符数组是动态分配的，调用者需在使用后手动释放内存。  
 *  
 * @param strSend 输入的字符串  
 *  
 * @return 转换后的字符数组指针  
 **********************************************************************************/ 
char* strToChar(string strSend)
{
    char* ConvertData;
    const int len2 = strSend.length();
    ConvertData = new char[len2 + 1];
    strcpy(ConvertData, strSend.c_str());
    return ConvertData;
}

/*********************************************************************************
 * @brief 将 UTF-16 编码的宽字符串转换为 UTF-8 编码的字符串  
 *  
 * 使用 Windows API 函数 WideCharToMultiByte 将 UTF-16 编码的宽字符串（std::wstring）  
 * 转换为 UTF-8 编码的字符串（std::string）。  
 *  
 * @param utf16 UTF-16 编码的宽字符串  
 *  
 * @return 转换后的 UTF-8 编码的字符串  
 **********************************************************************************/ 
string UTF16ToUTF8(const std::wstring& utf16) {
    int count = WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), -1, NULL, 0, NULL, NULL);
    char* buffer = new char[count+1];
    memset(buffer,0,count+1);
    WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), -1, buffer, count, NULL, NULL);
    std::string utf8(buffer);
    delete[] buffer;
    return utf8;
}

/*********************************************************************************
 * @brief 判断给定的字符串是否为有效的UTF-8编码  
 *  
 * 根据UTF-8编码规则，判断输入的字符串`str`是否是一个有效的UTF-8编码字符串。  
 *  
 * @param str 待检查的字符串  
 *  
 * @return 如果字符串是有效的UTF-8编码，则返回`true`；否则返回`false`  
 **********************************************************************************/ 
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

/*********************************************************************************
 * @brief 从控制台读取UTF-8编码的字符串  
 *  
 * 该函数通过Windows API读取用户在控制台输入的宽字符（UTF-16编码），然后将其转换为UTF-8编码的字符串。  
 *  
 * @return 读取并转换后的UTF-8编码字符串  
 **********************************************************************************/ 
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

/*********************************************************************************
 * @brief 获取有效的整数输入  
 *  
 * 通过控制台提示用户输入一个整数，并持续要求用户输入直到输入一个有效的整数为止。  
 *  
 * @param prompt 提示用户输入的字符串  
 *  
 * @return 用户输入的有效整数  
 *  
 * @throw 无直接抛出异常，但内部使用了try-catch来处理stoi可能抛出的异常  
 **********************************************************************************/ 
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

/*********************************************************************************
 * @brief 获取有效的数字输入  
 *  
 * 通过控制台提示用户输入一个数字，并持续要求用户输入直到输入一个有效的数字为止。  
 *  
 * @param prompt 提示用户输入的字符串  
 *  
 * @return 用户输入的有效数字 
 *  
 * @throw 无直接抛出异常，但内部使用了try-catch来处理stoi可能抛出的异常  
 **********************************************************************************/ 
double getValidDoubleInput(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);

        // 使用字符串流进行转换和验证
        std::istringstream stream(input);
        stream >> value;

        // 检查流是否成功转换，且没有额外的字符
        if (!stream.fail() && stream.eof()) {
            return value;
        } else {
            std::cerr << "输入无效，请输入一个有效的双精度浮点数。" << std::endl;
        }
        
        // 清空错误标志并忽略剩余的输入
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
/*********************************************************************************
 * @brief 修改系统参数  
 *  
 * 修改图书借阅时间限制和罚款金额  
 *  
 * @param *date 定义在returnbook的全局变量，记录借书时间 
 * @param *cost 定义在returnbook的全局变量，记录罚款金额    
 *  
 * @return 无返回值（void）  
 **********************************************************************************/ 
void changeSystemParameter(int *date,double *cost)
{
    *date=getValidIntegerInput("输入更改的借书日期(默认为14天,范围为0~60):");
    if(*date<=0||*date>=60)
    *date=14;
    cout<<"修改成功，当前为 "<<*date<<" 天。"<<endl;
    getchar();
    *cost=getValidDoubleInput("输入更改罚款金额(默认为0.5元/天):");
    cout<<"修改成功，当前为 "<<*cost<<" 元/天。"<<endl;
    // 将数据写入txt文件  
 std::ofstream outfile("../data/userinfo.txt"); 
 if (outfile.is_open()) { 
 outfile << *date << std::endl; 
 outfile << *cost << std::endl; 
 outfile.close(); 
 } else { 
 std::cerr << "无法打开文件: " << std::endl; 
 } 
 
} 


void lordfine()
{
 std::ifstream infile("../data/fine.txt"); 
if (!infile) { 
 std::cerr << "无法打开文件: " << std::endl; 
 } 
 std::string line; 
 std::getline(infile, line) && std::istringstream(line) >> deadline;
 std::getline(infile, line) && std::istringstream(line) >> finenum;
 infile.close(); 
}