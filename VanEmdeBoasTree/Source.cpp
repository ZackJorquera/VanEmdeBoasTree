#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>

#include "vEB.hpp"

using namespace std;

void comp();
double timevEBSort(vector<int>& dataArray);
double timeSort(vector<int>& dataArray);


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

    comp();

    cin.get();
}

void comp()
{
    vector<int> dataArray;
    vector<int> dataArray2;

    for (int i = 0; i < 65536; i++)
    {
        dataArray.push_back(i);
    }

    random_shuffle(&dataArray[0], &dataArray[65535]);

    dataArray2 = dataArray;

    auto t1 = timevEBSort(dataArray);
    auto t2 = timeSort(dataArray2);

    cout << "vEB: " << t1 << endl;
    cout << "std: " << t2 << endl;
}

double timevEBSort(vector<int>& dataArray)
{
    //start timer
    std::clock_t start;
    start = std::clock();

    vEB myV(65536);

    for (int i = 0; i < 65536; i++)
    {
        myV.insert(dataArray[i]);
    }

    for (int i = 0; i < 65536; i++)
    {
        dataArray[i] = myV.pop_front();
    }

    //end timer
    double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    return duration;
}

double timeSort(vector<int>& dataArray)
{
    //start timer
    std::clock_t start;
    start = std::clock();

    std::sort(&dataArray[0], &dataArray[65535]);
    
    //end timer
    double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    return duration;
}
