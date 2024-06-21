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



void BorrowBook(User uk ,string borrowdata);
bool compareBook(Book a,Book b);
void Rank();
string getCurrentDateTime();
int daysBetweenDates(const std::string& date1, const std::string& date2);
vector<string> chinese_io(char* ori_c);
char* strToChar(string strSend);
string UTF16ToUTF8(const std::wstring& utf16);
bool isValidUTF8(const std::string& str);
string readUTF8FromConsole();
int getValidIntegerInput(const std::string& prompt);
double getValidDoubleInput(const std::string& prompt);
void changeSystemParameter(int *date,double *cost);
void lordfine();
#endif //_FUNCTION_H