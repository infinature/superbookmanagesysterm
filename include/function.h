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
void BorrowBook(User uk ,string borrowdata );
bool compareBook(Book a,Book b);
list<string> Rank();

#endif //_FUNCTION_H