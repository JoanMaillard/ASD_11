//
// Created by Olivier Cuisenaire on 23.05.20.
//

#include <iostream>
#include "bst.h"

using namespace std;

int main() {

    bst<int> t{};

    for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
        t.insert(i);

    cout << t << endl;

    bst<int> t2{};
    t2.insert(8);
    t2.erase_min();

}