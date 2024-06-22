#include "Index.h"

/*********************************************************************************
 * @brief 读取存储的数据  
 *  
 * 从文件"../data/index.txt"中读取数据，并构造一个IndexNode对象的链表。  
 * 文件中每行包含一个单词和多个与之关联的书籍ID，单词和ID之间用空格分隔。  
 *  
 * @return 包含读取数据的IndexNode链表  
 **********************************************************************************/  
list<IndexNode> i_LordData()//读取存储的数据
{
    ifstream fp("../data/index.txt");//读方式
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
        // 尝试从行中读取整数，直到无法读取为止  
        while (iss >> num) 
        {  
            temp.bookid.push_back(num);  
  
            // 尝试读取下一个字符（可能是非整数字符） 
        }  
        p.push_back(temp);
    }
    fp.close();
    return p;
}

/*********************************************************************************
 * @brief 搜索书籍ID并集  
 *  
 * 根据给定的书名（可能包含中文），搜索与之关联的书籍ID。  
 * 首先将书名转换为char*，然后进行中文分词，接着在IndexNode链表中搜索每个分词。  
 * 将所有找到的书籍ID添加到一个vector中，并对其进行排序和去重。  
 *  
 * @param name 要搜索的书名  
 * @return 包含与书名关联的书籍ID的vector  
 **********************************************************************************/ 
vector<int> searchBookW(const string& name) {
    list<IndexNode> L = i_LordData();
    vector<int> idList;

    char* Name = strToChar(name);
    vector<string> res_str = chinese_io(Name);
    delete[] Name; // 确保释放内存

    for (const string& str : res_str) {
        IndexNode searchword(str);
        auto temp = find(L.begin(), L.end(), searchword);
        if (temp != L.end()) {
            copy((*temp).bookid.begin(), (*temp).bookid.end(), back_inserter(idList));
        }
    }

    sort(idList.begin(), idList.end()); // 默认从小到大排序
    idList.erase(unique(idList.begin(), idList.end()), idList.end()); // 去重

    return idList;
}
/*********************************************************************************
 * @brief 搜索书籍ID交集  
 *  
 * 根据给定的书名（中文），搜索与之关联的书籍ID，并返回所有分词搜索结果的书籍ID交集。  
 *  
 * @param name 要搜索的书名  
 * @return 包含书籍ID交集的vector，如果没有交集则返回空vector  
 **********************************************************************************/ 
vector<int> searchBookD(const string& name) {
    list<IndexNode> L = i_LordData();
    vector<vector<int>> bookIdLists;

    char* Name = strToChar(name);
    vector<string> res_str = chinese_io(Name);
    delete[] Name; // 确保释放内存

    for (const string& str : res_str) {
        IndexNode searchword(str);
        auto temp = find(L.begin(), L.end(), searchword);
        if (temp != L.end()) {
            bookIdLists.push_back(temp->bookid);
        }
    }

    if (bookIdLists.empty()) {
        return {};
    }

    // 初始化交集结果为第一个列表
    vector<int> commonBooks = bookIdLists[0];

    for (size_t i = 1; i < bookIdLists.size(); ++i) {
        vector<int> temp;
        sort(commonBooks.begin(), commonBooks.end());
        sort(bookIdLists[i].begin(), bookIdLists[i].end());
        set_intersection(commonBooks.begin(), commonBooks.end(),
                         bookIdLists[i].begin(), bookIdLists[i].end(),
                         back_inserter(temp));
        commonBooks = temp;
    }

    return commonBooks;
}
/*********************************************************************************
 * @brief 存储数据  
 *  
 * 将给定的IndexNode对象链表写入到文件"../data/index.txt"中。  
 * 如果文件已存在，则追加写入；否则创建新文件。  
 *  
 * @param p 包含要存储的IndexNode对象的链表  
 **********************************************************************************/ 
void i_SaveData(list<IndexNode> &p)//存储数据
{
    ofstream fp("../data/index.txt", ios::app);//fp为文件指针，写方式


    for (list<IndexNode>::const_iterator it = p.begin(); it != p.end(); it++)//利用迭代器来遍历book的list容器的元素并且输出到文件中
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
/*********************************************************************************
 * @brief 存储（覆盖保存）数据到文件  
 *  
 * 将给定的IndexNode对象链表写入到文件"../data/index.txt"中，与i_SaveData不同的是，  
 * 此函数会先清空文件内容再写入，即覆盖原有文件内容。  
 *  
 * @param p 包含要存储的IndexNode对象的链表  
 * @return 无返回值（void）  
 **********************************************************************************/ 
void i_SaveData_del(list<IndexNode> &p)//存储数据
{
    ofstream fp("../data/index.txt", ios::trunc);//fp为文件指针，写方式


    for (list<IndexNode>::const_iterator it = p.begin(); it != p.end(); it++)//利用迭代器来遍历book的list容器的元素并且输出到文件中
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

/*********************************************************************************
 * @brief 添加索引词到链表  
 *  
 * 将给定的字符串名称分词，并将每个分词后的词作为索引词添加到给定的IndexNode对象链表中。  
 * 如果链表已存在该索引词，则将其对应的书籍ID添加到该索引词的书籍ID列表中；  
 * 如果链表不存在该索引词，则创建一个新的IndexNode对象，并将其添加到链表中。  
 *  
 * @param name 字符串名称，用于分词并作为索引词  
 * @param id 书籍ID，用于添加到索引词的书籍ID列表中  
 * @param L 包含IndexNode对象的链表，用于存储索引词及其对应的书籍ID列表  
 * @return 无返回值（void）  
 **********************************************************************************/ 
void AddIndexword(const string& name, int id, list<IndexNode>& L) {
    char* Name = strToChar(name);
    vector<string> res_str = chinese_io(Name);
    delete[] Name; // 确保释放内存

    for (const string& str : res_str) {
        IndexNode searchword(str);
        auto temp = find(L.begin(), L.end(), searchword);
        if (temp != L.end()) {
            temp->addBooks(id);
        } else {
            IndexNode newNode(str);
            newNode.addBooks(id);
            L.push_back(newNode);
        }
    }
}

/*********************************************************************************
 * @brief 初始化建立书名词典  
 *  
 * 从数据源中读取书籍信息，对书籍名称进行分词处理，并将分词结果作为索引词存储到IndexNode对象链表中。  
 * 最后，将链表中的IndexNode对象保存到文件"../data/index.txt"中。  
 *  
 * @return 无返回值（void）  
 **********************************************************************************/ 
void BuildIndex()//建立书名词典
{
    list<Book> p=b_LordData();
    list<IndexNode> L;
    //IndexNode temp;
    for(list<Book>::const_iterator it = p.begin();it !=p.end();it++)
    {
        AddIndexword((*it).bookname,(*it).id,L);
    }
    i_SaveData(L);
}


