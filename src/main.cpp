#include "head.h"

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    //BuildIndex();
    //std::locale::global(std::locale(""));
    // User a;
    // string b;
    // lookBook();
    // BorrowBook(a,b);
    string a;
    a=readUTF8FromConsole();
    if(!isValidUTF8)
    cout<<"不是"<<endl;
    else
    cout<<a<<endl;
    return 0;
}