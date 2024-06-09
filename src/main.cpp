#include "head.h"

using namespace std;

int main()
{
    char* ch=(char*)"我是人中国人人";
    vector <string> res_str= chinese_io(ch);

    //输出结果向量中的每个汉字
    for (int i = 0; i < res_str.size(); ++i) {
        cout << res_str.at(i);
        cout << endl;
    }
    return 0;
}