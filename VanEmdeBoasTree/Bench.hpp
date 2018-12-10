#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

#include "vEB.hpp"

using namespace std;

//void WriteDataLine(int n, double time, ofstream* fs);
//vector<pair<int, double>> BenchSortingByN(int maxN, int stepSize);
//double timevEBSort(vector<int>& dataArray);

double timevEBSort(vector<int>& dataArray)
{
    //start timer
    std::clock_t start;
    start = std::clock();

    vEB myV(dataArray.size());

    for (size_t i = 0; i < dataArray.size(); i++)
    {
        myV.insert(dataArray[i]);
    }

    for (size_t i = 0; i < dataArray.size(); i++)
    {
        dataArray[i] = myV.pop_front();//This works on the assumption that the sort works
    }

    //end timer
    double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    return duration;
}

double timevEBInsertAve(int n)
{
    vEB myV(n);

    double totalDuration = 0;

    std::clock_t start;
    start = std::clock();

    for (int i = 0; i < n; i++)
    {
        myV.insert(i);
    }

    totalDuration += (std::clock() - start) / (double)CLOCKS_PER_SEC;

    return totalDuration / n;
}

void WriteDataLine(int n, double time, double time2, ofstream* fs)
{
    string toWrite = to_string(n) + "," + to_string(time) + "," + to_string(time2) + "\n";

    fs->write(toWrite.c_str(), toWrite.size());
}

vector<pair<int, double>> BenchInsertByN(int maxN, int stepSize)//sorts using insert and pop_front
{
    vector<pair<int, double>> retVec;

    for (int i = 0; i < maxN; i += stepSize)
    {        
        double time = timevEBInsertAve(i + 1);
        retVec.push_back(pair<int, double>(i, time));
    }

    return retVec;
}

vector<pair<int, double>> BenchSortingByN(int maxN, int stepSize)//sorts using insert and pop_front
{
    vector<pair<int, double>> retVec;

    vector<int> values;

    for (int i = 0; i < maxN; i++)
    {
        values.push_back(i);

        if (i % stepSize == 0)
        {
            if (i < 2)
                retVec.push_back(pair<int, double>(i, 0));
            else
            {
                double time = timevEBSort(values);
                retVec.push_back(pair<int, double>(i, time));
            }
        }
    }

    return retVec;
}

void BenchvEBPerformanceAndWriteToFile(string fileName)
{
    vector<pair<int, double>> retVec = BenchSortingByN(100000, 100);
    vector<pair<int, double>> retVec2 = BenchInsertByN(100000, 100);

    ofstream fs(fileName);

    fs.write("n,SortTime,InsertTime\n", 22);

    for (size_t i = 0; i < retVec.size(); i++)
    {
        WriteDataLine(retVec[i].first, retVec[i].second, retVec2[i].second, &fs);
    }

    fs.close();
}
