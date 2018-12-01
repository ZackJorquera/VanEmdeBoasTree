#pragma once

#include <vector>
#include <cmath>

using namespace std;

class vEB
{
public:
    vEB(size_t minSize)
    {
        int k = int(ceil(log2(log2(minSize))));
        uSize = int(pow(2, pow(2, k)));

        if(uSize > 2)
        {
            summary = new vEB(int(sqrt(double(uSize))));
        
            int clusters = int(sqrt(double(uSize)));
            if (uSize == 2)
                clusters = 2;
            for (int i = 0; i < clusters; i++)
            {
                cluster.push_back(new vEB(int(sqrt(double(uSize)))));
            }
        }
    }
    vEB() {}

    void insert(int x)
    {
        if (uSize == 2)
        {
            data[x] = true;

            if (min == -1)
            {
                min = x;
                max = x;
                return;
            }

            if (x < min)
                min = x;
            if (x > max)
                max = x;
            
            return;
        }

        if (min == -1)
        {
            min = x;
            max = x;
            return;
        }

        if (x < min)
        {
            int temp = min;
            min = x;
            x = temp;//swap x and min
        }
        if (x > max)
        {
            max = x;
        }

        if (cluster[high(x)]->min == -1)
        {
            summary->insert(high(x));
        }

        cluster[high(x)]->insert(low(x));
    }

    int successor(int x)
    {
        if (x < min)
            return min;
        if (x > max)
            return uSize;

        int i = high(x);
        int j;

        if (uSize == 2)
        {
            if (data[1] && x == 0)
                j = 1;
            else
                j = 2;
        }
        else
        {
            if (low(x) < cluster[i]->max)
            {
                j = cluster[i]->successor(low(x));
            }
            else
            {
                i = summary->successor(i);
                if (i >= int(sqrt(double(uSize))))
                    return uSize;
                j = cluster[i]->min;
            }
        }
        return index(i, j);
    }

    int prediccessor(int x)
    {
        if (x > max)
            return max;
        if (x < min)
            return -1;

        int i = high(x);
        int j;

        if (uSize == 2)
        {
            if (data[0] && x == 1)
                j = 0;
            else
                j = -1;
        }
        else
        {
            if (low(x) > cluster[i]->min)
            {
                j = cluster[i]->prediccessor(low(x));
                if (j == -1)
                    j = low(cluster[i]->min);
            }
            else if (high(x) == high(min) && low(x) > low(min))
            {
                /*j = cluster[i]->prediccessor(low(x));
                if (j == -1)
                        j = cluster[i]->min;*/
                j = low(min);
            }
            else
            {
                i = summary->prediccessor(i);
                if (i < 0)
                {
                    if (summary->min != high(x))
                        i = summary->min;
                    else
                        return -1;
                }
                j = cluster[i]->max;
            }
        }
        return index(i, j);
    }

    void deleteValue(int x)
    {
        if (uSize == 2)
        {
            data[x] = false;

            if (min == x && max == x)
            {
                min = -1;
                max = -1;
                return;
            }

            if (min == x)
                min = max;
            else
                max = min;

            return;
        }

        if (x == min)
        {
            int i = summary->min;
            if (i == -1)
            {
                min = -1;
                max = -1;
                return;
            }
            min = index(i, cluster[i]->min);
            x = min;
        }

        cluster[high(x)]->deleteValue(low(x));
        if (cluster[high(x)]->min == -1)
            summary->deleteValue(high(x));

        if (x == max)
        {
            int i = summary->max;
            if (i == -1)
                max = min;
            else
                max = index(i, cluster[i]->max);
        }
    }

    int pop_front()
    {
        int retVal = min;
        deleteValue(min);
        return retVal;
    }

    int pop_back()
    {
        int retVal = max;
        deleteValue(max);
        return retVal;
    }

    bool trySearch(int x)
    {
        if (x == min || x == max)
            return true;
        if (x < min || x > max)
            return false;

        return cluster[high(x)]->trySearch(low(x));

    }

protected:
    int uSize;
    bool data[2] = { false, false };
    int min = -1; // None
    int max = -1;
    vector<vEB*> cluster;
    vEB* summary;
private:

    int index(int i, int j)
    {
        return i * sqrt(double(uSize)) + j;
    }
    int low(int x)
    {
        return x % int(sqrt(double(uSize)));
    }
    int high(int x)
    {
        return int(floor(x / sqrt(double(uSize))));
    }
};
