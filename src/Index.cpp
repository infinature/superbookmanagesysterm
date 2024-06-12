#include "Index.h"
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

vector<int> searchBook(const string& name) {
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


// void DelIndexword(string name,int id)
// {
//     list<IndexNode> L=i_LordData();
//     for (auto ch : name)         //ch依次取的是str里面的字符,直到取完为止
//     {
//         IndexNode searchword(ch);//需要删除么
//         list<IndexNode>::iterator temp = find(L.begin(),L.end(),searchword);
//         if(temp!=L.end())
//         {  
//             ((*temp).bookid).erase(std::remove(((*temp).bookid).begin(),((*temp).bookid).end(),id),((*temp).bookid).end());
//         } 
//         if(temp==L.end())
//         {
//             cout<<"无法删除，无存储信息"<<endl;
//         }
//     }
// }
void BuildIndex()//建立书名词典
{
    list<Book> p=b_LordData();
    list<IndexNode> L;
    //IndexNode temp;
    for(list<Book>::const_iterator it = p.begin();it !=p.end();it++)
    {
        AddIndexword((*it).bookname,(*it).id,L);
    //     for (auto ch : (*it).bookname)         //ch依次取的是str里面的字符,直到取完为止
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


