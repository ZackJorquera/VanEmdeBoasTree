#include <iostream>
#include <string>

#include "vEB.hpp"

using namespace std;

int main()
{
    vEB_Vector<string> thisvEB(16);

    thisvEB.insert(3, "3");
    thisvEB.insert(5, "5");
    thisvEB.insert(12, "12");

    auto v1 = *thisvEB.getAfter(6);
    auto v2 = *thisvEB.getBefore(4);
    auto v3 = thisvEB.pop_front();
    auto v4 = thisvEB.pop_back();
    thisvEB.deleteValue(5);
}
