#include "stdafx.h"
#include "CppUnitTest.h"

#include <algorithm>
#include <ctime>
#include <iostream>

#include "../VanEmdeBoasTree/vEB.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
    TEST_CLASS(vEBTester)
    {
    public:
        //TODO: add a test for adding dups
        TEST_METHOD(canInit)
        {
            vEB myV(14);
            myV = vEB(18);
        }

        TEST_METHOD(CanInsertValuesUnder16)
        {
            vEB myV(16);

            myV.insert(6);
            Assert::AreEqual(myV.min, 6);
            Assert::AreEqual(myV.max, 6);

            myV.insert(3);
            Assert::AreEqual(myV.min, 3);

            myV.insert(7);
            Assert::AreEqual(myV.max, 7);

            myV.insert(13);
            Assert::AreEqual(myV.max, 13);

            myV.insert(0);
            Assert::AreEqual(myV.min, 0);

            myV.insert(1);
            Assert::AreNotEqual(myV.min, 1);
            Assert::AreNotEqual(myV.max, 1);

            myV.insert(2);
            myV.insert(4);
            myV.insert(5);
            myV.insert(8);
            myV.insert(9);
            myV.insert(10);
            myV.insert(11);
            myV.insert(12);
            myV.insert(14);
            myV.insert(15);

            try
            {
                myV.insert(-1);
                Assert::Fail();
            }
            catch (...) {}

            try
            {
                myV.insert(16);
                Assert::Fail();
            }
            catch (...) {}
        }

        TEST_METHOD(CanInsertValuesUnder256)
        {
            vEB myV(256);

            myV.insert(6);
            Assert::AreEqual(myV.min, 6);
            Assert::AreEqual(myV.max, 6);

            myV.insert(3);
            Assert::AreEqual(myV.min, 3);

            myV.insert(107);
            Assert::AreEqual(myV.max, 107);

            myV.insert(237);
            Assert::AreEqual(myV.max, 237);

            myV.insert(0);
            Assert::AreEqual(myV.min, 0);

            myV.insert(76);
            Assert::AreNotEqual(myV.min, 1);
            Assert::AreNotEqual(myV.max, 1);
        }

        TEST_METHOD(CanFindSuccessorUnder256)
        {
            vEB myV(256);

            myV.insert(67);
            myV.insert(5);
            myV.insert(101);
            myV.insert(200);
            myV.insert(54);
            myV.insert(255);

            Assert::AreEqual(myV.successor(-1), 5);
            Assert::AreEqual(myV.successor(0), 5);
            Assert::AreEqual(myV.successor(5), 54);
            Assert::AreEqual(myV.successor(60), 67);
            Assert::AreEqual(myV.successor(70), 101);
            Assert::AreEqual(myV.successor(101), 200);
            Assert::AreEqual(myV.successor(237), 255);
        }

        TEST_METHOD(CanFindPrediccessorUnder256)
        {
            vEB myV(256);

            myV.insert(87);
            myV.insert(0);
            myV.insert(5);
            myV.insert(101);
            myV.insert(200);
            myV.insert(54);
            myV.insert(255);

            int v = myV.prediccessor(179);

            Assert::AreEqual(myV.prediccessor(256), 255);
            Assert::AreEqual(myV.prediccessor(255), 200);
            Assert::AreEqual(myV.prediccessor(179), 101);
            Assert::AreEqual(myV.prediccessor(89), 87);
            Assert::AreEqual(myV.prediccessor(87), 54);
            Assert::AreEqual(myV.prediccessor(10), 5);
            Assert::AreEqual(myV.prediccessor(2), 0);
        }

        TEST_METHOD(CanInsertAndSearchUnder256)
        {
            vEB myV(256);

            myV.insert(6);
            myV.insert(3);
            myV.insert(107);
            myV.insert(237);
            myV.insert(0);
            myV.insert(76);
            myV.insert(187);
            myV.insert(255);

            Assert::IsTrue(myV.trySearch(6));
            Assert::IsTrue(myV.trySearch(3));
            Assert::IsTrue(myV.trySearch(107));
            Assert::IsTrue(myV.trySearch(237));
            Assert::IsTrue(myV.trySearch(0));
            Assert::IsTrue(myV.trySearch(76));
            Assert::IsTrue(myV.trySearch(187));
            Assert::IsTrue(myV.trySearch(255));
        }

        TEST_METHOD(CanDeleteValue256)
        {
            vEB myV(256);

            myV.insert(6);
            myV.insert(3);
            myV.insert(107);
            myV.insert(237);
            myV.insert(0);
            myV.insert(76);
            myV.insert(187);
            myV.insert(255);


            myV.deleteValue(0);
            Assert::AreEqual(myV.min, 3);

            myV.deleteValue(255);
            Assert::AreEqual(myV.max, 237);

            Assert::IsFalse(myV.trySearch(0));
            Assert::IsFalse(myV.trySearch(255));

            myV.deleteValue(107);
            Assert::IsFalse(myV.trySearch(107));
            myV.deleteValue(237);
            Assert::IsFalse(myV.trySearch(237));
            Assert::AreEqual(myV.max, 187);
            myV.deleteValue(76);
            Assert::IsFalse(myV.trySearch(76));
            myV.deleteValue(187);
            Assert::IsFalse(myV.trySearch(187));
            Assert::AreEqual(myV.max, 6);
            myV.deleteValue(3);
            Assert::IsFalse(myV.trySearch(3));
            Assert::AreEqual(myV.min, 6);
            myV.deleteValue(6);
            Assert::IsFalse(myV.trySearch(6));
            Assert::AreEqual(myV.min, -1);
            Assert::AreEqual(myV.max, -1);
        }

        TEST_METHOD(CanPopFrontAndBack256)
        {
            vEB myV(256);

            myV.insert(6);
            myV.insert(3);
            myV.insert(107);
            myV.insert(237);
            myV.insert(0);
            myV.insert(76);
            myV.insert(187);
            myV.insert(255);

            Assert::AreEqual(myV.pop_front(), 0);
            Assert::AreEqual(myV.pop_front(), 3);
            Assert::IsFalse(myV.trySearch(0));
            Assert::IsFalse(myV.trySearch(3));

            Assert::AreEqual(myV.pop_back(), 255);
            Assert::AreEqual(myV.pop_back(), 237);
            Assert::IsFalse(myV.trySearch(255));
            Assert::IsFalse(myV.trySearch(237));

            Assert::AreEqual(myV.pop_front(), 6);
            Assert::AreEqual(myV.pop_front(), 76);
            Assert::IsFalse(myV.trySearch(6));
            Assert::IsFalse(myV.trySearch(76));

            Assert::AreEqual(myV.pop_back(), 187);
            Assert::AreEqual(myV.pop_back(), 107);
            Assert::IsFalse(myV.trySearch(187));
            Assert::IsFalse(myV.trySearch(107));


            Assert::AreEqual(myV.min, -1);
            Assert::AreEqual(myV.max, -1);
        }

        TEST_METHOD(CanSort256)
        {
            int a[] = { 4,3,6,7,1,2,8,5,9,2,48,12,23,255,32,16,87,213,187,76,33,56,55,0,49 };

            vEB myV(256);

            for (int i = 0; i < 25; i++)
            {
                myV.insert(a[i]);
            }

            int last = myV.pop_front();

            for (int i = 0; i < 25 - 1; i++)
            {
                int v = myV.pop_front();
                Assert::IsFalse(last > v);
                last = v;
            }



            for (int i = 0; i < 25; i++)
            {
                myV.insert(a[i]);
            }

            last = myV.pop_back();

            for (int i = 0; i < 25 - 1; i++)
            {
                int v = myV.pop_back();
                Assert::IsFalse(last < v);
                last = v;
            }
        }

        TEST_METHOD(StressTestLessThen1sec)
        {
            int * dataArray = new int[65536];

            for (int i = 0; i < 65536; i++)
            {
                dataArray[i] = i; //any dups will be removed
            }

            random_shuffle(&dataArray[0], &dataArray[65535]);
            
            //start timer
            std::clock_t start;
            start = std::clock();
            //

            vEB myV(65536);

            for (int i = 0; i < 65536; i++)
            {
                myV.insert(dataArray[i]);
            }

            int last = myV.pop_front();

            for (int i = 0; i < 65536 - 1; i++)
            {
                try
                {
                    int v = myV.pop_front();

                    if (v == -1)
                        break;

                    if (last > v)
                        Assert::IsFalse(last > v);
                    last = v;
                }
                catch (...) {}
            }

            //end timer
            double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
            //print time
            Assert::IsTrue(duration < 1);
        }
    };
}
