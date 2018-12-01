#include <iostream>

#include "vEB.hpp"

using namespace std;

int main()
{
    vEB myV(15);

    myV.insert(1);
    myV.insert(5);
    myV.insert(6);
    myV.insert(7);
    myV.insert(0);
    myV.insert(15);

    int v = myV.prediccessor(-1);
    int v0 = myV.prediccessor(0);
    int v1 = myV.prediccessor(1);
    int v2 = myV.prediccessor(2);
    int v3 = myV.prediccessor(3);
    int v4 = myV.prediccessor(4);
    int v5 = myV.prediccessor(5);
    int v6 = myV.prediccessor(6);
    int v7 = myV.prediccessor(7);
    int v8 = myV.prediccessor(8);
    int v9 = myV.prediccessor(9);
    int v10 = myV.prediccessor(10);
    int v11 = myV.prediccessor(11);
    int v12 = myV.prediccessor(12);
    int v13 = myV.prediccessor(13);
    int v14 = myV.prediccessor(14);
    int v15 = myV.prediccessor(15);
    int v16 = myV.prediccessor(16);

    bool b = myV.trySearch(-1);
    bool b0 = myV.trySearch(0);
    bool b1 = myV.trySearch(1);
    bool b2 = myV.trySearch(2);
    bool b3 = myV.trySearch(3);
    bool b4 = myV.trySearch(4);
    bool b5 = myV.trySearch(5);
    bool b6 = myV.trySearch(6);
    bool b7 = myV.trySearch(7);
    bool b8 = myV.trySearch(8);
    bool b9 = myV.trySearch(9);
    bool b10 = myV.trySearch(10);
    bool b11 = myV.trySearch(11);
    bool b12 = myV.trySearch(12);
    bool b13 = myV.trySearch(13);
    bool b14 = myV.trySearch(14);
    bool b15 = myV.trySearch(15);

    myV.deleteValue(6);

    v5 = myV.successor(5);

    myV.deleteValue(0);

    v1 = myV.pop_back();
    v2 = myV.pop_back();
    v3 = myV.pop_back();
    v4 = myV.pop_back();
    v5 = myV.pop_back();
}
