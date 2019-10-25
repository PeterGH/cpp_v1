#ifndef _STRUCTURETEST_H_
#define _STRUCTURETEST_H_

#include "Structure.h"
#include "Test.h"

using namespace Test;

class StructureTest : public TestClass
{
public:
    StructureTest(Log &log) : TestClass(log) {}
    ~StructureTest(void) {}
    void Init(void);
};

void StructureTest::Init(void)
{
    Add("1-bit", [&]() {
        BitSet m(1);
        bitset<1> b;
        m.Set(0);
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.set(0);
        ASSERT2(m.Test(0), "Bit 0 != 1");
        ASSERT1(m.Test(0) == b.test(0));
        ASSERT2(m.Count() == 1, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == true);
        m.Reset(0);
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.reset(0);
        ASSERT2(!m.Test(0), "Bit 0 != 0");
        ASSERT1(m.Test(0) == b.test(0));
        ASSERT2(m.Count() == 0, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
        m.Set();
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.set();
        ASSERT2(m.Test(0), "Bit 0 != 1");
        ASSERT1(m.Test(0) == b.test(0));
        ASSERT2(m.Count() == 1, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == true);
        m.Reset();
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.reset();
        ASSERT2(!m.Test(0), "Bit 0 != 0");
        ASSERT1(m.Test(0) == b.test(0));
        ASSERT2(m.Count() == 0, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
        m.Flip();
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.flip();
        ASSERT2(m.Test(0), "Bit 0 != 1");
        ASSERT1(m.Test(0) == b.test(0));
        ASSERT2(m.Count() == 1, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == true);
        m.Flip(0);
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.flip(0);
        ASSERT2(!m.Test(0), "Bit 0 != 0");
        ASSERT1(m.Test(0) == b.test(0));
        ASSERT2(m.Count() == 0, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
    });

    Add("32-bit", [&]() {
        BitSet m(32);
        bitset<32> b;
        m.Set(0);
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.set(0);
        ASSERT2(m.Test(0), "Bit 0 != 1");
        ASSERT1(m.Test(0) == b.test(0));
        ASSERT2(m.Count() == 1, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == true);
        m.Set(11);
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.set(11);
        ASSERT2(m.Test(11), "Bit 11 != 1");
        ASSERT1(m.Test(11) == b.test(11));
        ASSERT2(m.Count() == 2, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
        m.Flip(11);
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.flip(11);
        ASSERT2(!m.Test(11), "Bit 11 != 0");
        ASSERT1(m.Test(11) == b.test(11));
        ASSERT2(m.Count() == 1, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == true);
        m.Set(23);
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.set(23);
        ASSERT2(m.Test(23), "Bit 23 != 1");
        ASSERT1(m.Test(23) == b.test(23));
        ASSERT2(m.Count() == 2, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
        m.Set(31);
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.set(31);
        ASSERT2(m.Test(31), "Bit 31 != 1");
        ASSERT1(m.Test(31) == b.test(31));
        ASSERT2(m.Count() == 3, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
        m.Flip(31);
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.flip(31);
        ASSERT2(!m.Test(31), "Bit 31 != 0");
        ASSERT1(m.Test(31) == b.test(31));
        ASSERT2(m.Count() == 2, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
        m.Flip(31);
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.flip(31);
        ASSERT2(m.Test(31), "Bit 31 != 1");
        ASSERT1(m.Test(31) == b.test(31));
        ASSERT2(m.Count() == 3, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
        m.Reset();
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.reset();
        ASSERT2(!m.Any(), "Mask is set");
        ASSERT1(m.Any() == b.any());
        ASSERT2(m.Count() == 0, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
        m.Set();
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.set();
        ASSERT2(m.All(), "Mask is not set");
        ASSERT1(m.All() == b.all());
        ASSERT2(m.Count() == 32, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
        m.Flip();
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.flip();
        ASSERT2(!m.All(), "Mask is not set");
        ASSERT1(m.All() == b.all());
        ASSERT2(m.Count() == 0, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
    });

    Add("40-bit", [&]() {
        BitSet m(40);
        bitset<40> b;
        m.Set(0);
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.set(0);
        ASSERT2(m.Test(0), "Bit 0 != 1");
        ASSERT1(m.Test(0) == b.test(0));
        ASSERT2(m.Count() == 1, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == true);
        m.Set(11);
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.set(11);
        ASSERT2(m.Test(11), "Bit 11 != 1");
        ASSERT1(m.Test(11) == b.test(11));
        ASSERT2(m.Count() == 2, String::Format("Count = [%d]", m.Count()));
        m.Set(23);
        ASSERT1(m.IsPower2() == false);
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.set(23);
        ASSERT2(m.Test(23), "Bit 23 != 1");
        ASSERT1(m.Test(23) == b.test(23));
        ASSERT2(m.Count() == 3, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
        m.Set(31);
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.set(31);
        ASSERT2(m.Test(31), "Bit 31 != 1");
        ASSERT1(m.Test(31) == b.test(31));
        ASSERT2(m.Count() == 4, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
        m.Set(32);
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.set(32);
        ASSERT2(m.Test(32), "Bit 32 != 1");
        ASSERT1(m.Test(32) == b.test(32));
        ASSERT2(m.Count() == 5, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
        m.Set(39);
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.set(39);
        ASSERT2(m.Test(39), "Bit 39 != 1");
        ASSERT1(m.Test(39) == b.test(39));
        ASSERT2(m.Count() == 6, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
        m.Flip(39);
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.flip(39);
        ASSERT2(!m.Test(39), "Bit 39 != 0");
        ASSERT1(m.Test(39) == b.test(39));
        ASSERT2(m.Count() == 5, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
        m.Flip();
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.flip();
        ASSERT2(m.Test(39), "Bit 39 != 1");
        ASSERT1(m.Test(39) == b.test(39));
        ASSERT2(m.Count() == 35, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
        m.Reset();
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.reset();
        ASSERT2(!m.Any(), "Mask is set");
        ASSERT1(m.Any() == b.any());
        ASSERT2(m.Count() == 0, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
        m.Set();
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.set();
        ASSERT2(m.All(), "Mask is not set");
        ASSERT1(m.All() == b.all());
        ASSERT2(m.Count() == 40, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
    });

    Add("41-bit", [&]() {
        BitSet m(41);
        bitset<41> b;
        m.Set(0);
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.set(0);
        ASSERT2(m.Test(0), "Bit 0 != 1");
        ASSERT1(m.Test(0) == b.test(0));
        ASSERT2(m.Count() == 1, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == true);
        m.Set(11);
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.set(11);
        ASSERT2(m.Test(11), "Bit 11 != 1");
        ASSERT1(m.Test(11) == b.test(11));
        ASSERT2(m.Count() == 2, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
        m.Set(23);
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.set(23);
        ASSERT2(m.Test(23), "Bit 23 != 1");
        ASSERT1(m.Test(23) == b.test(23));
        ASSERT2(m.Count() == 3, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
        m.Set(31);
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.set(31);
        ASSERT2(m.Test(31), "Bit 31 != 1");
        ASSERT1(m.Test(31) == b.test(31));
        ASSERT2(m.Count() == 4, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
        m.Set(32);
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.set(32);
        ASSERT2(m.Test(32), "Bit 32 != 1");
        ASSERT1(m.Test(32) == b.test(32));
        ASSERT2(m.Count() == 5, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
        m.Set(39);
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.set(39);
        ASSERT2(m.Test(39), "Bit 39 != 1");
        ASSERT1(m.Test(39) == b.test(39));
        ASSERT2(m.Count() == 6, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
        m.Set(40);
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.set(40);
        ASSERT2(m.Test(40), "Bit 40 != 1");
        ASSERT1(m.Test(40) == b.test(40));
        ASSERT2(m.Count() == 7, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
        m.Reset();
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.reset();
        ASSERT2(!m.Any(), "Mask is set");
        ASSERT1(m.Any() == b.any());
        ASSERT2(m.Count() == 0, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
        m.Set();
        Logger().WriteInformation("%s\n", m.ToString().c_str());
        b.set();
        ASSERT2(m.All(), "Mask is not set");
        ASSERT1(m.All() == b.all());
        ASSERT2(m.Count() == 41, String::Format("Count = [%d]", m.Count()));
        ASSERT1(m.IsPower2() == false);
    });

    Add("LeftShift", [&]() {
        {
            Logger().WriteInformation("\n");
            BitSet m(2);
            m.Set(0);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(m.Test(0));
            ASSERT1(!m.Test(1));

            m.LeftShift(0);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(m.Test(0));
            ASSERT1(!m.Test(1));

            m.LeftShift(1);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(!m.Test(0));
            ASSERT1(m.Test(1));

            m.LeftShift(1);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(!m.Test(0));
            ASSERT1(!m.Test(1));
        }
        {
            Logger().WriteInformation("\n");
            BitSet m(2);
            m.Set();
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(m.Test(0));
            ASSERT1(m.Test(1));

            m.LeftShift(0);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(m.Test(0));
            ASSERT1(m.Test(1));

            m.LeftShift(1);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(!m.Test(0));
            ASSERT1(m.Test(1));

            m.LeftShift(1);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(!m.Test(0));
            ASSERT1(!m.Test(1));
        }
        {
            Logger().WriteInformation("\n");
            BitSet m(3);
            m.Set(0);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(m.Test(0));
            ASSERT1(!m.Test(1));
            ASSERT1(!m.Test(2));

            m.LeftShift(0);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(m.Test(0));
            ASSERT1(!m.Test(1));
            ASSERT1(!m.Test(2));

            m.LeftShift(1);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(!m.Test(0));
            ASSERT1(m.Test(1));
            ASSERT1(!m.Test(2));

            m.LeftShift(1);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(!m.Test(0));
            ASSERT1(!m.Test(1));
            ASSERT1(m.Test(2));

            m.LeftShift(1);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(!m.Test(0));
            ASSERT1(!m.Test(1));
            ASSERT1(!m.Test(2));
        }
        {
            Logger().WriteInformation("\n");
            BitSet m(3);
            m.Set();
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(m.Test(0));
            ASSERT1(m.Test(1));
            ASSERT1(m.Test(2));

            m.LeftShift(1);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(!m.Test(0));
            ASSERT1(m.Test(1));
            ASSERT1(m.Test(2));

            m.LeftShift(1);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(!m.Test(0));
            ASSERT1(!m.Test(1));
            ASSERT1(m.Test(2));

            m.LeftShift(1);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(!m.Test(0));
            ASSERT1(!m.Test(1));
            ASSERT1(!m.Test(2));
        }
        {
            Logger().WriteInformation("\n");
            BitSet m(3);
            m.Set(0);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(m.Test(0));
            ASSERT1(!m.Test(1));
            ASSERT1(!m.Test(2));

            m.LeftShift(2);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(!m.Test(0));
            ASSERT1(!m.Test(1));
            ASSERT1(m.Test(2));

            m.LeftShift(1);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(!m.Test(0));
            ASSERT1(!m.Test(1));
            ASSERT1(!m.Test(2));
        }
        {
            Logger().WriteInformation("\n");
            BitSet m(3);
            m.Set();
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(m.Test(0));
            ASSERT1(m.Test(1));
            ASSERT1(m.Test(2));

            m.LeftShift(2);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(!m.Test(0));
            ASSERT1(!m.Test(1));
            ASSERT1(m.Test(2));

            m.LeftShift(1);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(!m.Test(0));
            ASSERT1(!m.Test(1));
            ASSERT1(!m.Test(2));
        }
        {
            Logger().WriteInformation("\n");
            BitSet m(32);
            m.Set(0);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(m.Test(0));
            for (int i = 1; i < 32; i++)
            {
                ASSERT1(!m.Test(i));
            }

            m.LeftShift(31);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 0; i < 31; i++)
            {
                ASSERT1(!m.Test(i));
            }
            ASSERT1(m.Test(31));

            m.LeftShift(1);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 0; i < 32; i++)
            {
                ASSERT1(!m.Test(i));
            }
        }
        {
            Logger().WriteInformation("\n");
            BitSet m(32);
            m.Set();
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 0; i < 32; i++)
            {
                ASSERT1(m.Test(i));
            }

            m.LeftShift(3);
            ASSERT1(!m.Test(0));
            ASSERT1(!m.Test(1));
            ASSERT1(!m.Test(2));
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 3; i < 32; i++)
            {
                ASSERT1(m.Test(i));
            }

            m.LeftShift(10);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 0; i < 13; i++)
            {
                ASSERT1(!m.Test(i));
            }
            for (int i = 13; i < 32; i++)
            {
                ASSERT1(m.Test(i));
            }
        }
        {
            Logger().WriteInformation("\n");
            BitSet m(32);
            m.Set();
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 0; i < 32; i++)
            {
                ASSERT1(m.Test(i));
            }

            m.LeftShift(31);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 0; i < 31; i++)
            {
                ASSERT1(!m.Test(i));
            }
            ASSERT1(m.Test(31));

            m.LeftShift(1);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 0; i < 32; i++)
            {
                ASSERT1(!m.Test(i));
            }
        }
        {
            Logger().WriteInformation("\n");
            BitSet m(33);
            m.Set(0);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(m.Test(0));
            for (int i = 1; i < 33; i++)
            {
                ASSERT1(!m.Test(i));
            }

            m.LeftShift(32);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 0; i < 32; i++)
            {
                ASSERT1(!m.Test(i));
            }
            ASSERT1(m.Test(32));

            m.LeftShift(1);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 0; i < 33; i++)
            {
                ASSERT1(!m.Test(i));
            }
        }
        {
            Logger().WriteInformation("\n");
            BitSet m(33);
            m.Set();
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 0; i < 33; i++)
            {
                ASSERT1(m.Test(i));
            }

            m.LeftShift(20);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 0; i < 20; i++)
            {
                ASSERT1(!m.Test(i));
            }
            for (int i = 20; i < 32; i++)
            {
                ASSERT1(m.Test(i));
            }

            m.LeftShift(10);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 0; i < 30; i++)
            {
                ASSERT1(!m.Test(i));
            }
            for (int i = 30; i < 32; i++)
            {
                ASSERT1(m.Test(i));
            }
        }
        {
            Logger().WriteInformation("\n");
            BitSet m(33);
            m.Set();
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 0; i < 33; i++)
            {
                ASSERT1(m.Test(i));
            }

            m.LeftShift(32);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 0; i < 32; i++)
            {
                ASSERT1(!m.Test(i));
            }
            ASSERT1(m.Test(32));

            m.LeftShift(1);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 0; i < 33; i++)
            {
                ASSERT1(!m.Test(i));
            }
        }
        {
            Logger().WriteInformation("\n");
            BitSet m(66);
            m.Set();
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 0; i < 66; i++)
            {
                ASSERT1(m.Test(i));
            }

            m.LeftShift(33);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 0; i < 33; i++)
            {
                ASSERT1(!m.Test(i));
            }
            for (int i = 33; i < 66; i++)
            {
                ASSERT1(m.Test(i));
            }

            m.LeftShift(33);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 0; i < 66; i++)
            {
                ASSERT1(!m.Test(i));
            }
        }
    });

    Add("Reverse", [&]() {
        auto check = [&](unsigned int n, unsigned int e) {
            BitSet::Reverse(n);
            ASSERT1(e == n);
        };

        check(1, 0x80000000);
        check(2, 0x40000000);
        check(4, 0x20000000);
        check(8, 0x10000000);
        check(16, 0x08000000);
        check(256, 0x00800000);
        check(0x00010000, 0x00008000);
        check(0x80000000, 1);
        check(0x40000000, 2);
        check(0x20000000, 4);
        check(0x10000000, 8);
        check(0x08000000, 16);
        check(0x00800000, 256);
        check(0x00008000, 0x00010000);
    });

    Add("Reverse2", [&]() {
        {
            Logger().WriteInformation("\n");
            BitSet m(1);
            m.Set();
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(m.Test(0));

            m.Reverse();
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(m.Test(0));
        }
        {
            Logger().WriteInformation("\n");
            BitSet m(2);
            m.Set(0);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(m.Test(0));
            ASSERT1(!m.Test(1));

            m.Reverse();
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(!m.Test(0));
            ASSERT1(m.Test(1));

            m.Set(0);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(m.Test(0));
            ASSERT1(m.Test(1));

            m.Reverse();
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(m.Test(0));
            ASSERT1(m.Test(1));
        }
        {
            Logger().WriteInformation("\n");
            BitSet m(3);
            m.Set(0);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(m.Test(0));
            ASSERT1(!m.Test(1));
            ASSERT1(!m.Test(2));

            m.Reverse();
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(!m.Test(0));
            ASSERT1(!m.Test(1));
            ASSERT1(m.Test(2));

            m.Set(1);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(!m.Test(0));
            ASSERT1(m.Test(1));
            ASSERT1(m.Test(2));

            m.Reverse();
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(m.Test(0));
            ASSERT1(m.Test(1));
            ASSERT1(!m.Test(2));

            m.Set(2);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(m.Test(0));
            ASSERT1(m.Test(1));
            ASSERT1(m.Test(2));

            m.Reverse();
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(m.Test(0));
            ASSERT1(m.Test(1));
            ASSERT1(m.Test(2));
        }
        {
            Logger().WriteInformation("\n");
            BitSet m(4);
            m.Set(0);
            m.Set(2);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(m.Test(0));
            ASSERT1(!m.Test(1));
            ASSERT1(m.Test(2));
            ASSERT1(!m.Test(3));

            m.Reverse();
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(!m.Test(0));
            ASSERT1(m.Test(1));
            ASSERT1(!m.Test(2));
            ASSERT1(m.Test(3));
        }
        {
            Logger().WriteInformation("\n");
            BitSet m(5);
            m.Set(0);
            m.Set(2);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(m.Test(0));
            ASSERT1(!m.Test(1));
            ASSERT1(m.Test(2));
            ASSERT1(!m.Test(3));
            ASSERT1(!m.Test(4));

            m.Reverse();
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(!m.Test(0));
            ASSERT1(!m.Test(1));
            ASSERT1(m.Test(2));
            ASSERT1(!m.Test(3));
            ASSERT1(m.Test(4));

            m.Reverse();
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(m.Test(0));
            ASSERT1(!m.Test(1));
            ASSERT1(m.Test(2));
            ASSERT1(!m.Test(3));
            ASSERT1(!m.Test(4));
        }
        {
            Logger().WriteInformation("\n");
            BitSet m(6);
            m.Set(3);
            m.Set(5);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(!m.Test(0));
            ASSERT1(!m.Test(1));
            ASSERT1(!m.Test(2));
            ASSERT1(m.Test(3));
            ASSERT1(!m.Test(4));
            ASSERT1(m.Test(5));

            m.Reverse();
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(m.Test(0));
            ASSERT1(!m.Test(1));
            ASSERT1(m.Test(2));
            ASSERT1(!m.Test(3));
            ASSERT1(!m.Test(4));
            ASSERT1(!m.Test(5));
        }
        {
            Logger().WriteInformation("\n");
            BitSet m(32);
            m.Set(31);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 0; i < 31; i++)
            {
                ASSERT1(!m.Test(i));
            }
            ASSERT1(m.Test(31));

            m.Reverse();
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 1; i < 32; i++)
            {
                ASSERT1(!m.Test(i));
            }
            ASSERT1(m.Test(0));
        }
        {
            Logger().WriteInformation("\n");
            BitSet m(33);
            m.Set(31);
            m.Set(32);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 0; i < 31; i++)
            {
                ASSERT1(!m.Test(i));
            }
            ASSERT1(m.Test(31));
            ASSERT1(m.Test(32));

            m.Reverse();
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 2; i < 32; i++)
            {
                ASSERT1(!m.Test(i));
            }
            ASSERT1(m.Test(0));
            ASSERT1(m.Test(1));
        }
        {
            Logger().WriteInformation("\n");
            BitSet m(64);
            m.Set(31);
            m.Set(63);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 0; i < 31; i++)
            {
                ASSERT1(!m.Test(i));
            }
            ASSERT1(m.Test(31));
            for (int i = 32; i < 63; i++)
            {
                ASSERT1(!m.Test(i));
            }
            ASSERT1(m.Test(63));

            m.Reverse();
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 1; i < 32; i++)
            {
                ASSERT1(!m.Test(i));
            }
            ASSERT1(m.Test(0));
            for (int i = 33; i < 64; i++)
            {
                ASSERT1(!m.Test(i));
            }
            ASSERT1(m.Test(32));
        }
        {
            Logger().WriteInformation("\n");
            BitSet m(65);
            m.Set(31);
            m.Set(63);
            m.Set(64);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 0; i < 31; i++)
            {
                ASSERT1(!m.Test(i));
            }
            ASSERT1(m.Test(31));
            for (int i = 32; i < 63; i++)
            {
                ASSERT1(!m.Test(i));
            }
            ASSERT1(m.Test(63));
            ASSERT1(m.Test(64));

            m.Reverse();
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 2; i < 33; i++)
            {
                ASSERT1(!m.Test(i));
            }
            ASSERT1(m.Test(0));
            ASSERT1(m.Test(1));
            for (int i = 34; i < 65; i++)
            {
                ASSERT1(!m.Test(i));
            }
            ASSERT1(m.Test(33));
        }
        {
            Logger().WriteInformation("\n");
            BitSet m(96);
            m.Set(31);
            m.Set(63);
            m.Set(95);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 0; i < 31; i++)
            {
                ASSERT1(!m.Test(i));
            }
            ASSERT1(m.Test(31));
            for (int i = 32; i < 63; i++)
            {
                ASSERT1(!m.Test(i));
            }
            ASSERT1(m.Test(63));
            for (int i = 64; i < 95; i++)
            {
                ASSERT1(!m.Test(i));
            }
            ASSERT1(m.Test(95));

            m.Reverse();
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            for (int i = 1; i < 32; i++)
            {
                ASSERT1(!m.Test(i));
            }
            ASSERT1(m.Test(0));
            for (int i = 33; i < 64; i++)
            {
                ASSERT1(!m.Test(i));
            }
            ASSERT1(m.Test(32));
            for (int i = 65; i < 96; i++)
            {
                ASSERT1(!m.Test(i));
            }
            ASSERT1(m.Test(64));
        }
    });

    Add("IsPower2", [&]() {
        BitSet m(100);
        for (int i = 0; i < 100; i++)
        {
            if (i > 0)
                m.Reset(i - 1);
            m.Set(i);
            Logger().WriteInformation("%s\n", m.ToString().c_str());
            ASSERT1(m.IsPower2());
        }
    });

    Add("LRUCache", [&]() {
        {
            Logger().WriteInformation("Cache(1)\n");
            LRUCache cache(1);

            int v = cache.Get(0);
            ASSERT1(v == -1);

            Logger().WriteInformation("Set(1, 1)\n");
            cache.Set(1, 1);
            v = cache.Get(0);
            ASSERT1(v == -1);
            v = cache.Get(1);
            ASSERT1(v == 1);

            Logger().WriteInformation("Set(2, 2)\n");
            cache.Set(2, 2);
            v = cache.Get(1);
            ASSERT1(v == -1);
            v = cache.Get(2);
            ASSERT1(v == 2);

            Logger().WriteInformation("Set(3, 3)\n");
            cache.Set(3, 3);
            v = cache.Get(2);
            ASSERT1(v == -1);
            v = cache.Get(3);
            ASSERT1(v == 3);

            Logger().WriteInformation("Set(3, 33)\n");
            cache.Set(3, 33);
            v = cache.Get(2);
            ASSERT1(v == -1);
            v = cache.Get(3);
            ASSERT1(v == 33);
        }
        {
            Logger().WriteInformation("Cache(2)\n");
            LRUCache cache(2);

            int v = cache.Get(0);
            ASSERT1(v == -1);

            Logger().WriteInformation("Set(1, 1)\n");
            cache.Set(1, 1);
            v = cache.Get(0);
            ASSERT1(v == -1);
            v = cache.Get(1);
            ASSERT1(v == 1);

            Logger().WriteInformation("Set(2, 2)\n");
            cache.Set(2, 2);
            v = cache.Get(0);
            ASSERT1(v == -1);
            v = cache.Get(1);
            ASSERT1(v == 1);
            v = cache.Get(2);
            ASSERT1(v == 2);

            Logger().WriteInformation("Set(3, 3)\n");
            cache.Set(3, 3);
            v = cache.Get(1);
            ASSERT1(v == -1);
            v = cache.Get(2);
            ASSERT1(v == 2);
            v = cache.Get(3);
            ASSERT1(v == 3);

            v = cache.Get(2);
            ASSERT1(v == 2);

            Logger().WriteInformation("Set(4, 4)\n");
            cache.Set(4, 4);
            v = cache.Get(1);
            ASSERT1(v == -1);
            v = cache.Get(2);
            ASSERT1(v == 2);
            v = cache.Get(3);
            ASSERT1(v == -1);
            v = cache.Get(4);
            ASSERT1(v == 4);

            Logger().WriteInformation("Set(2, 22)\n");
            cache.Set(2, 22);
            v = cache.Get(1);
            ASSERT1(v == -1);
            v = cache.Get(2);
            ASSERT1(v == 22);
            v = cache.Get(3);
            ASSERT1(v == -1);
            v = cache.Get(4);
            ASSERT1(v == 4);
        }
    });

    Add("Matrix", [&]() {
        Matrix<int> B(3, 4);
        Logger().Print(B);
        B(1, 2) = 101;
        Logger().Print(B, "%d", "\t");
        int v = B(1, 2);
        ASSERT1(101 == v);
        B(2, 3) = 202;
        auto p = [&](Log &l, int &x) { l.WriteInformation("%d", x); };
        Logger().Print<int>(B, p, "\t");
        v = B(2, 3);
        ASSERT1(202 == v);
        const int w = B(2, 3);
        ASSERT1(202 == w);
        v = 203;
        Logger().Print(B, "%d", "\t");
        ASSERT1(202 == B(2, 3));
        int &x = B(2, 3);
        x = 204;
        Logger().Print(B, "%d", "\t");
        ASSERT1(204 == B(2, 3));
    });

    Add("LowerTriangularMatrix", [&]() {
        LowerTriangularMatrix<int> B(4, 3);
        Logger().Print(B);
        B(2, 1) = 101;
        Logger().Print(B, "%d", "\t");
        int v = B(2, 1);
        ASSERT1(101 == v);
        B(3, 2) = 202;
        auto p = [&](Log &l, int x) { l.WriteInformation("%d", x); };
        Logger().Print<int>(B, p, "\t");
        v = B(3, 2);
        ASSERT1(202 == v);
        const int w = B(3, 2);
        ASSERT1(202 == w);
        ASSERTERROR(B(0, 1) = 0, invalid_argument);
        const LowerTriangularMatrix<int> A(4, 3);
        ASSERT1(A(0, 1) == 0);
        LowerTriangularMatrix<int> C(4, 5);
        Logger().Print(C);
        C(2, 1) = 101;
        Logger().Print(C, "%d", "\t");
        v = C(2, 1);
        ASSERT1(101 == v);
        C(3, 2) = 202;
        Logger().Print<int>(C, p, "\t");
        v = C(3, 2);
        ASSERT1(202 == v);
        const int y = C(3, 2);
        ASSERT1(202 == y);
        ASSERTERROR(C(0, 1) = 0, invalid_argument);
        const LowerTriangularMatrix<int> D(4, 5);
        ASSERT1(D(0, 1) == 0);
    });

    Add("UpperTriangularMatrix", [&]() {
        UpperTriangularMatrix<int> B(3, 4);
        Logger().Print(B);
        B(1, 2) = 101;
        Logger().Print(B, "%d", "\t");
        int v = B(1, 2);
        ASSERT1(101 == v);
        B(2, 3) = 202;
        auto p = [&](Log &l, int x) { l.WriteInformation("%d", x); };
        Logger().Print<int>(B, p, "\t");
        v = B(2, 3);
        ASSERT1(202 == v);
        const int w = B(2, 3);
        ASSERT1(202 == w);
        ASSERTERROR(B(1, 0) = 0, invalid_argument);
        const UpperTriangularMatrix<int> A(3, 4);
        ASSERT1(A(1, 0) == 0);
        UpperTriangularMatrix<int> C(5, 4);
        Logger().Print(C);
        C(1, 2) = 101;
        Logger().Print(C, "%d", "\t");
        v = C(1, 2);
        ASSERT1(101 == v);
        C(2, 3) = 202;
        Logger().Print<int>(C, p, "\t");
        v = C(2, 3);
        ASSERT1(202 == v);
        const int y = C(2, 3);
        ASSERT1(202 == y);
        ASSERTERROR(C(1, 0) = 0, invalid_argument);
        const UpperTriangularMatrix<int> D(5, 4);
        ASSERT1(D(1, 0) == 0);
    });

    Add("MRInteger1", [&]() {
        auto check = [&](MRInteger &c, unsigned int e0, unsigned int e1, unsigned int e2) -> void {
            ASSERT1(e0 == c[0]);
            ASSERT1(e1 == c[1]);
            ASSERT1(e2 == c[2]);
        };

        unsigned int c[] = {1, 3, 2};

        MRInteger ctr(c, 3);
        ASSERT1(6 == (int)ctr.Max());
        check(ctr, 0, 0, 0);

        ctr++;
        check(ctr, 0, 1, 0);

        ++ctr;
        check(ctr, 0, 2, 0);

        MRInteger ctr2 = ctr;
        check(ctr2, 0, 2, 0);

        ctr2++;
        ++ctr2;
        check(ctr2, 0, 1, 1);

        ctr2++;
        ++ctr2;
        check(ctr2, 0, 0, 0);

        ctr2++;
        ++ctr2;
        check(ctr2, 0, 2, 0);

        MRInteger ctr3(ctr2);
        check(ctr3, 0, 2, 0);

        ctr = ctr3++;
        check(ctr, 0, 2, 0);
        check(ctr3, 0, 0, 1);

        ctr3.Reset();
        check(ctr3, 0, 0, 0);

        MRInteger ctr4(ctr3);
        check(ctr4, 0, 0, 0);

        ctr4 = MRInteger(ctr);
        check(ctr4, 0, 2, 0);
    });

    Add("MRInteger2", [&]() {
        unsigned int c[] = {1, 3, 2};
        MRInteger ctr(c, 3);

        unsigned int c1[] = {1, 3, 2, 1};
        MRInteger ctr1(c1, 4);

        ASSERT1(!(ctr < ctr1));
        ASSERT1(!(ctr1 < ctr));
        ASSERT1(ctr == ctr1);
        ASSERT1(ctr1 == ctr);
        ASSERT1(!(ctr != ctr1));
        ASSERT1(!(ctr1 != ctr));
    });

    Add("MRInteger3", [&]() {
        unsigned int c[] = {3, 3, 3};
        MRInteger ctr(c, 3);

        unsigned int c1[] = {3, 3, 3, 3};
        MRInteger ctr1(c1, 4);

        ctr++;
        ASSERT1(ctr > ctr1);
        ASSERT1(!(ctr1 > ctr));
        ctr1++;
        ctr1++;
        ASSERT1(!(ctr > ctr1));
        ASSERT1(ctr <= ctr1);
        ASSERT1(ctr1 > ctr);
        ASSERT1(!(ctr1 <= ctr));

        unsigned int d[] = {0, 1, 1};
        unsigned int d1[] = {0, 1, 1, 1};
        ctr.Set(d, 3);
        ctr1.Set(d1, 4);
        ASSERT1(ctr1 > ctr);
        ASSERT1(!(ctr1 <= ctr));
        ASSERT1(!(ctr > ctr1));
        ASSERT1(ctr <= ctr1);

        unsigned int d2[] = {0, 1, 2};
        unsigned int d3[] = {0, 1, 1, 1};
        ctr.Set(d2, 3);
        ctr1.Set(d3, 4);
        ASSERT1(ctr1 > ctr);
        ASSERT1(!(ctr1 <= ctr));
        ASSERT1(!(ctr > ctr1));
        ASSERT1(ctr <= ctr1);

        unsigned int d4[] = {0, 1, 1, 0};
        ctr1.Set(d4, 4);
        ASSERT1(!(ctr1 > ctr));
        ASSERT1(ctr1 <= ctr);
        ASSERT1(ctr > ctr1);
        ASSERT1(!(ctr <= ctr1));
    });

    Add("MRInteger4", [&]() {
        unsigned int c[] = {1, 3, 3};
        MRInteger ctr(c, 3);

        unsigned int c1[] = {1, 3, 3, 2};
        MRInteger ctr1(c1, 4);

        ctr++;
        ASSERT1(!(ctr < ctr1));
        ASSERT1(ctr1 < ctr);
        ctr1++;
        ctr1++;
        ASSERT1(ctr < ctr1);
        ASSERT1(!(ctr >= ctr1));
        ASSERT1(!(ctr1 < ctr));
        ASSERT1(ctr1 >= ctr);

        unsigned int d[] = {0, 1, 1};
        unsigned int d1[] = {0, 1, 1, 1};
        ctr.Set(d, 3);
        ctr1.Set(d1, 4);
        ASSERT1(ctr < ctr1);
        ASSERT1(!(ctr >= ctr1));
        ASSERT1(!(ctr1 < ctr));
        ASSERT1(ctr1 >= ctr);

        unsigned int d2[] = {0, 1, 2};
        unsigned int d3[] = {0, 1, 1, 1};
        ctr.Set(d2, 3);
        ctr1.Set(d3, 4);
        ASSERT1(ctr < ctr1);
        ASSERT1(!(ctr >= ctr1));
        ASSERT1(!(ctr1 < ctr));
        ASSERT1(ctr1 >= ctr);

        unsigned int d4[] = {0, 1, 1, 0};
        ctr1.Set(d4, 4);
        ASSERT1(!(ctr < ctr1));
        ASSERT1(ctr >= ctr1);
        ASSERT1(ctr1 < ctr);
        ASSERT1(!(ctr1 >= ctr));
    });

    Add("MRIntegerRandom", [&]() {
        unsigned int b[] = {1, 2, 4, 8, 16, 32};
        MRInteger mri(b, 6);
        std::vector<MRInteger> numbers;
        for (int i = 0; i < 30000; i++)
        {
            mri.Random();
            numbers.push_back(MRInteger(mri));
        }

        sort(numbers.begin(), numbers.end());

        ASSERT1(std::is_sorted(numbers.begin(), numbers.end(), [&](const MRInteger &second, const MRInteger &first) {
            if (second < first)
            {
                for (int j = first.Length() - 1; j >= 0; j--)
                {
                    Logger().WriteInformation("\t%d", first[j]);
                }

                Logger().WriteInformation("\n");

                for (int j = second.Length() - 1; j >= 0; j--)
                {
                    Logger().WriteInformation("\t%d", second[j]);
                }

                Logger().WriteInformation("\n");
                return true;
            }
            else
            {
                return false;
            }
        }));
    });

    Add("Queue", [&]() {
        {
            Queue<int> q1;
            queue<int> q2;

            ASSERT1(q1.Empty() == true);
            ASSERT1(q2.empty() == true);
            ASSERT1(q1.Size() == q2.size());

            for (int i = 0; i < 100; i++)
            {
                q1.Push(i);
                q2.push(i);
                ASSERT1(q1.Empty() == false);
                ASSERT1(q2.empty() == false);
                ASSERT1(q1.Size() == q2.size());
            }

            int t1, t2;
            for (int i = 0; i < 99; i++)
            {
                t1 = q1.Front();
                q1.Pop();
                t2 = q2.front();
                q2.pop();
                ASSERT1(t1 == t2);
                ASSERT1(q1.Empty() == false);
                ASSERT1(q2.empty() == false);
                ASSERT1(q1.Size() == q2.size());
            }

            t1 = q1.Front();
            q1.Pop();
            t2 = q2.front();
            q2.pop();
            ASSERT1(t1 == t2);
            ASSERT1(q1.Empty() == true);
            ASSERT1(q2.empty() == true);
            ASSERT1(q1.Size() == q2.size());
        }
        {
            Queue<int> q1;
            queue<int> q2;

            ASSERTERROR(q1.Front(), runtime_error);
            ASSERT1(q1.Size() == q2.size());

            int v1, v2;
            for (int i = 0; i < 100; i++)
            {
                q1.Push(i);
                q2.push(i);
                v1 = q1.Front();
                v2 = q2.front();
                ASSERT1(v1 == 0);
                ASSERT1(v2 == 0);
                ASSERT1(q1.Size() == q2.size());
            }

            for (int i = 0; i < 99; i++)
            {
                q1.Pop();
                q2.pop();
                v1 = q1.Front();
                v2 = q2.front();
                ASSERT1(v1 == i + 1);
                ASSERT1(v2 == i + 1);
                ASSERT1(q1.Size() == q2.size());
            }

            v1 = q1.Front();
            v2 = q2.front();
            ASSERT1(v1 == 99);
            ASSERT1(v2 == 99);
            ASSERT1(q1.Size() == q2.size());

            q1.Pop();
            q2.pop();

            ASSERTERROR(q1.Front(), runtime_error);
            ASSERT1(q1.Empty() == true);
            ASSERT1(q2.empty() == true);
            ASSERT1(q1.Size() == q2.size());
        }
        {
            Queue<int> q1;
            queue<int> q2;

            ASSERTERROR(q1.Back(), runtime_error);
            ASSERT1(q1.Size() == q2.size());

            int v1, v2;
            for (int i = 0; i < 100; i++)
            {
                q1.Push(i);
                q2.push(i);
                v1 = q1.Back();
                v2 = q2.back();
                ASSERT1(v1 == i);
                ASSERT1(v2 == i);
                ASSERT1(q1.Size() == q2.size());
            }

            for (int i = 0; i < 99; i++)
            {
                q1.Pop();
                q2.pop();
                v1 = q1.Back();
                v2 = q2.back();
                ASSERT1(v1 == 99);
                ASSERT1(v2 == 99);
                ASSERT1(q1.Size() == q2.size());
            }

            q1.Pop();
            q2.pop();

            ASSERTERROR(q1.Back(), runtime_error);
            ASSERT1(q1.Empty() == true);
            ASSERT1(q2.empty() == true);
            ASSERT1(q1.Size() == q2.size());
        }
    });

    Add("Stack", [&]() {
        {
            Stack<int> s1;
            stack<int> s2;

            ASSERTERROR(s1.Top(), runtime_error);
            ASSERTERROR(s1.Pop(), runtime_error);
            ASSERT1(s1.Empty() == true);
            ASSERT1(s2.empty() == true);
            ASSERT1(s1.Size() == s2.size());

            for (int i = 0; i < 100; i++)
            {
                s1.Push(i);
                s2.push(i);
                ASSERT1(s1.Top() == i);
                ASSERT1(s2.top() == i);
                ASSERT1(s1.Empty() == false);
                ASSERT1(s2.empty() == false);
                ASSERT1(s1.Size() == s2.size());
            }

            int v1, v2;
            for (int i = 0; i < 99; i++)
            {
                v1 = s1.Top();
                s1.Pop();
                v2 = s2.top();
                s2.pop();
                ASSERT1(v1 == 99 - i);
                ASSERT1(v2 == 99 - i);
                ASSERT1(s1.Top() == 99 - i - 1);
                ASSERT1(s2.top() == 99 - i - 1);
                ASSERT1(s1.Empty() == false);
                ASSERT1(s2.empty() == false);
                ASSERT1(s1.Size() == s2.size());
            }

            v1 = s1.Top();
            s1.Pop();
            v2 = s2.top();
            s2.pop();
            ASSERT1(v1 == 0);
            ASSERT1(v2 == 0);
            ASSERTERROR(s1.Top(), runtime_error);
            ASSERTERROR(s1.Pop(), runtime_error);
            ASSERT1(s1.Empty() == true);
            ASSERT1(s2.empty() == true);
            ASSERT1(s1.Size() == s2.size());
        }
    });
}

#endif
