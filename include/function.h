#ifndef _FUNCTION_H
#define _FUNCTION_H

//#include <bits/stdc++.h>
#include "head.h"
//#include "Book.h"
//#include "User.h"
//#include "Index.h"

using namespace std;

class User;
class Borrowed_Book;
class Book;
void BorrowBook(User uk ,string borrowdata ,int kind);
bool compareBook(Book a,Book b);
list<string> Rank();
string getCurrentDateTime();
int daysBetweenDates(const std::string& date1, const std::string& date2);
vector<string> chinese_io(char* ori_c);
char* strToChar(string strSend);
string UTF16ToUTF8(const std::wstring& utf16);
bool isValidUTF8(const std::string& str);
string readUTF8FromConsole();
#endif //_FUNCTION_H