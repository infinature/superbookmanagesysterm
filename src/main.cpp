#include "head.h"

using namespace std;

int main() {
    list<IndexNode> indexList;
    AddIndexword("我是中国人人", 1, indexList);

    // 打印结果
    for (const auto& node : indexList) {
        cout << "Word: " << node.word << ", Book IDs: ";
        for (const auto& id : node.bookid) {
            cout << id << " ";
        }
        cout << endl;
    }
    return 0;
}