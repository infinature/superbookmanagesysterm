#ifndef _INDEX_H
#define _INDEX_H

// #include <bits/stdc++.h>
// #include "Book.h"
// #include "User.h"
#include "head.h"
using namespace std;
class IndexNode     //书名索引的词典节点
{
public:
    string word;        //书名中的词语   
    vector <int> bookid;             //所借书籍序号
    
    IndexNode(){}
    IndexNode(const string &s):word(s){}
    bool operator==(const IndexNode& other) const
    {
        return word == other.word;
    }
    void addBooks(int i)
    {
        bookid.push_back(i);
    }
};

void AddIndexword(const string &name,int id,list<IndexNode>& L);
//void DelIndexword(string name,int id);
list<IndexNode> i_LordData();
vector<int> searchBookW(const string& name);
vector<int> searchBookD(const string& name);
void i_SaveData(list<IndexNode> &p);
void BuildIndex();
#endif //_INDEX_H