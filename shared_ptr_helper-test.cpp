#include <iostream>
#include "shared_ptr_helper.h"
using namespace std;


int main() {

    std::unordered_map<uint64_t, std::pair<std::weak_ptr<int>, bool>> unorderedMap;
    weak_ptr<int> p;
    unorderedMap.insert(make_pair(1, make_pair(p, false)));

{
    shared_ptr<int> a = GetOrCreateSharedPtr<int>(unorderedMap, 1);
    shared_ptr<int> a2 = a;
    cout << a.use_count() << endl;
}
    cout << unorderedMap.at(1).first.use_count() << endl;

    return 0;
}