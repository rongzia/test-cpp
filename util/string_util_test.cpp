//
// Created by rrzhang on 2020/3/22.
//

#include <iostream>
#include "string_util.h"

using namespace std;

int main(){

    RandNum_generator rng('a', 'z');
    cout << StringUtil::Random_string(rng, 10) << endl;
    cout << StringUtil::Random_string(rng, 10) << endl;
    cout << StringUtil::Random_string(rng, 10) << endl;
    cout << StringUtil::Random_string(rng, 10) << endl;
    cout << StringUtil::Random_string(rng, 10) << endl;
    return 0;
}