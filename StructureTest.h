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

    Add("Heap", [&]() {
        {
            Heap<int> heap;

            ASSERT1(heap.IsHeap());

            heap.Push(0);
            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == 0);

            heap.Push(1);
            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == 1);

            heap.Push(2);
            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == 2);

            heap.Push(-1);
            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == 2);

            for (int i = 3; i < 10; i++)
            {
                heap.Push(i);
                ASSERT1(heap.Top() == i);
            }

            ASSERT1(heap.IsHeap());
        }
        {
            Heap<int> heap;

            for (int i = 0; i < 10; i++)
            {
                heap.Push(i);
                ASSERT1(heap.Top() == i);
            }

            ASSERT1(heap.IsHeap());

            for (int i = 0; i < 10; i++)
            {
                int v = heap.Pop();
                ASSERT1(heap.IsHeap());
                ASSERT1(v == (9 - i));
            }
        }
        {
            vector<int> input;

            for (int i = 0; i < 10; i++)
            {
                input.push_back(i);
            }

            Heap<int> heap(input);
            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == 9);
        }
        {
            Heap<int> heap(1);

            ASSERT1(heap.IsHeap());

            heap.Push(0);
            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == 0);

            heap.Push(1);
            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == 0);

            heap.Push(2);
            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == 0);

            heap.Push(-1);
            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == -1);

            for (int i = 3; i < 10; i++)
            {
                heap.Push(i);
                ASSERT1(heap.Top() == -1);
            }

            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == -1);
        }
        {
            // This example shows the heap keeps the smallest two numbers from the input

            Heap<int> heap(2);

            ASSERT1(heap.IsHeap());

            heap.Push(0);
            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == 0);

            heap.Push(1);
            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == 1);

            heap.Push(2);
            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == 1);

            heap.Push(-1);
            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == 0);

            for (int i = 3; i < 10; i++)
            {
                heap.Push(i);
                ASSERT1(heap.Top() == 0);
            }

            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == 0);
        }
        {
            Heap<int, greater<int>> heap;

            ASSERT1(heap.IsHeap());

            heap.Push(0);
            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == 0);

            heap.Push(1);
            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == 0);

            heap.Push(2);
            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == 0);

            heap.Push(-1);
            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == -1);

            for (int i = 3; i < 10; i++)
            {
                heap.Push(i);
                ASSERT1(heap.Top() == -1);
            }

            ASSERT1(heap.IsHeap());
        }
        {
            Heap<int, greater<int>> heap;

            for (int i = 0; i < 10; i++)
            {
                heap.Push(i);
                ASSERT1(heap.Top() == 0);
            }

            ASSERT1(heap.IsHeap());

            for (int i = 0; i < 10; i++)
            {
                int v = heap.Pop();
                ASSERT1(heap.IsHeap());
                ASSERT1(v == i);
            }
        }
        {
            vector<int> input;

            for (int i = 0; i < 10; i++)
            {
                input.push_back(i);
            }

            Heap<int, greater<int>> heap(input);
            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == 0);
        }
        {
            Heap<int, greater<int>> heap(1);

            ASSERT1(heap.IsHeap());

            heap.Push(0);
            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == 0);

            heap.Push(1);
            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == 1);

            heap.Push(2);
            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == 2);

            heap.Push(-1);
            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == 2);

            for (int i = 3; i < 10; i++)
            {
                heap.Push(i);
                ASSERT1(heap.Top() == i);
            }

            ASSERT1(heap.IsHeap());
        }
        {
            // This example shows the heap keeps the greatest two numbers from the input

            Heap<int, greater<int>> heap(2);

            ASSERT1(heap.IsHeap());

            heap.Push(0);
            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == 0);

            heap.Push(1);
            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == 0);

            heap.Push(2);
            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == 1);

            heap.Push(-1);
            ASSERT1(heap.IsHeap());
            ASSERT1(heap.Top() == 1);

            for (int i = 3; i < 10; i++)
            {
                heap.Push(i);
                ASSERT1(heap.Top() == (i - 1));
            }

            ASSERT1(heap.IsHeap());
        }
        {
            less<int> lt;
            for (int i = 0; i < 100; i++)
            {
                int count = 1 + rand() % 1000;
                Logger().WriteInformation("Run %d: %d elements\n", i, count);
                Heap<int, less<int>> heap;
                vector<int> vheap;
                for (int j = 0; j < count; j++)
                {
                    int v = rand() % 1000;
                    heap.Push(v);
                    vheap.push_back(v);
                    push_heap(vheap.begin(), vheap.end(), lt);
                    ASSERT1(heap.Top() == vheap.front());
                }
                for (int j = 0; j < count; j++)
                {
                    int h = heap.Pop();
                    pop_heap(vheap.begin(), vheap.end(), lt);
                    int vh = vheap.back();
                    vheap.pop_back();
                    ASSERT1(h == vh);
                    if (j < count - 1)
                        ASSERT1(heap.Top() == vheap.front());
                }
            }
        }
        {
            greater<int> gt;
            for (int i = 0; i < 100; i++)
            {
                int count = 1 + rand() % 1000;
                Logger().WriteInformation("Run %d: %d elements\n", i, count);
                Heap<int, greater<int>> heap;
                vector<int> vheap;
                for (int j = 0; j < count; j++)
                {
                    int v = rand() % 1000;
                    heap.Push(v);
                    vheap.push_back(v);
                    push_heap(vheap.begin(), vheap.end(), gt);
                    ASSERT1(heap.Top() == vheap.front());
                }
                for (int j = 0; j < count; j++)
                {
                    int h = heap.Pop();
                    pop_heap(vheap.begin(), vheap.end(), gt);
                    int vh = vheap.back();
                    vheap.pop_back();
                    ASSERT1(h == vh);
                    if (j < count - 1)
                        ASSERT1(heap.Top() == vheap.front());
                }
            }
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

    Add("Array1D", [&]() {
        Array1D<int> A(4);
        A.Print();
        A.SetValue(1, 101);
        A.Print();
        int v = A.GetValue(1);
        ASSERT2(101 == v, String::Format("v = %d", v));
        A[3] = 303;
        A.Print();
        v = A[3];
        ASSERT2(303 == v, String::Format("v = %d", v));
        v = A.Length();
        ASSERT2(4 == v, String::Format("v = %d", v));
    });

    Add("Array2D", [&]() {
        Array2D<int> A(3, 4);
        A.Print();
        A.SetValue(1, 2, 101);
        A.Print();
        int v = A.GetValue(1, 2);
        ASSERT2(101 == v, String::Format("v = %d", v));
        A.Element(2, 3) = 202;
        A.Print();
        v = A.Element(2, 3);
        ASSERT2(202 == v, String::Format("v = %d", v));
        v = A.CountRows();
        ASSERT2(3 == v, String::Format("v = %d", v));
        v = A.CountCols();
        ASSERT2(4 == v, String::Format("v = %d", v));
    });

    Add("Array1DInvalidIndex", [&]() {
        Array1D<int> A(4);
        ASSERTERROR(A.GetValue(-1), std::invalid_argument);
    });

    Add("Array2DInvalidIndices", [&]() {
        Array2D<int> A(3, 4);
        ASSERTERROR(A.GetValue(-1, -1), std::invalid_argument);
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

    Add("SingleLinkListDelete", [&]() {
        Test::SingleLinkList<int> list;
        (Logger() << list).WriteInformation("\n");
        for (int i = 0; i < 10; i++)
        {
            list.Insert(i);
        }

        (Logger() << list).WriteInformation("\n");

        ASSERT1(list.Contain(0));
        list.Delete(0);
        (Logger() << list).WriteInformation("\n");
        ASSERT1(!list.Contain(0));

        ASSERT1(list.Contain(9));
        list.Delete(9);
        (Logger() << list).WriteInformation("\n");
        ASSERT1(!list.Contain(9));

        ASSERT1(list.Contain(5));
        list.Delete(5);
        (Logger() << list).WriteInformation("\n");
        ASSERT1(!list.Contain(5));

        for (int i = 0; i < 10; i++)
        {
            list.Delete(i);
            (Logger() << list).WriteInformation("\n");
            ASSERT1(!list.Contain(i));
        }
    });

    Add("SingleLinkListInsert", [&]() {
        SingleLinkList<int> list;
        list.Print();
        for (int i = 0; i < 10; i++)
        {
            list.Insert(i);
            list.Print();
        }
        for (int i = 0; i < 10; i++)
        {
            int v = list[i];
            cout << i << "\t" << v << endl;
            ASSERT2(v == i, String::Format("list[%d] = %d", i, v));
        }

        ASSERTERROR(list[10], std::invalid_argument);
    });

    Add("SingleLinkListReverse", [&]() {
        SingleLinkList<int> list;
        list.Print();
        list.Reverse();
        list.Print();
        for (int i = 0; i < 10; i++)
        {
            list.Insert(i);
            list.Print();
            list.Reverse();
            list.Print();
            for (int j = 0; j <= i; j++)
            {
                int v = list[j];
                ASSERT2(v == (i - j), String::Format("list[%d] = %d", i, v));
            }
            list.Reverse();
        }

        ASSERTERROR(list[10], std::invalid_argument);
    });

    Add("SingleLinkListMiddle", [&]() {
        SingleLinkList<int> list;
        list.Print();
        ASSERTERROR(list.Middle(), std::invalid_argument);

        for (int i = 0; i < 10; i++)
        {
            list.Insert(i);
            list.Print();
            int v = list.Middle();
            cout << "Middle = " << v << endl;
            ASSERT2(v == (i >> 1), String::Format("list[%d] = %d", i, v));
        }

        ASSERTERROR(list[10], std::invalid_argument);
    });

    Add("SingleLinkListIterator", [&]() {
        SingleLinkList<int> list;
        list.Print();
        for (int i = 0; i < 10; i++)
        {
            list.Insert(i);
            list.Print();
        }

        cout << "++ it, it->" << endl;
        for (SingleLinkList<int>::iterator it = list.begin(); it != list.end(); ++it)
        {
            unsigned int i = it.index();
            int v = it->data;
            cout << i << "\t" << v << endl;
            ASSERT2(v == i, String::Format("list[%d] = %d", i, v));
        }

        cout << "it ++, it.current()" << endl;
        for (SingleLinkList<int>::iterator it = list.begin(); it != list.end(); it++)
        {
            unsigned int i = it.index();
            int v = it.current();
            cout << i << "\t" << v << endl;
            ASSERT2(v == i, String::Format("list[%d] = %d", i, v));
        }

        cout << "++ it, *it" << endl;
        for (SingleLinkList<int>::iterator it = list.begin(); it != list.end(); ++it)
        {
            unsigned int i = it.index();
            int v = *it;
            cout << i << "\t" << v << endl;
            ASSERT2(v == i, String::Format("list[%d] = %d", i, v));
        }

        cout << "bool(it) == true" << endl;
        SingleLinkList<int>::iterator it = list.begin();
        ASSERT1(it);

        cout << "bool(it) == false" << endl;
        it = list.end();
        ASSERTERROR(it, std::invalid_argument);
    });

    Add("SortedSingleLinkListDelete", [&]() {
        Test::SortedSingleLinkList<int> list;
        (Logger() << list).WriteInformation("\n");
        for (int i = 0; i < 10; i++)
        {
            list.Insert(i);
        }

        (Logger() << list).WriteInformation("\n");

        ASSERT1(list.Contain(0));
        list.Delete(0);
        (Logger() << list).WriteInformation("\n");
        ASSERT1(!list.Contain(0));

        ASSERT1(list.Contain(9));
        list.Delete(9);
        (Logger() << list).WriteInformation("\n");
        ASSERT1(!list.Contain(9));

        ASSERT1(list.Contain(5));
        list.Delete(5);
        (Logger() << list).WriteInformation("\n");
        ASSERT1(!list.Contain(5));

        for (int i = 0; i < 10; i++)
        {
            list.Delete(i);
            (Logger() << list).WriteInformation("\n");
            ASSERT1(!list.Contain(i));
        }
    });

    Add("SortedSingleLinkListInsert", [&]() {
        Test::SortedSingleLinkList<int> list1;
        Test::SortedSingleLinkList<int> list2;
        (Logger() << list1).WriteInformation("\n");
        (Logger() << list2).WriteInformation("\n");
        for (int i = 0; i < 10; i++)
        {
            list1.Insert(i);
            list2.Insert(9 - i);
            (Logger() << list1).WriteInformation("\n");
            (Logger() << list2).WriteInformation("\n");
        }

        for (int i = 0; i < 10; i++)
        {
            int v = list1[i];
            ASSERT2(v == i, Test::String::Format("list1[%d] = %d", i, v));
            ASSERT2(v == list2[i], Test::String::Format("list2[%d] = %d", i, v));
        }
    });

    Add("SortedSingleLinkListMiddle", [&]() {
        Test::SortedSingleLinkList<int> list;
        (Logger() << list).WriteInformation("\n");
        ASSERTERROR(list.Middle(), std::invalid_argument);

        for (int i = 0; i < 10; i++)
        {
            list.Insert(i);
            (Logger() << list).WriteInformation("\n");
            int v = list.Middle();
            Logger().WriteInformation("Middle = %d\n", v);
            ASSERT2(v == (i >> 1), Test::String::Format("list[%d] = %d", i, v));
        }

        ASSERTERROR(list[10], std::invalid_argument);
    });

    Add("SortedSingleLinkListReverse", [&]() {
        Test::SortedSingleLinkList<int> list;
        (Logger() << list).WriteInformation("\n");
        list.Reverse();
        (Logger() << list).WriteInformation("\n");
        for (int i = 0; i < 10; i++)
        {
            list.Insert(i);
            (Logger() << list).WriteInformation("\n");
            list.Reverse();
            (Logger() << list).WriteInformation("\n");
            for (int j = 0; j <= i; j++)
            {
                int v = list[j];
                ASSERT2(v == i - j, Test::String::Format("list[%d] = %d", j, v));
            }

            list.Reverse();
        }

        ASSERTERROR(list[10], std::invalid_argument);
    });

    Add("SortedSingleLinkListIterator", [&]() {
        Test::SortedSingleLinkList<int> list;
        (Logger() << list).WriteInformation("\n");
        for (int i = 0; i < 10; i++)
        {
            list.Insert(i);
            (Logger() << list).WriteInformation("\n");
        }

        Logger().WriteInformation("++ it, it->\n");
        for (Test::SortedSingleLinkList<int>::iterator it = list.begin(); it != list.end(); ++it)
        {
            unsigned int i = it.Index();
            int v = it->data;
            Logger().WriteInformation("%d\t%d\n", i, v);
            ASSERT2(v == i, Test::String::Format("list[%d] = %d", i, v));
        }

        Logger().WriteInformation("it ++, it.current()\n");
        for (Test::SortedSingleLinkList<int>::iterator it = list.begin(); it != list.end(); it++)
        {
            unsigned int i = it.Index();
            int v = it.current();
            Logger().WriteInformation("%d\t%d\n", i, v);
            ASSERT2(v == i, Test::String::Format("list[%d] = %d", i, v));
        }

        Logger().WriteInformation("++ it, *it\n");
        for (Test::SortedSingleLinkList<int>::iterator it = list.begin(); it != list.end(); ++it)
        {
            unsigned int i = it.Index();
            int v = *it;
            Logger().WriteInformation("%d\t%d\n", i, v);
            ASSERT2(v == i, Test::String::Format("list[%d] = %d", i, v));
        }

        Logger().WriteInformation("bool(it) == true\n");
        Test::SortedSingleLinkList<int>::iterator it = list.begin();
        ASSERT1(it);

        Logger().WriteInformation("bool(it) == false\n");
        it = list.end();
        ASSERTERROR(it, std::invalid_argument);
    });

    Add("SortedSingleLinkListOverride", [&]() {
        Test::SingleLinkList<int> *list1 = new Test::SingleLinkList<int>();
        Test::SingleLinkList<int> *list2 = new Test::SortedSingleLinkList<int>();
        (Logger() << *list1).WriteInformation("\n");
        (Logger() << *list2).WriteInformation("\n");
        for (int i = 0; i < 10; i++)
        {
            list1->Insert(9 - i);
            list2->Insert(i);
            (Logger() << *list1).WriteInformation("\n");
            (Logger() << *list2).WriteInformation("\n");
        }

        for (int i = 0; i < 10; i++)
        {
            int v = (*list1)[i];
            ASSERT2(v == i, Test::String::Format("list1[%d] = %d", i, v));
            ASSERT2(v == (*list2)[i], Test::String::Format("list2[%d] = %d", i, v));
        }
    });

    Add("CircularSingleLinkListDelete", [&]() {
        Test::CircularSingleLinkList<int> list;
        (Logger() << list).WriteInformation("\n");
        for (int i = 0; i < 10; i++)
        {
            list.Insert(i);
        }

        (Logger() << list).WriteInformation("\n");

        ASSERT1(list.Contain(0));
        list.Delete(0);
        (Logger() << list).WriteInformation("\n");
        ASSERT1(!list.Contain(0));

        ASSERT1(list.Contain(9));
        list.Delete(9);
        (Logger() << list).WriteInformation("\n");
        ASSERT1(!list.Contain(9));

        ASSERT1(list.Contain(5));
        list.Delete(5);
        (Logger() << list).WriteInformation("\n");
        ASSERT1(!list.Contain(5));

        for (int i = 0; i < 10; i++)
        {
            list.Delete(i);
            (Logger() << list).WriteInformation("\n");
            ASSERT1(!list.Contain(i));
        }
    });

    Add("CircularSingleLinkListInsert", [&]() {
        Test::CircularSingleLinkList<int> list;
        (Logger() << list).WriteInformation("\n");
        for (int i = 0; i < 10; i++)
        {
            list.Insert(i);
            (Logger() << list).WriteInformation("\n");
        }

        for (int i = 0; i < 10; i++)
        {
            int v = list[i + 1];
            ASSERT2(v == i, Test::String::Format("list[%d] = %d", i, v));
        }

        ASSERT2(list[10] == list[0], Test::String::Format("list[10] = %d", list[10]));
    });

    Add("SortedCircularSingleLinkListInsert 1", [&]() {
        Test::SortedCircularSingleLinkList<int> list;
        (Logger() << list).WriteInformation("\n");

        list.Insert(0);
        (Logger() << list).WriteInformation("\n");
        ASSERT1(list[0] == 0);

        list.Insert(0);
        (Logger() << list).WriteInformation("\n");
        ASSERT1(list[0] == 0);
        ASSERT1(list[1] == 0);

        list.Insert(2);
        (Logger() << list).WriteInformation("\n");
        ASSERT1(list[0] == 0);
        ASSERT1(list[1] == 0);
        ASSERT1(list[2] == 2);

        list.Insert(2);
        (Logger() << list).WriteInformation("\n");
        ASSERT1(list[0] == 0);
        ASSERT1(list[1] == 0);
        ASSERT1(list[2] == 2);
        ASSERT1(list[3] == 2);

        list.Insert(-1);
        (Logger() << list).WriteInformation("\n");
        ASSERT1(list[0] == -1);
        ASSERT1(list[1] == 0);
        ASSERT1(list[2] == 0);
        ASSERT1(list[3] == 2);
        ASSERT1(list[4] == 2);

        list.Insert(-1);
        (Logger() << list).WriteInformation("\n");
        ASSERT1(list[0] == -1);
        ASSERT1(list[1] == -1);
        ASSERT1(list[2] == 0);
        ASSERT1(list[3] == 0);
        ASSERT1(list[4] == 2);
        ASSERT1(list[5] == 2);

        list.Insert(1);
        (Logger() << list).WriteInformation("\n");
        ASSERT1(list[0] == -1);
        ASSERT1(list[1] == -1);
        ASSERT1(list[2] == 0);
        ASSERT1(list[3] == 0);
        ASSERT1(list[4] == 1);
        ASSERT1(list[5] == 2);
        ASSERT1(list[6] == 2);

        list.Insert(1);
        (Logger() << list).WriteInformation("\n");
        ASSERT1(list[0] == -1);
        ASSERT1(list[1] == -1);
        ASSERT1(list[2] == 0);
        ASSERT1(list[3] == 0);
        ASSERT1(list[4] == 1);
        ASSERT1(list[5] == 1);
        ASSERT1(list[6] == 2);
        ASSERT1(list[7] == 2);
    });

    Add("SortedCircularSingleLinkListInsert 2", [&]() {
        Test::SortedCircularSingleLinkList<int> list;
        (Logger() << list).WriteInformation("\n");

        for (int i = 0; i < 100; i++)
        {
            list.Insert(i);
        }

        (Logger() << list).WriteInformation("\n");

        for (int i = 0; i < 100; i++)
        {
            ASSERT2(list[i] == i, Test::String::Format("list[%d] = %d", i, list[i]));
        }
    });

    Add("SortedCircularSingleLinkListInsert 3", [&]() {
        Test::SortedCircularSingleLinkList<int> list;
        (Logger() << list).WriteInformation("\n");

        for (int i = 0; i < 100; i++)
        {
            list.Insert(99 - i);
        }

        (Logger() << list).WriteInformation("\n");

        for (int i = 0; i < 100; i++)
        {
            ASSERT2(list[i] == i, Test::String::Format("list[%d] = %d", i, list[i]));
        }
    });

    Add("SortedCircularSingleLinkListInsert 4", [&]() {
        Test::SortedCircularSingleLinkList<int> list;
        (Logger() << list).WriteInformation("\n");

        for (int i = 0; i < 100; i++)
        {
            list.Insert(9);
        }

        (Logger() << list).WriteInformation("\n");

        list.Insert(9);
        (Logger() << list).WriteInformation("\n");
        for (int i = 0; i < 101; i++)
        {
            ASSERT2(list[i] == 9, Test::String::Format("list[%d] = %d", i, list[i]));
        }

        list.Insert(5);
        (Logger() << list).WriteInformation("\n");
        ASSERT2(list[0] == 5, Test::String::Format("list[0] = %d", list[0]));

        for (int i = 1; i < 102; i++)
        {
            ASSERT2(list[i] == 9, Test::String::Format("list[%d] = %d", i, list[i]));
        }
    });

    Add("SortedCircularSingleLinkListInsert 5", [&]() {
        Test::SortedCircularSingleLinkList<int> list;
        (Logger() << list).WriteInformation("\n");

        for (int i = 0; i < 100; i++)
        {
            list.Insert(9);
        }

        (Logger() << list).WriteInformation("\n");

        list.Insert(15);
        (Logger() << list).WriteInformation("\n");
        for (int i = 0; i < 100; i++)
        {
            ASSERT2(list[i] == 9, Test::String::Format("list[%d] = %d", i, list[i]));
        }

        ASSERT2(list[100] == 15, Test::String::Format("list[100] = %d", list[100]));
    });

    Add("SortedCircularSingleLinkListInsert 6", [&]() {
        Test::SortedCircularSingleLinkList<int> list;
        (Logger() << list).WriteInformation("\n");

        int count = 1 + rand();
        for (int i = 0; i < count; i++)
        {
            list.Insert(rand());
        }

        (Logger() << list).WriteInformation("\n");

        int t = list[0];
        for (int i = 1; i < count; i++)
        {
            int v = list[i];
            ASSERT2(v >= t, Test::String::Format("list[%d] = %d > list[%d] = %d", i - 1, t, i, v));
            t = v;
        }
    });

    Add("AVLTreeInsert1", [&]() {
        Test::AVLTree<int> tree;
        bool valid;
        for (int i = 0; i < 20; i++)
        {
            tree.Insert(i);
            valid = tree.Verify();
            if (!valid)
                tree.Print();
            ASSERT1(valid == true);
        }
    });

    Add("AVLTreeInsert2", [&]() {
        for (int i = 0; i < 100; i++)
        {
            int count = 1 + Test::Random::Next(1000);
            cout << "Run " << i << ", " << count << " elements" << endl;
            Test::AVLTree<int> tree;
            bool valid;
            int v;
            for (int j = 0; j < count; j++)
            {
                v = Test::Random::Next();
                tree.Insert(v);
                valid = tree.Verify();
                if (!valid)
                {
                    cout << "Insert " << v << endl;
                    tree.Print();
                }
                ASSERT1(valid == true);
            }
        }
    });

    Add("AVLTreeDelete1", [&]() {
        Test::AVLTree<int> tree;
        int count = 10;
        for (int i = 0; i < count; i++)
        {
            tree.Insert(i);
        }

        tree.Print();
        bool valid = tree.Verify();
        ASSERT1(valid == true);

        for (int i = 0; i < count; i++)
        {
            cout << "Deleting " << i << endl;
            tree.Delete(i);
            tree.Print();
            valid = tree.Verify();
            ASSERT1(valid == true);
        }
    });

    Add("AVLTreeDelete2", [&]() {
        for (int j = 0; j < 1000; j++)
        {
            Test::AVLTree<int> tree;
            int count = Test::Random::Next(1000);
            cout << "Run " << j << ", " << count << " elements" << endl;

            int v;
            vector<int> vals;
            for (int i = 0; i < count; i++)
            {
                v = Test::Random::Next();
                vals.push_back(v);
                tree.Insert(v);
            }

            bool valid = tree.Verify();
            ASSERT1(valid == true);

            for (int i = 0; i < count; i++)
            {
                v = vals[i];
                tree.Delete(v);
                valid = tree.Verify();
                if (!valid)
                {
                    cout << "Delete " << v << endl;
                    tree.Print();
                }

                ASSERT1(valid == true);
            }
        }
    });

    Add("AVLTreeUpdate", [&]() {
        for (int j = 0; j < 100; j++)
        {
            unsigned int count = 1 + Test::Random::Next(1000);
            cout << "Run " << j << ", " << count << " elements" << endl;

            Test::AVLTree<int> tree;
            vector<int> values;
            int v;
            bool valid;
            string action;
            while (values.size() < count)
            {
                if (Test::Random::Next(100) < 70)
                {
                    v = Test::Random::Next();
                    action = Test::String::Format("Insert %d", v);
                    tree.Insert(v);
                    values.push_back(v);
                }
                else if (values.size() > 0)
                {
                    int i = Test::Random::Next(values.size() - 1);
                    v = values[i];
                    action = Test::String::Format("Delete %d", v);
                    tree.Delete(v);
                    values.erase(values.begin() + i);
                }

                valid = tree.Verify();
                if (!valid)
                {
                    cout << action << endl;
                    tree.Print();
                }

                ASSERT1(valid == true);
            }
        }
    });

    Add("Node", [&]() {
        {
            Node<int> node(1);
            ASSERT1(0 == node.CountNeighbors());
            ASSERT1(nullptr == node.Neighbor(0));
            ASSERT1(1 == node.CountNeighbors());
            ASSERT1(nullptr == node.Neighbor(0));
            ASSERT1(1 == node.CountNeighbors());
        }
        {
            Node<int> *p = new Node<int>(2);
            ASSERT1(0 == p->CountNeighbors());
            ASSERT1(nullptr == p->Neighbor(0));
            ASSERT1(1 == p->CountNeighbors());
            ASSERT1(nullptr == p->Neighbor(0));
            ASSERT1(1 == p->CountNeighbors());
            ASSERT1(nullptr == p->Neighbor(1));
            ASSERT1(2 == p->CountNeighbors());
            delete p;
        }
    });

    Add("SingleNode1", [&]() {
        {
            SingleNode<int> node(1);
            cout << &node;
            cout << "Count: " << node.CountNeighbors() << endl;
            ASSERT1(1 == node.CountNeighbors());
            cout << "Middle: " << node.Middle()->Value() << endl;
            ASSERT1(1 == node.Middle()->Value());
            SingleNode<int> *r = node.Reverse();
            cout << "Reverse:" << endl
                 << r;
            ASSERT1(1 == r->Value());
            r = nullptr;
            r = new SingleNode<int>(2);
            cout << r;
            delete r;
        }
        {
            SingleNode<int> node(1);
            node.Next() = &node;
            cout << &node;
            cout << "Count: " << node.CountNeighbors() << endl;
            ASSERT1(1 == node.CountNeighbors());
            cout << "Middle: " << node.Middle()->Value() << endl;
            ASSERT1(1 == node.Middle()->Value());
            SingleNode<int> *r = node.Reverse();
            cout << "Reverse:" << endl
                 << r;
            ASSERT1(1 == r->Value());
            r = nullptr;
            r = new SingleNode<int>(2);
            r->Next() = r;
            cout << r;
            delete r;
        }
    });

    Add("SingleNode2", [&]() {
        {
            SingleNode<int> *n1 = new SingleNode<int>(1);
            SingleNode<int> *n2 = new SingleNode<int>(2);
            SingleNode<int> *n3 = new SingleNode<int>(3);
            SingleNode<int> *n4 = new SingleNode<int>(4);
            n1->Next() = n2;
            n2->Next() = n3;
            n3->Next() = n4;

            cout << n1 << endl;

            cout << "Middle: " << n1->Middle()->Value() << endl;
            ASSERT1(2 == n1->Middle()->Value());

            SingleNode<int>::DeleteList(n1);
        }
        {
            SingleNode<int> *n1 = new SingleNode<int>(1);
            SingleNode<int> *n2 = new SingleNode<int>(2);
            SingleNode<int> *n3 = new SingleNode<int>(3);
            SingleNode<int> *n4 = new SingleNode<int>(4);
            n1->Next(n2);
            n2->Next(n3);
            n3->Next(n4);

            cout << n1;

            SingleNode<int> *n = SingleNode<int>::Reverse(n1);
            cout << "Reverse:" << endl;
            cout << n;

            SingleNode<int>::DeleteList(n);
        }
    });

    Add("SingleNode3", [&]() {
        {
            SingleNode<int> *n1 = new SingleNode<int>(1);
            SingleNode<int> *n2 = new SingleNode<int>(2);
            SingleNode<int> *n3 = new SingleNode<int>(3);
            SingleNode<int> *n4 = new SingleNode<int>(4);
            n1->Next() = n2;
            n2->Next() = n3;
            n3->Next() = n4;
            n4->Next() = n1;

            cout << n1 << endl;

            cout << "Middle: " << n1->Middle()->Value() << endl;

            SingleNode<int> *n = SingleNode<int>::Reverse(n1);
            cout << "Reverse:" << endl;
            cout << n;

            SingleNode<int>::DeleteList(n);
        }
    });

    Add("SingleNode4", [&]() {
        {
            SingleNode<int> n1(0);
            for (int i = 1; i < 10; i++)
            {
                n1.InsertAtEnd(new SingleNode<int>(i));
                cout << &n1;
                int m = n1.Middle()->Value();
                cout << "Middle: " << m << endl;
                ASSERT1(m == i >> 1);
            }
            n1.DeleteList();
        }
        {
            SingleNode<int> n1(0);
            for (int i = 9; i > 0; i--)
            {
                n1.InsertAfter(new SingleNode<int>(i));
                cout << &n1;
            }
            int m = n1.Middle()->Value();
            cout << "Middle: " << m << endl;
            ASSERT1(m == 4);
            n1.DeleteList();
        }
    });

    Add("SingleNode5", [&]() {
        {
            SingleNode<int> *n = new SingleNode<int>(0);
            for (int i = 1; i < 10; i++)
            {
                n->InsertAtEnd(new SingleNode<int>(i));
                cout << n;
                n = n->Reverse();
                cout << "Reverse: " << endl
                     << n;
            }
            SingleNode<int>::DeleteList(n);
        }
        {
            SingleNode<int> *n = new SingleNode<int>(0);
            n->Next() = n;
            for (int i = 1; i < 10; i++)
            {
                n->InsertAtEnd(new SingleNode<int>(i));
                cout << n;
                n = n->Reverse();
                cout << "Reverse: " << endl
                     << n;
            }
            SingleNode<int>::DeleteList(n);
        }
    });

    Add("SingleNode6", [&]() {
        {
            SingleNode<int> *n1 = new SingleNode<int>(1);
            SingleNode<int> *n2 = new SingleNode<int>(2);
            SingleNode<int> *n3 = new SingleNode<int>(3);
            SingleNode<int> *n4 = new SingleNode<int>(4);
            n1->Next() = n2;
            n2->Next() = n3;
            n3->Next() = n4;
            n4->Next() = n1;

            cout << n1;

            SingleNode<int> *p = SingleNode<int>::Tail(n1);
            cout << "Tail: " << p->Value() << endl;
            ASSERT1(4 == p->Value());

            n1 = SingleNode<int>::Reverse(n1);
            cout << n1;

            p = SingleNode<int>::Tail(n1);
            cout << "Tail: " << p->Value() << endl;
            ASSERT1(1 == p->Value());

            SingleNode<int>::DeleteList(n1);
        }
        {
            SingleNode<int> *n1 = new SingleNode<int>(1);
            SingleNode<int> *n2 = new SingleNode<int>(2);
            SingleNode<int> *n3 = new SingleNode<int>(3);
            SingleNode<int> *n4 = new SingleNode<int>(4);
            n1->Next() = n2;
            n2->Next() = n3;
            n3->Next() = n4;
            n4->Next() = n2;

            cout << n1;

            SingleNode<int> *p = SingleNode<int>::Tail(n1);
            cout << "Tail: " << p->Value() << endl;
            ASSERT1(4 == p->Value());

            n1 = SingleNode<int>::Reverse(n1);
            cout << n1;

            p = SingleNode<int>::Tail(n1);
            cout << "Tail: " << p->Value() << endl;
            ASSERT1(1 == p->Value());

            SingleNode<int>::DeleteList(n1);
        }
    });

    Add("SingleNode7", [&]() {
        {
            SingleNode<int> *n1 = new SingleNode<int>(1);
            cout << n1;
            cout << "Delete 0:" << endl;
            n1 = SingleNode<int>::Delete(n1, 0);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 1:" << endl;
            n1 = SingleNode<int>::Delete(n1, 1);
            cout << n1;
            ASSERT1(n1 == nullptr);
        }
        {
            SingleNode<int> *n1 = new SingleNode<int>(1);
            n1->Next() = n1;
            cout << n1;
            cout << "Delete 0:" << endl;
            n1 = SingleNode<int>::Delete(n1, 0);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 1:" << endl;
            n1 = SingleNode<int>::Delete(n1, 1);
            cout << n1;
            ASSERT1(n1 == nullptr);
        }
    });

    Add("SingleNode8", [&]() {
        {
            SingleNode<int> *n1 = new SingleNode<int>(1);
            SingleNode<int> *n2 = new SingleNode<int>(2);
            n1->Next() = n2;
            cout << n1;
            cout << "Delete 0:" << endl;
            n1 = SingleNode<int>::Delete(n1, 0);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 1:" << endl;
            n1 = SingleNode<int>::Delete(n1, 1);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 2:" << endl;
            n1 = SingleNode<int>::Delete(n1, 2);
            cout << n1;
            ASSERT1(n1 == nullptr);
        }
        {
            SingleNode<int> *n1 = new SingleNode<int>(1);
            SingleNode<int> *n2 = new SingleNode<int>(2);
            n1->Next() = n2;
            n2->Next() = n1;
            cout << n1;
            cout << "Delete 0:" << endl;
            n1 = SingleNode<int>::Delete(n1, 0);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 1:" << endl;
            n1 = SingleNode<int>::Delete(n1, 1);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 2:" << endl;
            n1 = SingleNode<int>::Delete(n1, 2);
            cout << n1;
            ASSERT1(n1 == nullptr);
        }
        {
            SingleNode<int> *n1 = new SingleNode<int>(1);
            SingleNode<int> *n2 = new SingleNode<int>(2);
            n1->Next() = n2;
            n2->Next() = n2;
            cout << n1;
            cout << "Delete 0:" << endl;
            n1 = SingleNode<int>::Delete(n1, 0);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 1:" << endl;
            n1 = SingleNode<int>::Delete(n1, 1);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 2:" << endl;
            n1 = SingleNode<int>::Delete(n1, 2);
            cout << n1;
            ASSERT1(n1 == nullptr);
        }
        {
            SingleNode<int> *n1 = new SingleNode<int>(1);
            SingleNode<int> *n2 = new SingleNode<int>(2);
            n1->Next() = n2;
            n2->Next() = n2;
            cout << n1;
            cout << "Delete 0:" << endl;
            n1 = SingleNode<int>::Delete(n1, 0);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 2:" << endl;
            n1 = SingleNode<int>::Delete(n1, 2);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 1:" << endl;
            n1 = SingleNode<int>::Delete(n1, 1);
            cout << n1;
            ASSERT1(n1 == nullptr);
        }
    });

    Add("SingleNode9", [&]() {
        {
            SingleNode<int> *n1 = new SingleNode<int>(1);
            SingleNode<int> *n2 = new SingleNode<int>(2);
            SingleNode<int> *n3 = new SingleNode<int>(3);
            n1->Next() = n2;
            n2->Next() = n3;
            cout << n1;
            cout << "Delete 0:" << endl;
            n1 = SingleNode<int>::Delete(n1, 0);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 1:" << endl;
            n1 = SingleNode<int>::Delete(n1, 1);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 2:" << endl;
            n1 = SingleNode<int>::Delete(n1, 2);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 3:" << endl;
            n1 = SingleNode<int>::Delete(n1, 3);
            cout << n1;
            ASSERT1(n1 == nullptr);
        }
        {
            SingleNode<int> *n1 = new SingleNode<int>(1);
            SingleNode<int> *n2 = new SingleNode<int>(2);
            SingleNode<int> *n3 = new SingleNode<int>(3);
            n1->Next() = n2;
            n2->Next() = n3;
            cout << n1;
            cout << "Delete 0:" << endl;
            n1 = SingleNode<int>::Delete(n1, 0);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 2:" << endl;
            n1 = SingleNode<int>::Delete(n1, 2);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 3:" << endl;
            n1 = SingleNode<int>::Delete(n1, 3);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 1:" << endl;
            n1 = SingleNode<int>::Delete(n1, 1);
            cout << n1;
            ASSERT1(n1 == nullptr);
        }
    });

    Add("SingleNode10", [&]() {
        {
            SingleNode<int> *n1 = new SingleNode<int>(1);
            SingleNode<int> *n2 = new SingleNode<int>(2);
            SingleNode<int> *n3 = new SingleNode<int>(3);
            n1->Next() = n2;
            n2->Next() = n3;
            n3->Next() = n1;
            cout << n1;
            cout << "Delete 0:" << endl;
            n1 = SingleNode<int>::Delete(n1, 0);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 1:" << endl;
            n1 = SingleNode<int>::Delete(n1, 1);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 2:" << endl;
            n1 = SingleNode<int>::Delete(n1, 2);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 3:" << endl;
            n1 = SingleNode<int>::Delete(n1, 3);
            cout << n1;
            ASSERT1(n1 == nullptr);
        }
        {
            SingleNode<int> *n1 = new SingleNode<int>(1);
            SingleNode<int> *n2 = new SingleNode<int>(2);
            SingleNode<int> *n3 = new SingleNode<int>(3);
            n1->Next() = n2;
            n2->Next() = n3;
            n3->Next() = n1;
            cout << n1;
            cout << "Delete 0:" << endl;
            n1 = SingleNode<int>::Delete(n1, 0);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 2:" << endl;
            n1 = SingleNode<int>::Delete(n1, 2);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 3:" << endl;
            n1 = SingleNode<int>::Delete(n1, 3);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 1:" << endl;
            n1 = SingleNode<int>::Delete(n1, 1);
            cout << n1;
            ASSERT1(n1 == nullptr);
        }
        {
            SingleNode<int> *n1 = new SingleNode<int>(1);
            SingleNode<int> *n2 = new SingleNode<int>(2);
            SingleNode<int> *n3 = new SingleNode<int>(3);
            n1->Next() = n2;
            n2->Next() = n3;
            n3->Next() = n1;
            cout << n1;
            cout << "Delete 0:" << endl;
            n1 = SingleNode<int>::Delete(n1, 0);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 3:" << endl;
            n1 = SingleNode<int>::Delete(n1, 3);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 2:" << endl;
            n1 = SingleNode<int>::Delete(n1, 2);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 1:" << endl;
            n1 = SingleNode<int>::Delete(n1, 1);
            cout << n1;
            ASSERT1(n1 == nullptr);
        }
        {
            SingleNode<int> *n1 = new SingleNode<int>(1);
            SingleNode<int> *n2 = new SingleNode<int>(2);
            SingleNode<int> *n3 = new SingleNode<int>(3);
            n1->Next() = n2;
            n2->Next() = n3;
            n3->Next() = n2;
            cout << n1;
            cout << "Delete 0:" << endl;
            n1 = SingleNode<int>::Delete(n1, 0);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 2:" << endl;
            n1 = SingleNode<int>::Delete(n1, 2);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 3:" << endl;
            n1 = SingleNode<int>::Delete(n1, 3);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 1:" << endl;
            n1 = SingleNode<int>::Delete(n1, 1);
            cout << n1;
            ASSERT1(n1 == nullptr);
        }
        {
            SingleNode<int> *n1 = new SingleNode<int>(1);
            SingleNode<int> *n2 = new SingleNode<int>(2);
            SingleNode<int> *n3 = new SingleNode<int>(3);
            n1->Next() = n2;
            n2->Next() = n3;
            n3->Next() = n2;
            cout << n1;
            cout << "Delete 0:" << endl;
            n1 = SingleNode<int>::Delete(n1, 0);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 3:" << endl;
            n1 = SingleNode<int>::Delete(n1, 3);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 2:" << endl;
            n1 = SingleNode<int>::Delete(n1, 2);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 1:" << endl;
            n1 = SingleNode<int>::Delete(n1, 1);
            cout << n1;
            ASSERT1(n1 == nullptr);
        }
        {
            SingleNode<int> *n1 = new SingleNode<int>(1);
            SingleNode<int> *n2 = new SingleNode<int>(2);
            SingleNode<int> *n3 = new SingleNode<int>(3);
            n1->Next() = n2;
            n2->Next() = n3;
            n3->Next() = n3;
            cout << n1;
            cout << "Delete 0:" << endl;
            n1 = SingleNode<int>::Delete(n1, 0);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 2:" << endl;
            n1 = SingleNode<int>::Delete(n1, 2);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 3:" << endl;
            n1 = SingleNode<int>::Delete(n1, 3);
            cout << n1;
            ASSERT1(n1 != nullptr);
            cout << "Delete 1:" << endl;
            n1 = SingleNode<int>::Delete(n1, 1);
            cout << n1;
            ASSERT1(n1 == nullptr);
        }
    });

    Add("SingleNodeReorder", [&]() {
        auto check = [&](SingleNode<int> *node) {
            size_t len = node->Length();
            cout << node << endl;
            SingleNode<int>::Reorder(node);
            size_t len2 = node->Length();
            cout << node << endl;
            ASSERT1(len == len2);
            size_t i = 0;
            SingleNode<int> *p = node;
            while (p != nullptr)
            {
                ASSERT1(p->Value() == i);
                p = p->Next();
                i++;
            }
            SingleNode<int>::DeleteList(node);
        };
        {
            SingleNode<int> *n = new SingleNode<int>(0);
            check(n);
        }
        {
            SingleNode<int> *n = new SingleNode<int>(0);
            n->InsertAtEnd(new SingleNode<int>(1));
            check(n);
        }
        {
            SingleNode<int> *n = new SingleNode<int>(0);
            n->InsertAtEnd(new SingleNode<int>(2));
            n->InsertAtEnd(new SingleNode<int>(1));
            check(n);
        }
        {
            SingleNode<int> *n = new SingleNode<int>(0);
            n->InsertAtEnd(new SingleNode<int>(2));
            n->InsertAtEnd(new SingleNode<int>(3));
            n->InsertAtEnd(new SingleNode<int>(1));
            check(n);
        }
        {
            for (int i = 5; i < 100; i++)
            {
                Logger().WriteInformation("Reorder a list of %d nodes\n", i);
                SingleNode<int> *n = new SingleNode<int>(0);
                int j = (i + 1) >> 1;
                for (int k = 1; k < j; k++)
                {
                    n->InsertAtEnd(new SingleNode<int>(2 * k));
                }
                j = i >> 1;
                for (int k = j; k > 0; k--)
                {
                    n->InsertAtEnd(new SingleNode<int>(2 * k - 1));
                }
                check(n);
            }
        }
    });

    Add("SingleNodeCycle", [&]() {
        auto check = [&](SingleNode<int> *node, int beginning) {
            cout << node;
            size_t l1 = node->Length();
            size_t l2 = SingleNode<int>::Length(node);
            bool hasCycle = SingleNode<int>::HasCycle(node);
            if (hasCycle)
            {
                SingleNode<int> *cycle = SingleNode<int>::FindCycle(node);
                Logger().WriteInformation("Has cycle at %d\n", cycle->Value());
                int v = cycle->Value();
                ASSERT1(beginning == v);
            }
            else
            {
                Logger().WriteInformation("No cycle\n");
                ASSERT1(beginning == -1);
            }
            node = SingleNode<int>::Reverse(node);
            Logger().WriteInformation("Reverse:\n");
            cout << node;
            hasCycle = SingleNode<int>::HasCycle(node);
            if (hasCycle)
            {
                SingleNode<int> *cycle = SingleNode<int>::FindCycle(node);
                Logger().WriteInformation("Has cycle at %d\n", cycle->Value());
            }
            else
            {
                Logger().WriteInformation("No cycle\n");
            }
            size_t l3 = SingleNode<int>::Length(node);
            SingleNode<int>::DeleteList(node);
            ASSERT1(l1 == l2);
            ASSERT1(l1 == l3);
        };
        {
            SingleNode<int> *n = new SingleNode<int>(0);
            check(n, -1);
        }
        {
            SingleNode<int> *n = new SingleNode<int>(0);
            n->Next() = n;
            check(n, 0);
        }
        {
            SingleNode<int> *n = new SingleNode<int>(0);
            n->InsertAtEnd(new SingleNode<int>(1));
            check(n, -1);
        }
        {
            SingleNode<int> *n = new SingleNode<int>(0);
            n->Next() = n;
            n->InsertAtEnd(new SingleNode<int>(1));
            check(n, 0);
        }
        {
            SingleNode<int> *n = new SingleNode<int>(0);
            SingleNode<int> *c = new SingleNode<int>(1);
            c->Next() = c;
            n->Next() = c;
            check(n, 1);
        }
        {
            SingleNode<int> *n = new SingleNode<int>(0);
            n->InsertAtEnd(new SingleNode<int>(1));
            n->InsertAtEnd(new SingleNode<int>(2));
            check(n, -1);
        }
        {
            SingleNode<int> *n = new SingleNode<int>(0);
            n->Next() = n;
            n->InsertAtEnd(new SingleNode<int>(1));
            n->InsertAtEnd(new SingleNode<int>(2));
            check(n, 0);
        }
        {
            SingleNode<int> *n = new SingleNode<int>(0);
            SingleNode<int> *c = new SingleNode<int>(1);
            c->Next() = c;
            c->InsertAtEnd(new SingleNode<int>(2));
            n->Next() = c;
            check(n, 1);
        }
        {
            SingleNode<int> *n = new SingleNode<int>(0);
            n->InsertAtEnd(new SingleNode<int>(1));
            SingleNode<int> *c = new SingleNode<int>(2);
            c->Next() = c;
            n->Next() = c;
            check(n, 2);
        }
        {
            for (int i = 4; i < 100; i++)
            {
                Logger().WriteInformation("Test %d nodes\n", i);
                for (int j = 0; j < i; j++)
                {
                    SingleNode<int> *n;
                    SingleNode<int> *c = new SingleNode<int>(j);
                    c->Next() = c;
                    for (int k = j + 1; k < i; k++)
                    {
                        c->InsertAtEnd(new SingleNode<int>(k));
                    }
                    if (j == 0)
                    {
                        n = c;
                    }
                    else
                    {
                        n = new SingleNode<int>(0);
                        SingleNode<int> *p = n;
                        for (int k = 1; k < j; k++)
                        {
                            p = new SingleNode<int>(k);
                            n->InsertAtEnd(p);
                        }
                        p->Next() = c;
                    }
                    check(n, j);
                }
            }
        }
    });

    Add("DoubleNode1", [&]() {
        {
            DoubleNode<int> node(1);
            cout << &node;
        }
        {
            DoubleNode<int> *p = new DoubleNode<int>(2);
            cout << p;
            delete p;
        }
        {
            DoubleNode<int> *n1 = new DoubleNode<int>(1);
            DoubleNode<int> *n2 = new DoubleNode<int>(2);
            DoubleNode<int> *n3 = new DoubleNode<int>(3);
            DoubleNode<int> *n4 = new DoubleNode<int>(4);
            n1->Next() = n2;
            n2->Prev() = n1;
            n2->Next() = n3;
            n3->Prev() = n2;
            n3->Next() = n4;
            n4->Prev() = n3;

            cout << n1;
            DoubleNode<int>::DeleteList(n1);
        }
        {
            DoubleNode<int> *n1 = new DoubleNode<int>(1);
            DoubleNode<int> *n2 = new DoubleNode<int>(2);
            DoubleNode<int> *n3 = new DoubleNode<int>(3);
            DoubleNode<int> *n4 = new DoubleNode<int>(4);
            n1->Next(n2);
            n2->Prev(n1);
            n2->Next(n3);
            n3->Prev(n2);
            n3->Next(n4);
            n4->Prev(n3);
            n4->Next(n1);
            n1->Prev(n4);

            cout << n1;
            DoubleNode<int>::DeleteList(n1);
        }
    });

    Add("DoubleNodeClone", [&]() {
        {
            DoubleNode<int> node(1);
            cout << &node;
            DoubleNode<int> *copy = (DoubleNode<int> *)Node<int>::Clone(&node);
            cout << copy;
            ASSERT1(copy->Value() == 1);
            ASSERT1(copy->Prev() == nullptr);
            ASSERT1(copy->Next() == nullptr);
            delete copy;
        }
        {
            DoubleNode<int> node(1);
            node.Prev() = &node;
            node.Next() = &node;
            cout << &node;
            DoubleNode<int> *copy = (DoubleNode<int> *)Node<int>::Clone(&node);
            cout << copy;
            ASSERT1(copy->Value() == 1);
            ASSERT1(copy->Prev() == copy);
            ASSERT1(copy->Next() == copy);
            delete copy;
        }
        {
            DoubleNode<int> *n1 = new DoubleNode<int>(1);
            DoubleNode<int> *n2 = new DoubleNode<int>(2);
            DoubleNode<int> *n3 = new DoubleNode<int>(3);
            DoubleNode<int> *n4 = new DoubleNode<int>(4);
            n1->Next() = n2;
            n2->Prev() = n1;
            n2->Next() = n3;
            n3->Prev() = n2;
            n3->Next() = n4;
            n4->Prev() = n3;

            DoubleNode<int> *copy = (DoubleNode<int> *)Node<int>::Clone(n1);

            cout << n1;
            cout << copy;

            DoubleNode<int>::DeleteList(n1);
            DoubleNode<int>::DeleteList(copy);
        }
        {
            DoubleNode<int> *n1 = new DoubleNode<int>(1);
            DoubleNode<int> *n2 = new DoubleNode<int>(2);
            DoubleNode<int> *n3 = new DoubleNode<int>(3);
            DoubleNode<int> *n4 = new DoubleNode<int>(4);
            n1->Next() = n2;
            n2->Prev() = n1;
            n2->Next() = n3;
            n3->Prev() = n1;
            n3->Next() = n4;
            n4->Prev() = n1;

            DoubleNode<int> *copy = (DoubleNode<int> *)Node<int>::Clone(n1);

            cout << n1;
            cout << copy;

            ASSERT1(copy->Prev() == nullptr);
            ASSERT1(copy->Value() == 1);
            ASSERT1(copy->Next()->Value() == 2);
            ASSERT1(copy->Next()->Prev() == copy);
            ASSERT1(copy->Next()->Next()->Value() == 3);
            ASSERT1(copy->Next()->Next()->Prev() == copy);
            ASSERT1(copy->Next()->Next()->Next()->Value() == 4);
            ASSERT1(copy->Next()->Next()->Next()->Prev() == copy);
            ASSERT1(copy->Next()->Next()->Next()->Next() == nullptr);

            DoubleNode<int>::DeleteList(n1);
            DoubleNode<int>::DeleteList(copy);
        }
        {
            DoubleNode<int> *n1 = new DoubleNode<int>(1);
            DoubleNode<int> *n2 = new DoubleNode<int>(2);
            DoubleNode<int> *n3 = new DoubleNode<int>(3);
            DoubleNode<int> *n4 = new DoubleNode<int>(4);
            n1->Prev() = n4;
            n1->Next() = n2;
            n2->Prev() = n4;
            n2->Next() = n3;
            n3->Prev() = n4;
            n3->Next() = n4;
            n4->Prev() = n4;
            n4->Next() = nullptr;

            DoubleNode<int> *copy = (DoubleNode<int> *)Node<int>::Clone(n1);

            cout << n1;
            cout << copy;

            ASSERT1(copy->Prev() == copy->Next()->Next()->Next());
            ASSERT1(copy->Value() == 1);
            ASSERT1(copy->Next()->Value() == 2);
            ASSERT1(copy->Next()->Prev() == copy->Next()->Next()->Next());
            ASSERT1(copy->Next()->Next()->Value() == 3);
            ASSERT1(copy->Next()->Next()->Prev() == copy->Next()->Next()->Next());
            ASSERT1(copy->Next()->Next()->Next()->Value() == 4);
            ASSERT1(copy->Next()->Next()->Next()->Prev() == copy->Next()->Next()->Next());
            ASSERT1(copy->Next()->Next()->Next()->Next() == nullptr);

            DoubleNode<int>::DeleteList(n1);
            DoubleNode<int>::DeleteList(copy);
        }
    });

    Add("Destructor", [&]() {
        {
            BinaryNode<int> *node = new BinaryNode<int>(0);
            node->Left() = new BinaryNode<int>(1);
            node->Right() = new BinaryNode<int>(2);
            cout << node->Left()->Value() << endl;
            cout << node->Right()->Value() << endl;
            cout << node->Value() << endl;
            node->Print();
            node->Print2();
            node->DeleteTree();
        }
        {
            BinaryNodeWithParent<int> *node = new BinaryNodeWithParent<int>(0);
            node->Left(new BinaryNodeWithParent<int>(1));
            node->Right(new BinaryNodeWithParent<int>(2));
            cout << node->Left()->Value() << endl;
            cout << node->Right()->Value() << endl;
            cout << node->Value() << endl;
            node->Print();
            node->Print2();
            node->DeleteTree();
        }
    });

    Add("RandomTreePreOrder", [&]() {
        auto check = [&](vector<int> &v) {
            BinaryNode<int> *node = BinaryNode<int>::RandomTreeFromPreOrder(v);
            node->Print2();
            vector<int> v1;
            function<void(int)> w = [&](int n) { v1.push_back(n); };
            BinaryNode<int>::PreOrderWalk(node, w);
            BinaryNode<int>::DeleteTree(node);
            ASSERT1(v.size() == v1.size());
            for (size_t i = 0; i < v.size(); i++)
            {
                ASSERT1(v[i] == v1[i]);
            }
        };
        {
            vector<int> v = {0};
            check(v);
        }
        {
            vector<int> v = {0, 1};
            check(v);
        }
        {
            vector<int> v = {0, 1, 2};
            check(v);
        }
        {
            vector<int> v = {0, 1, 2, 3, 4};
            check(v);
        }
        {
            for (int i = 0; i < 100; i++)
            {
                int n = 1 + (rand() % 25);
                vector<int> v;
                for (int j = 0; j < n; j++)
                {
                    v.push_back(rand());
                }
                check(v);
            }
        }
    });

    Add("RandomTreeInOrder", [&]() {
        auto check = [&](vector<int> &v) {
            BinaryNode<int> *node = BinaryNode<int>::RandomTreeFromInOrder(v);
            node->Print2();
            vector<int> v1;
            function<void(int)> w = [&](int n) { v1.push_back(n); };
            BinaryNode<int>::InOrderWalk(node, w);
            BinaryNode<int>::DeleteTree(node);
            ASSERT1(v.size() == v1.size());
            for (size_t i = 0; i < v.size(); i++)
            {
                ASSERT1(v[i] == v1[i]);
            }
        };
        {
            vector<int> v = {0};
            check(v);
        }
        {
            vector<int> v = {0, 1};
            check(v);
        }
        {
            vector<int> v = {0, 1, 2};
            check(v);
        }
        {
            vector<int> v = {0, 1, 2, 3, 4};
            check(v);
        }
        {
            for (int i = 0; i < 100; i++)
            {
                int n = 1 + (rand() % 25);
                vector<int> v;
                for (int j = 0; j < n; j++)
                {
                    v.push_back(rand());
                }
                check(v);
            }
        }
    });

    Add("RandomTreePostOrder", [&]() {
        auto check = [&](vector<int> &v) {
            BinaryNode<int> *node = BinaryNode<int>::RandomTreeFromPostOrder(v);
            node->Print2();
            vector<int> v1;
            function<void(int)> w = [&](int n) { v1.push_back(n); };
            BinaryNode<int>::PostOrderWalk(node, w);
            BinaryNode<int>::DeleteTree(node);
            ASSERT1(v.size() == v1.size());
            for (size_t i = 0; i < v.size(); i++)
            {
                ASSERT1(v[i] == v1[i]);
            }
        };
        {
            vector<int> v = {0};
            check(v);
        }
        {
            vector<int> v = {0, 1};
            check(v);
        }
        {
            vector<int> v = {0, 1, 2};
            check(v);
        }
        {
            vector<int> v = {0, 1, 2, 3, 4};
            check(v);
        }
        {
            for (int i = 0; i < 100; i++)
            {
                int n = 1 + (rand() % 25);
                vector<int> v;
                for (int j = 0; j < n; j++)
                {
                    v.push_back(rand());
                }
                check(v);
            }
        }
    });

    Add("CompleteTree", [&]() {
        auto check = [&](vector<int> &v) {
            BinaryNode<int> *node = BinaryNode<int>::ToCompleteTree(v);
            BinaryNode<int> *node2 = BinaryNode<int>::FillToComplete(nullptr, v);
            BinaryNode<int> *node3 = nullptr;
            for_each(v.begin(), v.end(), [&](int i) {
                node3 = BinaryNode<int>::Insert(node3, i);
            });
            if (v.size() == 0)
            {
                ASSERT1(node == nullptr);
                ASSERT1(node2 == nullptr);
                ASSERT1(node3 == nullptr);
            }
            else
            {
                node->Print2();
                bool complete = BinaryNode<int>::IsCompleteTree(node);
                bool complete2 = BinaryNode<int>::IsCompleteTree(node2);
                bool complete3 = BinaryNode<int>::IsCompleteTree(node3);
                int equal = BinaryNode<int>::Compare(node, node2);
                int equal2 = BinaryNode<int>::Compare2(node, node2);
                int equal3 = BinaryNode<int>::Compare(node, node3);
                BinaryNode<int>::DeleteTree(node);
                BinaryNode<int>::DeleteTree(node2);
                BinaryNode<int>::DeleteTree(node3);
                ASSERT1(complete == true);
                ASSERT1(complete2 == true);
                ASSERT1(complete3 == true);
                ASSERT1(equal == 0);
                ASSERT1(equal2 == 0);
                ASSERT1(equal3 == 0);
            }
        };
        check(vector<int>{});
        check(vector<int>{0});
        check(vector<int>{0, 1});
        check(vector<int>{0, 1, 2});
        check(vector<int>{0, 1, 2, 3});
        check(vector<int>{0, 1, 2, 3, 4});
        for (int i = 5; i < 50; i++)
        {
            vector<int> v;
            for (int j = 0; j <= i; j++)
            {
                v.push_back(j);
            }
            check(v);
        }
    });

    Add("IsComplete", [&]() {
        auto check = [&](BinaryNode<int> *node, bool expect) {
            node->Print2();
            bool complete = BinaryNode<int>::IsCompleteTree(node);
            BinaryNode<int>::DeleteTree(node);
            ASSERT1(complete == expect);
        };
        {
            BinaryNode<int> *n0 = new BinaryNode<int>(0);
            check(n0, true);
        }
        {
            BinaryNode<int> *n0 = new BinaryNode<int>(0);
            BinaryNode<int> *n1 = new BinaryNode<int>(1);
            n0->Right() = n1;
            check(n0, false);
        }
        {
            BinaryNode<int> *n0 = new BinaryNode<int>(0);
            BinaryNode<int> *n1 = new BinaryNode<int>(1);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            n0->Left() = n1;
            n1->Left() = n2;
            check(n0, false);
        }
        {
            BinaryNode<int> *n0 = new BinaryNode<int>(0);
            BinaryNode<int> *n1 = new BinaryNode<int>(1);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            n0->Right() = n1;
            n1->Right() = n2;
            check(n0, false);
        }
        {
            BinaryNode<int> *n0 = new BinaryNode<int>(0);
            BinaryNode<int> *n1 = new BinaryNode<int>(1);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            BinaryNode<int> *n3 = new BinaryNode<int>(3);
            n0->Left() = n1;
            n0->Right() = n2;
            n1->Left() = n3;
            check(n0, true);
        }
        {
            BinaryNode<int> *n0 = new BinaryNode<int>(0);
            BinaryNode<int> *n1 = new BinaryNode<int>(1);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            BinaryNode<int> *n3 = new BinaryNode<int>(3);
            n0->Left() = n1;
            n0->Right() = n2;
            n1->Right() = n3;
            check(n0, false);
        }
        {
            BinaryNode<int> *n0 = new BinaryNode<int>(0);
            BinaryNode<int> *n1 = new BinaryNode<int>(1);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            BinaryNode<int> *n3 = new BinaryNode<int>(3);
            BinaryNode<int> *n4 = new BinaryNode<int>(4);
            BinaryNode<int> *n5 = new BinaryNode<int>(5);
            n0->Left() = n1;
            n0->Right() = n2;
            n1->Left() = n3;
            n1->Right() = n4;
            n2->Left() = n5;
            check(n0, true);
        }
        {
            BinaryNode<int> *n0 = new BinaryNode<int>(0);
            BinaryNode<int> *n1 = new BinaryNode<int>(1);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            BinaryNode<int> *n3 = new BinaryNode<int>(3);
            BinaryNode<int> *n4 = new BinaryNode<int>(4);
            BinaryNode<int> *n5 = new BinaryNode<int>(5);
            BinaryNode<int> *n6 = new BinaryNode<int>(6);
            n0->Left() = n1;
            n0->Right() = n2;
            n1->Left() = n3;
            n1->Right() = n4;
            n2->Left() = n5;
            n3->Left() = n6;
            check(n0, false);
        }
    });

    Add("FillToComplete", [&]() {
        auto check = [&](BinaryNode<int> *node, vector<int> values) {
            node->Print2();
            node = BinaryNode<int>::FillToComplete(node, values);
            node->Print2();
            BinaryNode<int>::DeleteTree(node);
        };
        {
            BinaryNode<int> *n0 = new BinaryNode<int>(0);
            vector<int> v = {1};
            check(n0, v);
        }
        {
            BinaryNode<int> *n0 = new BinaryNode<int>(0);
            vector<int> v = {1, 2};
            check(n0, v);
        }
        {
            BinaryNode<int> *n0 = new BinaryNode<int>(0);
            BinaryNode<int> *n1 = new BinaryNode<int>(1);
            n0->Left() = n1;
            vector<int> v = {2};
            check(n0, v);
        }
        {
            BinaryNode<int> *n0 = new BinaryNode<int>(0);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            n0->Right() = n2;
            vector<int> v = {1};
            check(n0, v);
        }
        {
            BinaryNode<int> *n0 = new BinaryNode<int>(0);
            BinaryNode<int> *n1 = new BinaryNode<int>(1);
            n0->Left() = n1;
            vector<int> v = {2, 3};
            check(n0, v);
        }
        {
            BinaryNode<int> *n0 = new BinaryNode<int>(0);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            n0->Right() = n2;
            vector<int> v = {1, 3};
            check(n0, v);
        }
        {
            BinaryNode<int> *n0 = new BinaryNode<int>(0);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            BinaryNode<int> *n5 = new BinaryNode<int>(5);
            n0->Right() = n2;
            n2->Left() = n5;
            vector<int> v = {1, 3};
            check(n0, v);
        }
        {
            BinaryNode<int> *n0 = new BinaryNode<int>(0);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            BinaryNode<int> *n5 = new BinaryNode<int>(5);
            n0->Right() = n2;
            n2->Left() = n5;
            vector<int> v = {1, 3, 4, 6};
            check(n0, v);
        }
    });

    Add("Search1", [&]() {
        auto check = [&](size_t s) {
            vector<int> v;
            for (size_t i = 0; i < s; i++)
            {
                v.push_back(i);
            }
            BinaryNode<int> *node = BinaryNode<int>::RandomTreeFromInOrder(v);
            node->Print2();
            bool pass = true;
            int num;
            bool pass2 = true;
            int num2;
            BinaryNode<int> *n;
            for_each(v.begin(), v.end(), [&](int i) {
                n = BinaryNode<int>::Search(node, i);
                if (n == nullptr || n->Value() != i)
                {
                    pass = false;
                    num = i;
                }
                i = s + rand();
                n = BinaryNode<int>::Search(node, i);
                if (n != nullptr && n->Value() == i)
                {
                    pass2 = false;
                    num2 = i;
                }
            });
            BinaryNode<int>::DeleteTree(node);
            ASSERT2(pass == true, String::Format("%d is not found", num));
            ASSERT2(pass2 == true, String::Format("%d is found", num2));
        };
        check(1);
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        for (int i = 7; i < 50; i++)
        {
            check(i);
        }
    });

    Add("LowestCommonAncestor1", [&]() {
        auto check = [&](size_t s) {
            vector<int> v;
            for (size_t i = 0; i < s; i++)
            {
                v.push_back(i);
            }
            BinaryNode<int> *node = BinaryNode<int>::RandomTreeFromInOrder(v);
            node->Print2();
            for (size_t i = 0; i < s - 1; i++)
            {
                for (size_t j = i + 1; j < s; j++)
                {
                    BinaryNode<int> *f = BinaryNode<int>::Search(node, v[i]);
                    BinaryNode<int> *s = BinaryNode<int>::Search(node, v[j]);
                    BinaryNode<int> *a = BinaryNode<int>::LowestCommonAncestor(node, f, s);
                    BinaryNode<int> *a2 = BinaryNode<int>::LowestCommonAncestor2(node, f, s);
                    Logger().WriteInformation("LCA(%d, %d) = %d, %d\n", v[i], v[j], a->Value(), a2->Value());
                    ASSERT1(a == a2);
                }
            }
            BinaryNode<int>::DeleteTree(node);
        };
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        for (int i = 7; i < 50; i++)
        {
            check(i);
        }
    });

    Add("LowestCommonAncestor2", [&]() {
        auto check = [&](size_t s) {
            vector<int> v;
            for (size_t i = 0; i < s; i++)
            {
                v.push_back(i);
            }
            BinaryNode<int> *n = BinaryNode<int>::RandomTreeFromInOrder(v);
            BinaryNodeWithParent<int> *node = BinaryNodeWithParent<int>::Clone2(n);
            BinaryNode<int>::DeleteTree(n);
            node->Print2();
            for (size_t i = 0; i < s - 1; i++)
            {
                for (size_t j = i + 1; j < s; j++)
                {
                    BinaryNodeWithParent<int> *f = (BinaryNodeWithParent<int> *)BinaryNode<int>::Search(node, v[i]);
                    BinaryNodeWithParent<int> *s = (BinaryNodeWithParent<int> *)BinaryNode<int>::Search(node, v[j]);
                    BinaryNodeWithParent<int> *a = BinaryNodeWithParent<int>::LowestCommonAncestor(f, s);
                    BinaryNodeWithParent<int> *a2 = BinaryNodeWithParent<int>::LowestCommonAncestor2(f, s);
                    Logger().WriteInformation("LCA(%d, %d) = %d, %d\n", v[i], v[j], a->Value(), a2->Value());
                    ASSERT1(a == a2);
                }
            }
            BinaryNode<int>::DeleteTree(node);
        };
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        for (int i = 7; i < 50; i++)
        {
            check(i);
        }
    });

    Add("LowestCommonAncestor3", [&]() {
        auto check = [&](size_t s) {
            vector<int> v;
            for (size_t i = 0; i < s; i++)
            {
                v.push_back(i);
            }
            BinaryNode<int> *n = BinaryNode<int>::SearchTreeRandom(v);
            BinaryNodeWithParent<int> *node = BinaryNodeWithParent<int>::Clone2(n);
            BinaryNode<int>::DeleteTree(n);
            node->Print2();
            for (size_t i = 0; i < s - 1; i++)
            {
                for (size_t j = i + 1; j < s; j++)
                {
                    BinaryNodeWithParent<int> *f = (BinaryNodeWithParent<int> *)BinaryNode<int>::Search(node, v[i]);
                    BinaryNodeWithParent<int> *s = (BinaryNodeWithParent<int> *)BinaryNode<int>::Search(node, v[j]);
                    BinaryNodeWithParent<int> *a = (BinaryNodeWithParent<int> *)BinaryNode<int>::LowestCommonAncestor(node, f, s);
                    BinaryNodeWithParent<int> *a2 = (BinaryNodeWithParent<int> *)BinaryNode<int>::LowestCommonAncestor2(node, f, s);
                    BinaryNodeWithParent<int> *a3 = BinaryNodeWithParent<int>::LowestCommonAncestor(f, s);
                    BinaryNodeWithParent<int> *a4 = BinaryNodeWithParent<int>::LowestCommonAncestor2(f, s);
                    BinaryNodeWithParent<int> *a5 = (BinaryNodeWithParent<int> *)BinaryNode<int>::SearchTreeLowestCommonAncestor(node, v[i], v[j]);
                    Logger().WriteInformation("LCA(%d, %d) = %d, %d, %d, %d, %d\n", v[i], v[j], a->Value(), a2->Value(), a3->Value(), a4->Value(), a5->Value());
                    ASSERT1(a == a2);
                    ASSERT1(a == a3);
                    ASSERT1(a == a4);
                    ASSERT1(a == a5);
                }
            }
            BinaryNode<int>::DeleteTree(node);
        };
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        for (int i = 7; i < 50; i++)
        {
            check(i);
        }
    });

    Add("BuildTreePreOrderInOrder", [&]() {
        auto check = [&](size_t s) {
            BinaryNode<int> *node = nullptr;
            while (node == nullptr)
                node = BinaryNode<int>::RandomTree(s);
            node->Print2();

            int count = BinaryNode<int>::Size(node);
            unique_ptr<int[]> preOrder(new int[count]);
            unique_ptr<int[]> inOrder(new int[count]);

            function<function<void(int)>(unique_ptr<int[]> &, int &)>
                f = [&](unique_ptr<int[]> &v, int &k) -> function<void(int)> {
                function<void(int)> w = [&](int n) {
                    v[k++] = n;
                };
                return w;
            };

            int i = 0;
            int j = 0;
            BinaryNode<int>::PreOrderWalk(node, f(preOrder, i));
            BinaryNode<int>::InOrderWalk(node, f(inOrder, j));

            Logger().WriteInformation("PreOrder: ");
            Logger().Print(preOrder.get(), count);
            Logger().WriteInformation("InOrder: ");
            Logger().Print(inOrder.get(), count);

            int equal2;
            int equal3;
            BinaryNode<int> *node2 = BinaryNode<int>::BuildTreePreOrderInOrder(preOrder.get(), count, inOrder.get(), count);
            BinaryNode<int> *node3 = BinaryNode<int>::BuildTreePreOrderInOrder2(preOrder.get(), count, inOrder.get(), count);
            node2->Print2();
            node3->Print2();
            equal2 = BinaryNode<int>::Compare(node, node2);
            equal3 = BinaryNode<int>::Compare(node, node3);
            BinaryNode<int>::DeleteTree(node);
            BinaryNode<int>::DeleteTree(node2);
            BinaryNode<int>::DeleteTree(node3);
            ASSERT1(equal2 == 0);
            ASSERT1(equal3 == 0);
        };
        check(1);
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        check(7);
        check(8);
        check(9);
        check(10);
        for (int i = 11; i < 50; i++)
        {
            check(i);
        }
    });

    Add("BuildTreeInOrderPostOrder", [&]() {
        auto check = [&](size_t s) {
            BinaryNode<int> *node = nullptr;
            while (node == nullptr)
                node = BinaryNode<int>::RandomTree(s);
            node->Print2();

            int count = BinaryNode<int>::Size(node);
            unique_ptr<int[]> inOrder(new int[count]);
            unique_ptr<int[]> postOrder(new int[count]);

            function<function<void(int)>(unique_ptr<int[]> &, int &)>
                f = [&](unique_ptr<int[]> &v, int &k) -> function<void(int)> {
                function<void(int)> w = [&](int n) {
                    v[k++] = n;
                };
                return w;
            };

            int i = 0;
            int j = 0;
            BinaryNode<int>::InOrderWalk(node, f(inOrder, i));
            BinaryNode<int>::PostOrderWalk(node, f(postOrder, j));

            Logger().WriteInformation("InOrder: ");
            Logger().Print(inOrder.get(), count);
            Logger().WriteInformation("PostOrder: ");
            Logger().Print(postOrder.get(), count);

            int equal2;
            int equal3;
            BinaryNode<int> *node2 = BinaryNode<int>::BuildTreeInOrderPostOrder(inOrder.get(), count, postOrder.get(), count);
            BinaryNode<int> *node3 = BinaryNode<int>::BuildTreeInOrderPostOrder2(inOrder.get(), count, postOrder.get(), count);
            node2->Print2();
            node3->Print2();
            equal2 = BinaryNode<int>::Compare(node, node2);
            equal3 = BinaryNode<int>::Compare(node, node3);
            BinaryNode<int>::DeleteTree(node);
            BinaryNode<int>::DeleteTree(node2);
            BinaryNode<int>::DeleteTree(node3);
            ASSERT1(equal2 == 0);
            ASSERT1(equal3 == 0);
        };
        check(1);
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        check(7);
        check(8);
        check(9);
        check(10);
        for (int i = 11; i < 50; i++)
        {
            check(i);
        }
    });

    Add("ToPreOrderLinkList", [&]() {
        auto check = [&](size_t s) {
            BinaryNode<int> *node = nullptr;
            while (node == nullptr)
                node = BinaryNode<int>::RandomTree(s);
            node->Print2();

            vector<int> preOrder;
            auto f = [&](int n) { preOrder.push_back(n); };
            BinaryNode<int>::PreOrderWalk(node, f);
            Logger().Print(preOrder);

            DoubleNode<int> *list = (DoubleNode<int> *)BinaryNode<int>::ToPreOrderLinkList(node);
            cout << list;

            size_t i = 0;
            DoubleNode<int> *p = list;
            while (i < preOrder.size() && p != nullptr)
            {
                ASSERT1(preOrder[i] == p->Value());
                i++;
                p = p->Next();
            }
            DoubleNode<int>::DeleteList(list);
            ASSERT1(i == preOrder.size());
            ASSERT1(p == nullptr);
        };
        check(1);
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        check(7);
        check(8);
        check(9);
        check(10);
        for (int i = 11; i < 50; i++)
        {
            check(i);
        }
    });

    Add("ToInOrderLinkList", [&]() {
        auto check = [&](size_t s) {
            BinaryNode<int> *node = nullptr;
            while (node == nullptr)
                node = BinaryNode<int>::RandomTree(s);
            node->Print2();

            vector<int> inOrder;
            auto f = [&](int n) { inOrder.push_back(n); };
            BinaryNode<int>::InOrderWalk(node, f);
            Logger().Print(inOrder);

            DoubleNode<int> *list = (DoubleNode<int> *)BinaryNode<int>::ToInOrderLinkList(node);
            cout << list;

            size_t i = 0;
            DoubleNode<int> *p = list;
            while (i < inOrder.size() && p != nullptr)
            {
                ASSERT1(inOrder[i] == p->Value());
                i++;
                p = p->Next();
            }
            DoubleNode<int>::DeleteList(list);
            ASSERT1(i == inOrder.size());
            ASSERT1(p == nullptr);
        };
        check(1);
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        check(7);
        check(8);
        check(9);
        check(10);
        for (int i = 11; i < 50; i++)
        {
            check(i);
        }
    });

    Add("ToPostOrderLinkList", [&]() {
        auto check = [&](size_t s) {
            BinaryNode<int> *node = nullptr;
            while (node == nullptr)
                node = BinaryNode<int>::RandomTree(s);
            node->Print2();

            vector<int> postOrder;
            auto f = [&](int n) { postOrder.push_back(n); };
            BinaryNode<int>::PostOrderWalk(node, f);
            Logger().Print(postOrder);

            DoubleNode<int> *list = (DoubleNode<int> *)BinaryNode<int>::ToPostOrderLinkList(node);
            cout << list;

            size_t i = 0;
            DoubleNode<int> *p = list;
            while (i < postOrder.size() && p != nullptr)
            {
                ASSERT1(postOrder[i] == p->Value());
                i++;
                p = p->Next();
            }
            DoubleNode<int>::DeleteList(list);
            ASSERT1(i == postOrder.size());
            ASSERT1(p == nullptr);
        };
        check(1);
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        check(7);
        check(8);
        check(9);
        check(10);
        for (int i = 11; i < 50; i++)
        {
            check(i);
        }
    });

    Add("ToBalancedTree", [&]() {
        auto check = [&](size_t s) {
            SingleNode<int> *list = SingleNode<int>::RandomList(s);
            cout << list;
            SingleNode<int> *list2 = (SingleNode<int> *)Node<int>::Clone(list);
            cout << list2;
            BinaryNode<int> *tree = BinaryNode<int>::ToBalancedTree(list);
            tree->Print2();
            BinaryNode<int> *tree2 = BinaryNode<int>::ToBalancedTree2(list2);
            tree2->Print2();
            int equal = BinaryNode<int>::Compare(tree, tree2);
            BinaryNode<int>::DeleteTree(tree);
            BinaryNode<int>::DeleteTree(tree2);
            ASSERT1(equal == 0);
        };
        check(1);
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        check(7);
        check(8);
        check(9);
        check(10);
        for (int i = 11; i < 50; i++)
        {
            check(i);
        }
    });

    Add("GetBoundaryValues1", [&]() {
        auto check = [&](int count) {
            Logger().WriteInformation("Get boundary values of a binary tree of %d nodes:\n", count);
            BinaryNode<int> *tree = nullptr;
            while (tree == nullptr)
                tree = BinaryNode<int>::RandomTree(count);
            tree->Print2();
            vector<int> values;
            tree->GetBoundaryValues(values);
            Logger().Print(values);
        };

        check(1);
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        check(7);
        check(8);
        check(9);
        check(10);
        check(11);
        check(12);
        check(13);
        check(14);
        check(15);
        check(16);
    });

    Add("GetBoundaryValues2", [&]() {
        Logger().WriteInformation("Get boundary values of a binary tree\n");
        BinaryNode<int> *n0 = new BinaryNode<int>(0);
        BinaryNode<int> *n1 = new BinaryNode<int>(1);
        BinaryNode<int> *n2 = new BinaryNode<int>(2);
        BinaryNode<int> *n3 = new BinaryNode<int>(3);
        BinaryNode<int> *n4 = new BinaryNode<int>(4);
        BinaryNode<int> *n5 = new BinaryNode<int>(5);
        BinaryNode<int> *n6 = new BinaryNode<int>(6);
        BinaryNode<int> *n7 = new BinaryNode<int>(7);
        BinaryNode<int> *n8 = new BinaryNode<int>(8);
        BinaryNode<int> *n9 = new BinaryNode<int>(9);
        BinaryNode<int> *n10 = new BinaryNode<int>(10);
        BinaryNode<int> *n11 = new BinaryNode<int>(11);
        BinaryNode<int> *n12 = new BinaryNode<int>(12);
        BinaryNode<int> *n13 = new BinaryNode<int>(13);
        BinaryNode<int> *n14 = new BinaryNode<int>(14);
        BinaryNode<int> *n15 = new BinaryNode<int>(15);
        BinaryNode<int> *n16 = new BinaryNode<int>(16);
        n0->Left() = n1;
        n0->Right() = n9;
        n1->Right() = n2;
        n2->Left() = n3;
        n2->Right() = n5;
        n3->Right() = n4;
        n5->Left() = n6;
        n5->Right() = n8;
        n6->Left() = n7;
        n9->Left() = n10;
        n10->Left() = n11;
        n10->Right() = n15;
        n11->Left() = n12;
        n11->Right() = n13;
        n13->Right() = n14;
        n15->Left() = n16;

        n0->Print2();

        vector<int> expect = {0, 1, 2, 3, 4, 7, 8, 12, 14, 16, 15, 10, 9};

        vector<int> values;
        n0->GetBoundaryValues(values);

        Logger().Print(values);

        ASSERT1(values.size() == expect.size());
        for (unsigned int i = 0; i < expect.size(); i++)
        {
            ASSERT1(values[i] == expect[i]);
        }
    });

    Add("Serialize", [&]() {
        auto check = [&](int count) {
            Logger().WriteInformation("Serialize/deserialize a binary tree of %d nodes:\n", count);
            BinaryNode<int> *tree = nullptr;
            while (tree == nullptr)
                tree = BinaryNode<int>::RandomTree(count);
            tree->Print2();
            stringstream ss;
            BinaryNode<int>::Serialize(tree, ss);
            Logger().WriteInformation("%s\n", ss.str().c_str());
            BinaryNode<int> *tree2 = BinaryNode<int>::Deserialize(ss);
            tree2->Print2();
            int equal = BinaryNode<int>::Compare(tree, tree2);
            ASSERT1(equal == 0);
        };
        check(1);
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        check(7);
        check(8);
        check(9);
        check(10);
        check(11);
        check(12);
        check(13);
        check(14);
        check(15);
        check(16);
    });

    Add("Clone1", [&]() {
        auto check = [&](size_t s) {
            Node<int> *node = nullptr;
            while (node == nullptr)
                node = BinaryNode<int>::RandomTree(s);
            ((BinaryNode<int> *)node)->Print2();
            BinaryNode<int> *copy = (BinaryNode<int> *)Node<int>::Clone(node);
            copy->Print2();
            int equal = BinaryNode<int>::Compare((BinaryNode<int> *)node, copy);
            BinaryNode<int>::DeleteTree((BinaryNode<int> *)node);
            BinaryNode<int>::DeleteTree(copy);
            ASSERT1(equal == 0);
        };
        check(1);
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        check(7);
        check(8);
        check(9);
        check(10);
    });

    Add("Clone2", [&]() {
        auto check = [&](size_t s) {
            BinaryNode<int> *node = nullptr;
            while (node == nullptr)
                node = BinaryNode<int>::RandomTree(s);
            node->Print2();
            BinaryNodeWithParent<int> *copy = BinaryNodeWithParent<int>::Clone2(node);
            copy->Print2();
            int equal = BinaryNode<int>::Compare(node, copy);
            BinaryNode<int>::DeleteTree(node);
            BinaryNode<int>::DeleteTree(copy);
            ASSERT1(equal == 0);
        };
        check(1);
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        check(7);
        check(8);
        check(9);
        check(10);
    });

    Add("PreOrder", [&]() {
        for (int i = 0; i < 100; i++)
        {
            int count = 1 + rand();
            BinaryNode<int> *tree = nullptr;
            while (tree == nullptr)
                tree = BinaryNode<int>::RandomTree(count);
            count = tree->Size();

            BinaryNodeWithParent<int> *tree2 = BinaryNodeWithParent<int>::Clone2(tree);

            cout << "Run " << i << ", " << count << " elements" << endl;

            if (count < 50)
            {
                tree->Print2();
                tree2->Print2();
            }

            vector<int> v1;
            vector<int> v2;
            vector<int> v3;
            vector<int> v4;
            vector<int> v5;
            vector<int> v6;
            vector<int> v7;
            vector<int> v8;
            vector<int> v9;
            vector<int> v10;
            vector<int> v11;

            function<function<void(int)>(vector<int> &)> f = [&](vector<int> &v) -> function<void(int)> {
                function<void(int)> w = [&](int n) {
                    v.push_back(n);
                };

                return w;
            };

            tree->PreOrderWalk(f(v1));
            tree->PreOrderWalkWithStack(f(v2));
            tree->PreOrderWalkWithStack2(f(v3));
            tree->PreOrderWalkWithStack3(f(v4));
            tree2->PreOrderWalk(f(v5));
            tree2->PreOrderWalkWithStack(f(v6));
            tree2->PreOrderWalkWithStack2(f(v7));
            tree2->PreOrderWalkWithStack3(f(v8));
            tree2->PreOrderWalkWithOutStack(f(v9));

            for (PreOrderBinaryIterator<int, BinaryNode> it = PreOrderBinaryIterator<int, BinaryNode>(tree); it != PreOrderBinaryIterator<int, BinaryNode>(); it++)
            {
                v10.push_back(*it);
            }

            for (PreOrderBinaryIteratorWithOutStack<int> it = PreOrderBinaryIteratorWithOutStack<int>(tree2); it != PreOrderBinaryIteratorWithOutStack<int>(); it++)
            {
                v11.push_back(*it);
            }

            BinaryNode<int>::DeleteTree(tree);
            BinaryNode<int>::DeleteTree(tree2);

            ASSERT2(v1.size() == count, String::Format("Expect %d elements, actual visited %d", count, v1.size()));
            ASSERT2(v2.size() == count, String::Format("Expect %d elements, actual visited %d", count, v2.size()));
            ASSERT2(v3.size() == count, String::Format("Expect %d elements, actual visited %d", count, v3.size()));
            ASSERT2(v4.size() == count, String::Format("Expect %d elements, actual visited %d", count, v4.size()));
            ASSERT2(v5.size() == count, String::Format("Expect %d elements, actual visited %d", count, v5.size()));
            ASSERT2(v6.size() == count, String::Format("Expect %d elements, actual visited %d", count, v6.size()));
            ASSERT2(v7.size() == count, String::Format("Expect %d elements, actual visited %d", count, v7.size()));
            ASSERT2(v8.size() == count, String::Format("Expect %d elements, actual visited %d", count, v8.size()));
            ASSERT2(v9.size() == count, String::Format("Expect %d elements, actual visited %d", count, v9.size()));
            ASSERT2(v10.size() == count, String::Format("Expect %d elements, actual visited %d", count, v10.size()));
            ASSERT2(v11.size() == count, String::Format("Expect %d elements, actual visited %d", count, v11.size()));

            for (int j = 0; j < count; j++)
            {
                ASSERT1(v1[j] == v2[j]);
                ASSERT1(v1[j] == v3[j]);
                ASSERT1(v1[j] == v4[j]);
                ASSERT1(v1[j] == v5[j]);
                ASSERT1(v1[j] == v6[j]);
                ASSERT1(v1[j] == v7[j]);
                ASSERT1(v1[j] == v8[j]);
                ASSERT1(v1[j] == v9[j]);
                ASSERT1(v1[j] == v10[j]);
                ASSERT1(v1[j] == v11[j]);
            }
        }
    });

    Add("InOrder", [&]() {
        for (int i = 0; i < 100; i++)
        {
            int count = 1 + rand();
            BinaryNode<int> *tree = nullptr;
            while (tree == nullptr)
                tree = BinaryNode<int>::RandomTree(count);
            count = tree->Size();

            BinaryNodeWithParent<int> *tree2 = BinaryNodeWithParent<int>::Clone2(tree);

            cout << "Run " << i << ", " << count << " elements" << endl;

            if (count < 50)
            {
                tree->Print2();
                tree2->Print2();
            }

            vector<int> v1;
            vector<int> v2;
            vector<int> v3;
            vector<int> v4;
            vector<int> v5;
            vector<int> v6;
            vector<int> v7;
            vector<int> v8;
            vector<int> v9;

            function<function<void(int)>(vector<int> &)> f = [&](vector<int> &v) -> function<void(int)> {
                function<void(int)> w = [&](int n) {
                    v.push_back(n);
                };

                return w;
            };

            tree->InOrderWalk(f(v1));
            tree->InOrderWalkWithStack(f(v2));
            tree->InOrderWalkWithStack2(f(v3));
            tree2->InOrderWalk(f(v4));
            tree2->InOrderWalkWithStack(f(v5));
            tree2->InOrderWalkWithStack2(f(v6));
            tree2->InOrderWalkWithOutStack(f(v7));

            for (InOrderBinaryIterator<int, BinaryNode> it = InOrderBinaryIterator<int, BinaryNode>(tree); it != InOrderBinaryIterator<int, BinaryNode>(); it++)
            {
                v8.push_back(*it);
            }

            for (InOrderBinaryIteratorWithOutStack<int> it = InOrderBinaryIteratorWithOutStack<int>(tree2); it != InOrderBinaryIteratorWithOutStack<int>(); it++)
            {
                v9.push_back(*it);
            }

            BinaryNode<int>::DeleteTree(tree);
            BinaryNode<int>::DeleteTree(tree2);

            ASSERT2(v1.size() == count, String::Format("Expect %d elements, actual visited %d", count, v1.size()));
            ASSERT2(v2.size() == count, String::Format("Expect %d elements, actual visited %d", count, v2.size()));
            ASSERT2(v3.size() == count, String::Format("Expect %d elements, actual visited %d", count, v3.size()));
            ASSERT2(v4.size() == count, String::Format("Expect %d elements, actual visited %d", count, v4.size()));
            ASSERT2(v5.size() == count, String::Format("Expect %d elements, actual visited %d", count, v5.size()));
            ASSERT2(v6.size() == count, String::Format("Expect %d elements, actual visited %d", count, v6.size()));
            ASSERT2(v7.size() == count, String::Format("Expect %d elements, actual visited %d", count, v7.size()));
            ASSERT2(v8.size() == count, String::Format("Expect %d elements, actual visited %d", count, v8.size()));
            ASSERT2(v9.size() == count, String::Format("Expect %d elements, actual visited %d", count, v9.size()));

            for (int j = 0; j < count; j++)
            {
                ASSERT1(v1[j] == v2[j]);
                ASSERT1(v1[j] == v3[j]);
                ASSERT1(v1[j] == v4[j]);
                ASSERT1(v1[j] == v5[j]);
                ASSERT1(v1[j] == v6[j]);
                ASSERT1(v1[j] == v7[j]);
                ASSERT1(v1[j] == v8[j]);
                ASSERT1(v1[j] == v9[j]);
            }
        }
    });

    Add("PostOrder", [&]() {
        for (int i = 0; i < 100; i++)
        {
            int count = 1 + rand();
            BinaryNode<int> *tree = nullptr;
            while (tree == nullptr)
                tree = BinaryNode<int>::RandomTree(count);
            count = tree->Size();

            BinaryNodeWithParent<int> *tree2 = BinaryNodeWithParent<int>::Clone2(tree);

            cout << "Run " << i << ", " << count << " elements" << endl;

            if (count < 50)
            {
                tree->Print2();
                tree2->Print2();
            }

            vector<int> v1;
            vector<int> v2;
            vector<int> v3;
            vector<int> v4;
            vector<int> v5;
            vector<int> v6;
            vector<int> v7;
            vector<int> v8;
            vector<int> v9;

            function<function<void(int)>(vector<int> &)> f = [&](vector<int> &v) -> function<void(int)> {
                function<void(int)> w = [&](int n) {
                    v.push_back(n);
                };

                return w;
            };

            tree->PostOrderWalk(f(v1));
            tree->PostOrderWalkWithStack(f(v2));
            tree->PostOrderWalkWithStack2(f(v3));
            tree2->PostOrderWalk(f(v4));
            tree2->PostOrderWalkWithStack(f(v5));
            tree2->PostOrderWalkWithStack2(f(v6));
            tree2->PostOrderWalkWithOutStack(f(v7));

            for (PostOrderBinaryIterator<int, BinaryNode> it = PostOrderBinaryIterator<int, BinaryNode>(tree); it != PostOrderBinaryIterator<int, BinaryNode>(); it++)
            {
                v8.push_back(*it);
            }

            for (PostOrderBinaryIteratorWithOutStack<int> it = PostOrderBinaryIteratorWithOutStack<int>(tree2); it != PostOrderBinaryIteratorWithOutStack<int>(); it++)
            {
                v9.push_back(*it);
            }

            BinaryNode<int>::DeleteTree(tree);
            BinaryNode<int>::DeleteTree(tree2);

            ASSERT2(v1.size() == count, String::Format("Expect %d elements, actual visited %d", count, v1.size()));
            ASSERT2(v2.size() == count, String::Format("Expect %d elements, actual visited %d", count, v2.size()));
            ASSERT2(v3.size() == count, String::Format("Expect %d elements, actual visited %d", count, v3.size()));
            ASSERT2(v4.size() == count, String::Format("Expect %d elements, actual visited %d", count, v4.size()));
            ASSERT2(v5.size() == count, String::Format("Expect %d elements, actual visited %d", count, v5.size()));
            ASSERT2(v6.size() == count, String::Format("Expect %d elements, actual visited %d", count, v6.size()));
            ASSERT2(v7.size() == count, String::Format("Expect %d elements, actual visited %d", count, v7.size()));
            ASSERT2(v8.size() == count, String::Format("Expect %d elements, actual visited %d", count, v8.size()));
            ASSERT2(v9.size() == count, String::Format("Expect %d elements, actual visited %d", count, v9.size()));

            for (int j = 0; j < count; j++)
            {
                ASSERT1(v1[j] == v2[j]);
                ASSERT1(v1[j] == v3[j]);
                ASSERT1(v1[j] == v4[j]);
                ASSERT1(v1[j] == v5[j]);
                ASSERT1(v1[j] == v6[j]);
                ASSERT1(v1[j] == v7[j]);
                ASSERT1(v1[j] == v8[j]);
                ASSERT1(v1[j] == v9[j]);
            }
        }
    });

    Add("Height", [&]() {
        for (int i = 0; i < 100; i++)
        {
            int count = 1 + rand();
            BinaryNode<int> *tree = nullptr;
            while (tree == nullptr)
                tree = BinaryNode<int>::RandomTree(count);
            count = tree->Size();

            BinaryNodeWithParent<int> *tree2 = BinaryNodeWithParent<int>::Clone2(tree);

            cout << "Run " << i << ", " << count << " elements" << endl;

            if (count < 50)
            {
                tree->Print2();
                tree2->Print2();
            }

            int height = BinaryNode<int>::Height(tree);
            int height2 = BinaryNodeWithParent<int>::Height2(tree2);

            BinaryNode<int>::DeleteTree(tree);
            BinaryNode<int>::DeleteTree(tree2);

            ASSERT1(height == height2);
        }
    });

    Add("LevelOrderWalk1", [&]() {
        auto check = [&](int count) {
            Logger().WriteInformation("Level order walk a binary tree of %d nodes:\n", count);
            BinaryNode<int> *tree = nullptr;
            while (tree == nullptr)
                tree = BinaryNode<int>::RandomTree(count);
            BinaryNodeWithRightSibling<int> *tree2 = BinaryNodeWithRightSibling<int>::Clone2(tree);
            BinaryNodeWithRightSibling<int>::SetRightSibling(tree2);

            tree->Print2();
            tree2->Print2();

            vector<int> v1;
            vector<int> v2;
            vector<int> v3;

            auto visit = [&](vector<int> &v) -> function<void(int)> {
                function<void(int)> f = [&](int c) {
                    v.push_back(c);
                };
                return f;
            };

            tree->LevelOrderWalk(visit(v1));
            tree->LevelOrderWalk2(visit(v2));
            tree2->LevelOrderWalk3(visit(v3));
            Logger().Print(v1);
            Logger().Print(v2);
            Logger().Print(v3);

            ASSERT1(v1.size() == v2.size());
            ASSERT1(v1.size() == v3.size());
            for (unsigned int i = 0; i < v1.size(); i++)
            {
                ASSERT1(v1[i] == v2[i]);
                ASSERT1(v1[i] == v3[i]);
            }
        };

        check(1);
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        check(7);
        check(8);
        check(9);
        check(10);
        check(11);
        check(12);
        check(13);
        check(14);
        check(15);
        check(16);
    });

    Add("LevelOrderWalk2", [&]() {
        auto check = [&](int count) {
            Logger().WriteInformation("Level order walk a binary tree of %d nodes:\n", count);
            BinaryNode<int> *tree = nullptr;
            while (tree == nullptr)
                tree = BinaryNode<int>::RandomCompleteTree(count);

            BinaryNodeWithRightSibling<int> *tree2 = Test::BinaryNodeWithRightSibling<int>::Clone2(tree);
            BinaryNodeWithRightSibling<int>::SetRightSibling(tree2);

            BinaryNodeWithRightSibling<int> *tree3 = Test::BinaryNodeWithRightSibling<int>::Clone2(tree);
            BinaryNodeWithRightSibling<int>::SetRightSibling2(tree3);

            tree->Print2();
            tree2->Print2();
            tree3->Print2();

            vector<int> v1;
            vector<int> v2;
            vector<int> v3;
            vector<int> v4;

            auto visit = [&](vector<int> &v) -> function<void(int)> {
                function<void(int)> f = [&](int c) {
                    v.push_back(c);
                };
                return f;
            };

            tree->LevelOrderWalk(visit(v1));
            tree->LevelOrderWalk2(visit(v2));
            tree2->LevelOrderWalk3(visit(v3));
            tree3->LevelOrderWalk3(visit(v4));

            Logger().Print(v1);
            Logger().Print(v2);
            Logger().Print(v3);
            Logger().Print(v4);

            ASSERT1(v1.size() == v2.size());
            ASSERT1(v1.size() == v3.size());
            ASSERT1(v1.size() == v4.size());
            for (unsigned int i = 0; i < v1.size(); i++)
            {
                ASSERT1(v1[i] == v2[i]);
                ASSERT1(v1[i] == v3[i]);
                ASSERT1(v1[i] == v4[i]);
            }
        };

        check(1);
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        check(7);
        check(8);
        check(9);
        check(10);
        check(11);
        check(12);
        check(13);
        check(14);
        check(15);
        check(16);
    });

    Add("Min", [&]() {
        auto check = [&](size_t s) {
            vector<int> v;
            for (size_t i = 0; i < s; i++)
            {
                v.push_back(rand());
            }
            BinaryNode<int> *node = BinaryNode<int>::SearchTreeRandom(v);
            node->Print2();
            int m = *min_element(v.begin(), v.end());
            BinaryNode<int> *m1 = BinaryNode<int>::Min(node);
            BinaryNode<int> *m2 = BinaryNode<int>::SearchTreeMin(node);
            Logger().WriteInformation("Min = %d, %d, %d\n", m, m1->Value(), m2->Value());
            ASSERT1(m == m1->Value());
            ASSERT1(m == m2->Value());
            BinaryNode<int>::DeleteTree(node);
        };
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        for (int i = 7; i < 50; i++)
        {
            check(i);
        }
    });

    Add("Max1", [&]() {
        auto check = [&](size_t s) {
            vector<int> v;
            for (size_t i = 0; i < s; i++)
            {
                v.push_back(rand());
            }
            BinaryNode<int> *node = BinaryNode<int>::SearchTreeRandom(v);
            node->Print2();
            int m = *max_element(v.begin(), v.end());
            BinaryNode<int> *m1 = BinaryNode<int>::Max(node);
            BinaryNode<int> *m2 = BinaryNode<int>::SearchTreeMax(node);
            Logger().WriteInformation("Max = %d, %d, %d\n", m, m1->Value(), m2->Value());
            ASSERT1(m == m1->Value());
            ASSERT1(m == m2->Value());
            BinaryNode<int>::DeleteTree(node);
        };
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        for (int i = 7; i < 50; i++)
        {
            check(i);
        }
    });

    Add("Successor", [&]() {
        auto check = [&](size_t s) {
            vector<int> v;
            for (size_t i = 0; i < s; i++)
            {
                v.push_back(i);
            }
            BinaryNodeWithParent<int> *node = BinaryNodeWithParent<int>::RandomTree2(v);
            node->Print2();
            for (size_t i = 0; i < s; i++)
            {
                BinaryNodeWithParent<int> *p = (BinaryNodeWithParent<int> *)BinaryNode<int>::SearchTreeSearch2(node, i);
                BinaryNodeWithParent<int> *n = BinaryNodeWithParent<int>::SearchTreeSuccessor(p);
                Logger().WriteInformation("Successor(%d) = %s\n", i, n == nullptr ? "null" : to_string(n->Value()).c_str());
                if (i == s - 1)
                    ASSERT1(n == nullptr);
                else
                    ASSERT1(i + 1 == n->Value());
            }
            BinaryNode<int>::DeleteTree(node);
        };
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        for (int i = 7; i < 50; i++)
        {
            check(i);
        }
    });

    Add("Predecessor", [&]() {
        auto check = [&](size_t s) {
            vector<int> v;
            for (size_t i = 0; i < s; i++)
            {
                v.push_back(i);
            }
            BinaryNodeWithParent<int> *node = BinaryNodeWithParent<int>::RandomTree2(v);
            node->Print2();
            for (size_t i = 0; i < s; i++)
            {
                BinaryNodeWithParent<int> *p = (BinaryNodeWithParent<int> *)BinaryNode<int>::SearchTreeSearch2(node, i);
                BinaryNodeWithParent<int> *n = BinaryNodeWithParent<int>::SearchTreePredecessor(p);
                Logger().WriteInformation("Predecessor(%d) = %s\n", i, n == nullptr ? "null" : to_string(n->Value()).c_str());
                if (i == 0)
                    ASSERT1(n == nullptr);
                else
                    ASSERT1(i - 1 == n->Value());
            }
            BinaryNode<int>::DeleteTree(node);
        };
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        for (int i = 7; i < 50; i++)
        {
            check(i);
        }
    });

    Add("Delete1", [&]() {
        auto check = [&](size_t s) {
            vector<int> v;
            for (size_t i = 0; i < s; i++)
            {
                v.push_back(i);
            }
            BinaryNodeWithParent<int> *node = BinaryNodeWithParent<int>::RandomTree2(v);
            node->Print2();
            for (size_t i = 0; i < s; i++)
            {
                BinaryNodeWithParent<int> *n;
                if (i % 2 == 0)
                    n = (BinaryNodeWithParent<int> *)BinaryNode<int>::SearchTreeMin(node);
                else
                    n = (BinaryNodeWithParent<int> *)BinaryNode<int>::SearchTreeMax(node);
                Logger().WriteInformation("Delete %d\n", n->Value());
                node = BinaryNodeWithParent<int>::SearchTreeDelete(node, n);
                if (node != nullptr)
                    node->Print2();
            }
        };

        check(1);
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        for (int i = 7; i < 50; i++)
        {
            check(i);
        }
    });

    Add("Delete2", [&]() {
        auto check = [&](size_t s) {
            vector<int> v(s);
            generate(v.begin(), v.end(), rand);
            sort(v.begin(), v.end());
            BinaryNodeWithParent<int> *node = BinaryNodeWithParent<int>::RandomTree2(v);
            node->Print2();
            for (size_t i = 0; i < s; i++)
            {
                vector<int>::iterator it = v.begin() + (rand() % v.size());
                BinaryNodeWithParent<int> *n = (BinaryNodeWithParent<int> *)BinaryNode<int>::SearchTreeSearch2(node, *it);
                v.erase(it);
                Logger().WriteInformation("Delete %d\n", n->Value());
                node = BinaryNodeWithParent<int>::SearchTreeDelete(node, n);
                if (node != nullptr)
                    node->Print2();
            }
        };

        check(1);
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        for (int i = 7; i < 50; i++)
        {
            check(i);
        }
    });

    Add("Verify1", [&]() {
        auto check = [&](BinaryNode<int> *n, bool expect) {
            bool r = BinaryNode<int>::SearchTreeVerify(n);
            bool r2 = BinaryNode<int>::SearchTreeVerify2(n);
            bool r3 = BinaryNode<int>::SearchTreeVerify3(n);
            BinaryNode<int>::DeleteTree(n);
            ASSERT1(expect == r);
            ASSERT1(expect == r2);
            ASSERT1(expect == r3);
        };
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(80);
            BinaryNode<int> *n2 = new BinaryNode<int>(70);
            BinaryNode<int> *n3 = new BinaryNode<int>(100);
            n1->Left() = n2;
            n2->Right() = n3;
            n1->Print2();
            check(n1, false);
        }
        {
            Test::BinaryNode<int> *n1 = new Test::BinaryNode<int>(80);
            Test::BinaryNode<int> *n2 = new Test::BinaryNode<int>(80);
            Test::BinaryNode<int> *n3 = new Test::BinaryNode<int>(70);
            n1->Left() = n2;
            n2->Right() = n3;
            n1->Print2();
            check(n1, false);
        }
        {
            Test::BinaryNode<int> *n1 = new Test::BinaryNode<int>(80);
            Test::BinaryNode<int> *n2 = new Test::BinaryNode<int>(80);
            Test::BinaryNode<int> *n3 = new Test::BinaryNode<int>(70);
            n1->Left() = n3;
            n1->Right() = n2;
            n1->Print2();
            check(n1, false);
        }
    });

    Add("Verify2", [&]() {
        auto check = [&](size_t s) {
            vector<int> v(s);
            generate(v.begin(), v.end(), rand);
            sort(v.begin(), v.end());
            BinaryNode<int> *node = BinaryNode<int>::SearchTreeRandom(v);
            node->Print2();
            bool r = BinaryNode<int>::SearchTreeVerify(node);
            bool r2 = BinaryNode<int>::SearchTreeVerify2(node);
            bool r3 = BinaryNode<int>::SearchTreeVerify3(node);
            BinaryNode<int>::DeleteTree(node);
            ASSERT1(true == r);
            ASSERT1(true == r2);
            ASSERT1(true == r3);
        };

        check(1);
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        for (int i = 7; i < 50; i++)
        {
            check(i);
        }
    });

    Add("Verify3", [&]() {
        auto check = [&](size_t s) {
            vector<int> v(s);
            generate(v.begin(), v.end(), rand);
            BinaryNode<int> *node = BinaryNode<int>::RandomTreeFromInOrder(v);
            node->Print2();
            bool r = BinaryNode<int>::SearchTreeVerify(node);
            bool r2 = BinaryNode<int>::SearchTreeVerify2(node);
            bool r3 = BinaryNode<int>::SearchTreeVerify3(node);
            BinaryNode<int>::DeleteTree(node);
            ASSERT1(r == r2);
            ASSERT1(r == r3);
        };

        check(1);
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        for (int i = 7; i < 50; i++)
        {
            check(i);
        }
    });

    Add("MaxSearchTreeInBinaryTree1", [&]() {
        auto check = [&](size_t s) {
            Logger().WriteInformation("Test a binary tree of %d nodes\n", s);
            vector<int> v(s);
            generate(v.begin(), v.end(), rand);
            BinaryNode<int> *node = BinaryNode<int>::RandomTreeFromInOrder(v);
            node->Print2();
            BinaryNodeWithParent<int> *tree = BinaryNodeWithParent<int>::MaxSearchTreeInBinaryTree(node);
            tree->Print2();
            BinaryNodeWithParent<int> *tree2 = BinaryNodeWithParent<int>::MaxSearchTreeInBinaryTree2(node);
            tree2->Print2();
            BinaryNode<int>::DeleteTree(node);
            bool r = BinaryNode<int>::SearchTreeVerify(tree);
            bool r2 = BinaryNode<int>::SearchTreeVerify(tree2);
            int size = BinaryNode<int>::Size(tree);
            int size2 = BinaryNode<int>::Size(tree2);
            BinaryNode<int>::DeleteTree(tree);
            BinaryNode<int>::DeleteTree(tree2);
            ASSERT1(r == true);
            ASSERT1(r2 == true);
            ASSERT1(size == size2);
        };
        check(1);
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        for (int i = 7; i < 50; i++)
        {
            check(i);
        }
    });

    Add("MaxSearchTreeInBinaryTree2", [&]() {
        auto check = [&](BinaryNode<int> *node) {
            node->Print2();
            BinaryNodeWithParent<int> *tree = BinaryNodeWithParent<int>::MaxSearchTreeInBinaryTree(node);
            tree->Print2();
            BinaryNodeWithParent<int> *tree2 = BinaryNodeWithParent<int>::MaxSearchTreeInBinaryTree2(node);
            tree2->Print2();
            BinaryNode<int>::DeleteTree(node);
            bool r = BinaryNode<int>::SearchTreeVerify(tree);
            bool r2 = BinaryNode<int>::SearchTreeVerify(tree2);
            int size = BinaryNode<int>::Size(tree);
            int size2 = BinaryNode<int>::Size(tree2);
            BinaryNode<int>::DeleteTree(tree);
            BinaryNode<int>::DeleteTree(tree2);
            ASSERT1(r == true);
            ASSERT1(r2 == true);
            ASSERT1(size == size2);
        };

        BinaryNode<int> *n0 = new BinaryNode<int>(10);
        BinaryNode<int> *n1 = new BinaryNode<int>(50);
        BinaryNode<int> *n2 = new BinaryNode<int>(5);
        BinaryNode<int> *n3 = new BinaryNode<int>(80);
        BinaryNode<int> *n4 = new BinaryNode<int>(4);
        BinaryNode<int> *n5 = new BinaryNode<int>(6);
        BinaryNode<int> *n6 = new BinaryNode<int>(70);
        BinaryNode<int> *n7 = new BinaryNode<int>(75);
        BinaryNode<int> *n8 = new BinaryNode<int>(3);
        BinaryNode<int> *n9 = new BinaryNode<int>(7);
        BinaryNode<int> *n10 = new BinaryNode<int>(60);
        BinaryNode<int> *n11 = new BinaryNode<int>(75);
        n0->Right() = n1;
        n1->Left() = n2;
        n1->Right() = n3;
        n2->Left() = n4;
        n2->Right() = n5;
        n3->Left() = n6;
        n3->Right() = n7;
        n4->Left() = n8;
        n5->Right() = n9;
        n6->Left() = n10;
        n6->Right() = n11;

        check(n0);
    });

    Add("MaxSearchTreeInBinaryTree3", [&]() {
        auto check = [&](size_t s) {
            Logger().WriteInformation("Test a binary search tree of %d nodes\n", s);
            vector<int> v(s);
            generate(v.begin(), v.end(), rand);
            sort(v.begin(), v.end());
            BinaryNode<int> *node = BinaryNode<int>::RandomTreeFromInOrder(v);
            node->Print2();
            BinaryNodeWithParent<int> *tree = BinaryNodeWithParent<int>::MaxSearchTreeInBinaryTree(node);
            tree->Print2();
            BinaryNodeWithParent<int> *tree2 = BinaryNodeWithParent<int>::MaxSearchTreeInBinaryTree2(node);
            tree2->Print2();
            bool r = BinaryNode<int>::SearchTreeVerify(tree);
            bool r2 = BinaryNode<int>::SearchTreeVerify(tree2);
            int size = BinaryNode<int>::Size(tree);
            int size2 = BinaryNode<int>::Size(tree2);
            int equal = BinaryNode<int>::Compare(node, tree);
            int equal2 = BinaryNode<int>::Compare(node, tree2);
            BinaryNode<int>::DeleteTree(node);
            BinaryNode<int>::DeleteTree(tree);
            BinaryNode<int>::DeleteTree(tree2);
            ASSERT1(r == true);
            ASSERT1(r2 == true);
            ASSERT1(size == size2);
            ASSERT1(equal == 0);
            ASSERT1(equal2 == 0);
        };
        check(1);
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        for (int i = 7; i < 50; i++)
        {
            check(i);
        }
    });

    Add("MaxSubSearchTreeInBinaryTree1", [&]() {
        auto check = [&](size_t s) {
            Logger().WriteInformation("Test a binary tree of %d nodes\n", s);
            vector<int> v(s);
            generate(v.begin(), v.end(), rand);
            BinaryNode<int> *node = BinaryNode<int>::RandomTreeFromInOrder(v);
            node->Print2();
            BinaryNodeWithParent<int> *tree = BinaryNodeWithParent<int>::MaxSubSearchTreeInBinaryTree(node);
            tree->Print2();
            BinaryNodeWithParent<int> *tree2 = BinaryNodeWithParent<int>::MaxSubSearchTreeInBinaryTree2(node);
            tree2->Print2();
            bool r = BinaryNode<int>::SearchTreeVerify(tree);
            bool r2 = BinaryNode<int>::SearchTreeVerify(tree2);
            int size = BinaryNode<int>::Size(tree);
            int size2 = BinaryNode<int>::Size(tree2);
            int equal = BinaryNode<int>::Compare(node, tree);
            int equal2 = BinaryNode<int>::Compare(node, tree2);
            BinaryNode<int>::DeleteTree(node);
            BinaryNode<int>::DeleteTree(tree);
            BinaryNode<int>::DeleteTree(tree2);
            ASSERT1(r == true);
            ASSERT1(r2 == true);
            ASSERT1(size == size2);
            ASSERT1(equal == 0);
            ASSERT1(equal2 == 0);
        };
        check(1);
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        for (int i = 7; i < 50; i++)
        {
            check(i);
        }
    });

    Add("MaxSubSearchTreeInBinaryTree2", [&]() {
        auto check = [&](size_t s) {
            Logger().WriteInformation("Test a binary search tree of %d nodes\n", s);
            vector<int> v(s);
            generate(v.begin(), v.end(), rand);
            sort(v.begin(), v.end());
            BinaryNode<int> *node = BinaryNode<int>::RandomTreeFromInOrder(v);
            node->Print2();
            BinaryNodeWithParent<int> *tree = BinaryNodeWithParent<int>::MaxSubSearchTreeInBinaryTree(node);
            tree->Print2();
            BinaryNodeWithParent<int> *tree2 = BinaryNodeWithParent<int>::MaxSubSearchTreeInBinaryTree2(node);
            tree2->Print2();
            BinaryNode<int>::DeleteTree(node);
            bool r = BinaryNode<int>::SearchTreeVerify(tree);
            bool r2 = BinaryNode<int>::SearchTreeVerify(tree2);
            int size = BinaryNode<int>::Size(tree);
            int size2 = BinaryNode<int>::Size(tree2);
            BinaryNode<int>::DeleteTree(tree);
            BinaryNode<int>::DeleteTree(tree2);
            ASSERT1(r == true);
            ASSERT1(r2 == true);
            ASSERT1(size == size2);
        };
        check(1);
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        for (int i = 7; i < 50; i++)
        {
            check(i);
        }
    });

    Add("SearchTreeSerialize", [&]() {
        auto check = [&](size_t s) {
            Logger().WriteInformation("Test a binary search tree of %d nodes\n", s);
            vector<int> v(s);
            generate(v.begin(), v.end(), rand);
            sort(v.begin(), v.end());
            BinaryNode<int> *node = BinaryNode<int>::RandomTreeFromInOrder(v);
            node->Print2();
            stringstream ss;
            BinaryNode<int>::SearchTreeSerialize(node, ss);
            Logger().WriteInformation("%s\n", ss.str().c_str());
            BinaryNode<int> *node2 = BinaryNode<int>::SearchTreeDeserialize(ss);
            node2->Print2();
            stringstream ss2;
            BinaryNode<int>::SearchTreeSerialize(node, ss2);
            Logger().WriteInformation("%s\n", ss2.str().c_str());
            BinaryNode<int> *node3 = BinaryNode<int>::SearchTreeDeserialize2(ss2);
            node3->Print2();
            stringstream ss3;
            BinaryNode<int>::SearchTreeSerialize(node, ss3);
            Logger().WriteInformation("%s\n", ss3.str().c_str());
            BinaryNode<int> *node4 = BinaryNode<int>::SearchTreeDeserialize3(ss3);
            node4->Print2();
            int equal2 = BinaryNode<int>::Compare(node, node2);
            int equal3 = BinaryNode<int>::Compare(node, node3);
            int equal4 = BinaryNode<int>::Compare(node, node4);
            BinaryNode<int>::DeleteTree(node);
            BinaryNode<int>::DeleteTree(node2);
            BinaryNode<int>::DeleteTree(node3);
            BinaryNode<int>::DeleteTree(node4);
            ASSERT1(equal2 == 0);
            ASSERT1(equal3 == 0);
            ASSERT1(equal4 == 0);
        };
        check(1);
        check(2);
        check(3);
        check(4);
        check(5);
        check(6);
        for (int i = 7; i < 50; i++)
        {
            check(i);
        }
    });

    Add("SearchTreeRecover", [&]() {
        auto check = [&](BinaryNode<int> *node) {
            Logger().WriteInformation("Recover tree\n");
            node->Print2();
            bool valid = BinaryNode<int>::SearchTreeVerify(node);
            bool valid2 = BinaryNode<int>::SearchTreeVerify2(node);
            bool valid3 = BinaryNode<int>::SearchTreeVerify3(node);
            BinaryNode<int> *copy = BinaryNode<int>::Clone1(node);
            copy->Print2();
            Logger().WriteInformation("to\n");
            node = BinaryNode<int>::SearchTreeRecover(node);
            copy = BinaryNode<int>::SearchTreeRecover2(copy);
            node->Print2();
            copy->Print2();
            bool valid4 = BinaryNode<int>::SearchTreeVerify(node);
            bool valid5 = BinaryNode<int>::SearchTreeVerify2(node);
            bool valid6 = BinaryNode<int>::SearchTreeVerify3(node);
            int equal = BinaryNode<int>::Compare(node, copy);
            BinaryNode<int>::DeleteTree(node);
            BinaryNode<int>::DeleteTree(copy);
            ASSERT1(valid == valid2);
            ASSERT1(valid == valid3);
            ASSERT1(valid4 == true);
            ASSERT1(valid5 == true);
            ASSERT1(valid6 == true);
            ASSERT1(equal == 0);
        };
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(1);
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(1);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            n1->Left() = n2;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(2);
            BinaryNode<int> *n2 = new BinaryNode<int>(1);
            n1->Right() = n2;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(1);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            BinaryNode<int> *n3 = new BinaryNode<int>(3);
            n1->Left() = n2;
            n1->Right() = n3;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(3);
            BinaryNode<int> *n2 = new BinaryNode<int>(1);
            BinaryNode<int> *n3 = new BinaryNode<int>(2);
            n1->Left() = n2;
            n1->Right() = n3;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(2);
            BinaryNode<int> *n2 = new BinaryNode<int>(3);
            BinaryNode<int> *n3 = new BinaryNode<int>(1);
            n1->Left() = n2;
            n1->Right() = n3;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(3);
            BinaryNode<int> *n2 = new BinaryNode<int>(1);
            BinaryNode<int> *n3 = new BinaryNode<int>(2);
            n1->Left() = n2;
            n2->Left() = n3;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(2);
            BinaryNode<int> *n2 = new BinaryNode<int>(3);
            BinaryNode<int> *n3 = new BinaryNode<int>(1);
            n1->Left() = n2;
            n2->Left() = n3;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(2);
            BinaryNode<int> *n2 = new BinaryNode<int>(1);
            BinaryNode<int> *n3 = new BinaryNode<int>(3);
            n1->Right() = n2;
            n2->Right() = n3;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(1);
            BinaryNode<int> *n2 = new BinaryNode<int>(3);
            BinaryNode<int> *n3 = new BinaryNode<int>(2);
            n1->Right() = n2;
            n2->Right() = n3;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(4);
            BinaryNode<int> *n2 = new BinaryNode<int>(1);
            BinaryNode<int> *n3 = new BinaryNode<int>(6);
            BinaryNode<int> *n4 = new BinaryNode<int>(2);
            BinaryNode<int> *n5 = new BinaryNode<int>(3);
            BinaryNode<int> *n6 = new BinaryNode<int>(5);
            BinaryNode<int> *n7 = new BinaryNode<int>(7);
            n1->Left() = n2;
            n1->Right() = n3;
            n2->Left() = n4;
            n2->Right() = n5;
            n3->Left() = n6;
            n3->Right() = n7;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(4);
            BinaryNode<int> *n2 = new BinaryNode<int>(3);
            BinaryNode<int> *n3 = new BinaryNode<int>(6);
            BinaryNode<int> *n4 = new BinaryNode<int>(1);
            BinaryNode<int> *n5 = new BinaryNode<int>(2);
            BinaryNode<int> *n6 = new BinaryNode<int>(5);
            BinaryNode<int> *n7 = new BinaryNode<int>(7);
            n1->Left() = n2;
            n1->Right() = n3;
            n2->Left() = n4;
            n2->Right() = n5;
            n3->Left() = n6;
            n3->Right() = n7;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(4);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            BinaryNode<int> *n3 = new BinaryNode<int>(6);
            BinaryNode<int> *n4 = new BinaryNode<int>(3);
            BinaryNode<int> *n5 = new BinaryNode<int>(1);
            BinaryNode<int> *n6 = new BinaryNode<int>(5);
            BinaryNode<int> *n7 = new BinaryNode<int>(7);
            n1->Left() = n2;
            n1->Right() = n3;
            n2->Left() = n4;
            n2->Right() = n5;
            n3->Left() = n6;
            n3->Right() = n7;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(2);
            BinaryNode<int> *n2 = new BinaryNode<int>(4);
            BinaryNode<int> *n3 = new BinaryNode<int>(6);
            BinaryNode<int> *n4 = new BinaryNode<int>(1);
            BinaryNode<int> *n5 = new BinaryNode<int>(3);
            BinaryNode<int> *n6 = new BinaryNode<int>(5);
            BinaryNode<int> *n7 = new BinaryNode<int>(7);
            n1->Left() = n2;
            n1->Right() = n3;
            n2->Left() = n4;
            n2->Right() = n5;
            n3->Left() = n6;
            n3->Right() = n7;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(1);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            BinaryNode<int> *n3 = new BinaryNode<int>(6);
            BinaryNode<int> *n4 = new BinaryNode<int>(4);
            BinaryNode<int> *n5 = new BinaryNode<int>(3);
            BinaryNode<int> *n6 = new BinaryNode<int>(5);
            BinaryNode<int> *n7 = new BinaryNode<int>(7);
            n1->Left() = n2;
            n1->Right() = n3;
            n2->Left() = n4;
            n2->Right() = n5;
            n3->Left() = n6;
            n3->Right() = n7;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(3);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            BinaryNode<int> *n3 = new BinaryNode<int>(6);
            BinaryNode<int> *n4 = new BinaryNode<int>(1);
            BinaryNode<int> *n5 = new BinaryNode<int>(4);
            BinaryNode<int> *n6 = new BinaryNode<int>(5);
            BinaryNode<int> *n7 = new BinaryNode<int>(7);
            n1->Left() = n2;
            n1->Right() = n3;
            n2->Left() = n4;
            n2->Right() = n5;
            n3->Left() = n6;
            n3->Right() = n7;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(4);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            BinaryNode<int> *n3 = new BinaryNode<int>(5);
            BinaryNode<int> *n4 = new BinaryNode<int>(1);
            BinaryNode<int> *n5 = new BinaryNode<int>(3);
            BinaryNode<int> *n6 = new BinaryNode<int>(6);
            BinaryNode<int> *n7 = new BinaryNode<int>(7);
            n1->Left() = n2;
            n1->Right() = n3;
            n2->Left() = n4;
            n2->Right() = n5;
            n3->Left() = n6;
            n3->Right() = n7;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(4);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            BinaryNode<int> *n3 = new BinaryNode<int>(7);
            BinaryNode<int> *n4 = new BinaryNode<int>(1);
            BinaryNode<int> *n5 = new BinaryNode<int>(3);
            BinaryNode<int> *n6 = new BinaryNode<int>(5);
            BinaryNode<int> *n7 = new BinaryNode<int>(6);
            n1->Left() = n2;
            n1->Right() = n3;
            n2->Left() = n4;
            n2->Right() = n5;
            n3->Left() = n6;
            n3->Right() = n7;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(4);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            BinaryNode<int> *n3 = new BinaryNode<int>(6);
            BinaryNode<int> *n4 = new BinaryNode<int>(1);
            BinaryNode<int> *n5 = new BinaryNode<int>(3);
            BinaryNode<int> *n6 = new BinaryNode<int>(7);
            BinaryNode<int> *n7 = new BinaryNode<int>(5);
            n1->Left() = n2;
            n1->Right() = n3;
            n2->Left() = n4;
            n2->Right() = n5;
            n3->Left() = n6;
            n3->Right() = n7;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(6);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            BinaryNode<int> *n3 = new BinaryNode<int>(4);
            BinaryNode<int> *n4 = new BinaryNode<int>(1);
            BinaryNode<int> *n5 = new BinaryNode<int>(3);
            BinaryNode<int> *n6 = new BinaryNode<int>(5);
            BinaryNode<int> *n7 = new BinaryNode<int>(7);
            n1->Left() = n2;
            n1->Right() = n3;
            n2->Left() = n4;
            n2->Right() = n5;
            n3->Left() = n6;
            n3->Right() = n7;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(5);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            BinaryNode<int> *n3 = new BinaryNode<int>(6);
            BinaryNode<int> *n4 = new BinaryNode<int>(1);
            BinaryNode<int> *n5 = new BinaryNode<int>(3);
            BinaryNode<int> *n6 = new BinaryNode<int>(4);
            BinaryNode<int> *n7 = new BinaryNode<int>(7);
            n1->Left() = n2;
            n1->Right() = n3;
            n2->Left() = n4;
            n2->Right() = n5;
            n3->Left() = n6;
            n3->Right() = n7;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(7);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            BinaryNode<int> *n3 = new BinaryNode<int>(6);
            BinaryNode<int> *n4 = new BinaryNode<int>(1);
            BinaryNode<int> *n5 = new BinaryNode<int>(3);
            BinaryNode<int> *n6 = new BinaryNode<int>(5);
            BinaryNode<int> *n7 = new BinaryNode<int>(4);
            n1->Left() = n2;
            n1->Right() = n3;
            n2->Left() = n4;
            n2->Right() = n5;
            n3->Left() = n6;
            n3->Right() = n7;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(4);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            BinaryNode<int> *n3 = new BinaryNode<int>(6);
            BinaryNode<int> *n4 = new BinaryNode<int>(5);
            BinaryNode<int> *n5 = new BinaryNode<int>(3);
            BinaryNode<int> *n6 = new BinaryNode<int>(1);
            BinaryNode<int> *n7 = new BinaryNode<int>(7);
            n1->Left() = n2;
            n1->Right() = n3;
            n2->Left() = n4;
            n2->Right() = n5;
            n3->Left() = n6;
            n3->Right() = n7;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(4);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            BinaryNode<int> *n3 = new BinaryNode<int>(6);
            BinaryNode<int> *n4 = new BinaryNode<int>(1);
            BinaryNode<int> *n5 = new BinaryNode<int>(7);
            BinaryNode<int> *n6 = new BinaryNode<int>(5);
            BinaryNode<int> *n7 = new BinaryNode<int>(3);
            n1->Left() = n2;
            n1->Right() = n3;
            n2->Left() = n4;
            n2->Right() = n5;
            n3->Left() = n6;
            n3->Right() = n7;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(4);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            BinaryNode<int> *n3 = new BinaryNode<int>(6);
            BinaryNode<int> *n4 = new BinaryNode<int>(7);
            BinaryNode<int> *n5 = new BinaryNode<int>(3);
            BinaryNode<int> *n6 = new BinaryNode<int>(5);
            BinaryNode<int> *n7 = new BinaryNode<int>(1);
            n1->Left() = n2;
            n1->Right() = n3;
            n2->Left() = n4;
            n2->Right() = n5;
            n3->Left() = n6;
            n3->Right() = n7;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(4);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            BinaryNode<int> *n3 = new BinaryNode<int>(6);
            BinaryNode<int> *n4 = new BinaryNode<int>(1);
            BinaryNode<int> *n5 = new BinaryNode<int>(5);
            BinaryNode<int> *n6 = new BinaryNode<int>(3);
            BinaryNode<int> *n7 = new BinaryNode<int>(7);
            n1->Left() = n2;
            n1->Right() = n3;
            n2->Left() = n4;
            n2->Right() = n5;
            n3->Left() = n6;
            n3->Right() = n7;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(4);
            BinaryNode<int> *n2 = new BinaryNode<int>(6);
            BinaryNode<int> *n3 = new BinaryNode<int>(2);
            BinaryNode<int> *n4 = new BinaryNode<int>(1);
            BinaryNode<int> *n5 = new BinaryNode<int>(3);
            BinaryNode<int> *n6 = new BinaryNode<int>(5);
            BinaryNode<int> *n7 = new BinaryNode<int>(7);
            n1->Left() = n2;
            n1->Right() = n3;
            n2->Left() = n4;
            n2->Right() = n5;
            n3->Left() = n6;
            n3->Right() = n7;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(4);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            BinaryNode<int> *n3 = new BinaryNode<int>(1);
            BinaryNode<int> *n4 = new BinaryNode<int>(6);
            BinaryNode<int> *n5 = new BinaryNode<int>(3);
            BinaryNode<int> *n6 = new BinaryNode<int>(5);
            BinaryNode<int> *n7 = new BinaryNode<int>(7);
            n1->Left() = n2;
            n1->Right() = n3;
            n2->Left() = n4;
            n2->Right() = n5;
            n3->Left() = n6;
            n3->Right() = n7;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(4);
            BinaryNode<int> *n2 = new BinaryNode<int>(2);
            BinaryNode<int> *n3 = new BinaryNode<int>(3);
            BinaryNode<int> *n4 = new BinaryNode<int>(1);
            BinaryNode<int> *n5 = new BinaryNode<int>(6);
            BinaryNode<int> *n6 = new BinaryNode<int>(5);
            BinaryNode<int> *n7 = new BinaryNode<int>(7);
            n1->Left() = n2;
            n1->Right() = n3;
            n2->Left() = n4;
            n2->Right() = n5;
            n3->Left() = n6;
            n3->Right() = n7;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(4);
            BinaryNode<int> *n2 = new BinaryNode<int>(5);
            BinaryNode<int> *n3 = new BinaryNode<int>(6);
            BinaryNode<int> *n4 = new BinaryNode<int>(1);
            BinaryNode<int> *n5 = new BinaryNode<int>(3);
            BinaryNode<int> *n6 = new BinaryNode<int>(2);
            BinaryNode<int> *n7 = new BinaryNode<int>(7);
            n1->Left() = n2;
            n1->Right() = n3;
            n2->Left() = n4;
            n2->Right() = n5;
            n3->Left() = n6;
            n3->Right() = n7;
            check(n1);
        }
        {
            BinaryNode<int> *n1 = new BinaryNode<int>(4);
            BinaryNode<int> *n2 = new BinaryNode<int>(7);
            BinaryNode<int> *n3 = new BinaryNode<int>(6);
            BinaryNode<int> *n4 = new BinaryNode<int>(1);
            BinaryNode<int> *n5 = new BinaryNode<int>(3);
            BinaryNode<int> *n6 = new BinaryNode<int>(5);
            BinaryNode<int> *n7 = new BinaryNode<int>(2);
            n1->Left() = n2;
            n1->Right() = n3;
            n2->Left() = n4;
            n2->Right() = n5;
            n3->Left() = n6;
            n3->Right() = n7;
            check(n1);
        }
        {
            for (int i = 0; i < 100; i++)
            {
                int size = 1 + (rand() % 100);
                vector<int> v;
                for (int t = 0; t < size; t++)
                    v.push_back(t);
                BinaryNode<int> *node = BinaryNode<int>::RandomTreeFromInOrder(v);
                int j = rand() % size;
                int k = rand() % size;
                if (k == j)
                {
                    if (j == size - 1)
                        k--;
                    else
                        k++;
                }
                BinaryNode<int> *p = BinaryNode<int>::SearchTreeSearch(node, v[j]);
                BinaryNode<int> *q = BinaryNode<int>::SearchTreeSearch(node, v[k]);
                BinaryNode<int>::SwapValues(p, q);
                Logger().WriteInformation("Test a tree of %d nodes\n", size);
                check(node);
            }
        }
    });

    Add("UniqueTreesFromPreOrder1", [&]() {
        auto check = [&](int n, int c) {
            vector<int> v;
            for (int i = 0; i < n; i++)
            {
                v.push_back(i);
            }
            unsigned long long count = BinaryNode<int>::CountUniqueTreesFromPreOrderOfSize(v.size());
            vector<BinaryNode<int> *> trees = BinaryNode<int>::UniqueTreesFromPreOrder(v);
            Logger().WriteInformation("%d numbers can build %d unique binary trees.\n", n, trees.size());
            for_each(trees.begin(), trees.end(), [&](BinaryNode<int> *t) {
                t->Print2();
                vector<int> u;
                auto f = [&](int w) { u.push_back(w); };
                BinaryNode<int>::PreOrderWalk(t, f);
                BinaryNode<int>::DeleteTree(t);
                ASSERT1(v.size() == u.size());
                for (size_t i = 0; i < v.size(); i++)
                {
                    ASSERT1(v[i] == u[i]);
                }
            });
            ASSERT1((int)trees.size() == c);
            ASSERT1(count == c);
        };

        check(1, 1);
        check(2, 2);
        check(3, 5);
        check(4, 14);
    });

    Add("UniqueTreesFromPreOrder2", [&]() {
        auto check = [&](int n) {
            vector<int> v(n);
            generate(v.begin(), v.end(), rand);
            unsigned long long count = BinaryNode<int>::CountUniqueTreesFromPreOrderOfSize(v.size());
            vector<BinaryNode<int> *> trees = BinaryNode<int>::UniqueTreesFromPreOrder(v);
            Logger().WriteInformation("%d numbers can build %d unique binary trees.\n", n, trees.size());
            for_each(trees.begin(), trees.end(), [&](BinaryNode<int> *t) {
                t->Print2();
                vector<int> u;
                auto f = [&](int w) { u.push_back(w); };
                BinaryNode<int>::PreOrderWalk(t, f);
                BinaryNode<int>::DeleteTree(t);
                ASSERT1(v.size() == u.size());
                for (size_t i = 0; i < v.size(); i++)
                {
                    ASSERT1(v[i] == u[i]);
                }
            });
            ASSERT1(count == trees.size());
        };

        for (int i = 1; i < 9; i++)
        {
            check(i);
        }
    });

    Add("UniqueTreesFromInOrder1", [&]() {
        auto check = [&](int n, int c) {
            vector<int> v;
            for (int i = 0; i < n; i++)
            {
                v.push_back(i);
            }
            unsigned long long count = BinaryNode<int>::CountUniqueTreesFromInOrderOfSize(v.size());
            vector<BinaryNode<int> *> trees = BinaryNode<int>::UniqueTreesFromInOrder(v);
            Logger().WriteInformation("%d numbers can build %d unique binary trees.\n", n, trees.size());
            for_each(trees.begin(), trees.end(), [&](BinaryNode<int> *t) {
                t->Print2();
                vector<int> u;
                auto f = [&](int w) { u.push_back(w); };
                BinaryNode<int>::InOrderWalk(t, f);
                BinaryNode<int>::DeleteTree(t);
                ASSERT1(v.size() == u.size());
                for (size_t i = 0; i < v.size(); i++)
                {
                    ASSERT1(v[i] == u[i]);
                }
            });
            ASSERT1((int)trees.size() == c);
            ASSERT1(count == c);
        };

        check(1, 1);
        check(2, 2);
        check(3, 5);
        check(4, 14);
    });

    Add("UniqueTreesFromInOrder2", [&]() {
        auto check = [&](int n) {
            vector<int> v(n);
            generate(v.begin(), v.end(), rand);
            unsigned long long count = BinaryNode<int>::CountUniqueTreesFromInOrderOfSize(v.size());
            vector<BinaryNode<int> *> trees = BinaryNode<int>::UniqueTreesFromInOrder(v);
            Logger().WriteInformation("%d numbers can build %d unique binary trees.\n", n, trees.size());
            for_each(trees.begin(), trees.end(), [&](BinaryNode<int> *t) {
                t->Print2();
                vector<int> u;
                auto f = [&](int w) { u.push_back(w); };
                BinaryNode<int>::InOrderWalk(t, f);
                BinaryNode<int>::DeleteTree(t);
                ASSERT1(v.size() == u.size());
                for (size_t i = 0; i < v.size(); i++)
                {
                    ASSERT1(v[i] == u[i]);
                }
            });
            ASSERT1(count == trees.size());
        };

        for (int i = 1; i < 9; i++)
        {
            check(i);
        }
    });

    Add("UniqueTreesFromPostOrder1", [&]() {
        auto check = [&](int n, int c) {
            vector<int> v;
            for (int i = 0; i < n; i++)
            {
                v.push_back(i);
            }
            unsigned long long count = BinaryNode<int>::CountUniqueTreesFromPostOrderOfSize(v.size());
            vector<BinaryNode<int> *> trees = BinaryNode<int>::UniqueTreesFromPostOrder(v);
            Logger().WriteInformation("%d numbers can build %d unique binary trees.\n", n, trees.size());
            for_each(trees.begin(), trees.end(), [&](BinaryNode<int> *t) {
                t->Print2();
                vector<int> u;
                auto f = [&](int w) { u.push_back(w); };
                BinaryNode<int>::PostOrderWalk(t, f);
                BinaryNode<int>::DeleteTree(t);
                ASSERT1(v.size() == u.size());
                for (size_t i = 0; i < v.size(); i++)
                {
                    ASSERT1(v[i] == u[i]);
                }
            });
            ASSERT1((int)trees.size() == c);
            ASSERT1(count == c);
        };

        check(1, 1);
        check(2, 2);
        check(3, 5);
        check(4, 14);
    });

    Add("UniqueTreesFromPostOrder2", [&]() {
        auto check = [&](int n) {
            vector<int> v(n);
            generate(v.begin(), v.end(), rand);
            unsigned long long count = BinaryNode<int>::CountUniqueTreesFromPostOrderOfSize(v.size());
            vector<BinaryNode<int> *> trees = BinaryNode<int>::UniqueTreesFromPostOrder(v);
            Logger().WriteInformation("%d numbers can build %d unique binary trees.\n", n, trees.size());
            for_each(trees.begin(), trees.end(), [&](BinaryNode<int> *t) {
                t->Print2();
                vector<int> u;
                auto f = [&](int w) { u.push_back(w); };
                BinaryNode<int>::PostOrderWalk(t, f);
                BinaryNode<int>::DeleteTree(t);
                ASSERT1(v.size() == u.size());
                for (size_t i = 0; i < v.size(); i++)
                {
                    ASSERT1(v[i] == u[i]);
                }
            });
            ASSERT1(count == trees.size());
        };

        for (int i = 1; i < 9; i++)
        {
            check(i);
        }
    });

    Add("CountUniqueTrees", [&]() {
        auto check = [&](int n) {
            unsigned long long count1 = BinaryNode<int>::CountUniqueTreesFromPreOrderOfSize(n);
            unsigned long long count2 = BinaryNode<int>::CountUniqueTreesFromInOrderOfSize(n);
            unsigned long long count3 = BinaryNode<int>::CountUniqueTreesFromPostOrderOfSize(n);
            Logger().WriteInformation("%d\t%llu\t%llu\t%llu\n", n, count1, count2, count3);
        };
        for (int i = 1; i <= 20; i++)
        {
            check(i);
        }
    });

    Add("Constructor", [&]() {
        Test::BinaryNode<int> node(3);
        Test::BinaryIterator<int, Test::BinaryNode> it(&node);
        Logger().WriteInformation("it.Current() = %d\n", it.Current());
        Logger().WriteInformation("it->Value() = %d\n", it->Value());
        Logger().WriteInformation("*it = %d\n", *it);

        Test::BinaryIterator<int, Test::BinaryNode> it2(it);
        Logger().WriteInformation("it2.Current() = %d\n", it2.Current());
        Logger().WriteInformation("it2->Value() = %d\n", it2->Value());
        Logger().WriteInformation("*it2 = %d\n", *it2);

        ASSERT1(it.Current() == it2.Current());
        ASSERT1(it->Value() == it2->Value());
        ASSERT1(*it == it2.Current());
        ASSERT1(*it == it2->Value());
        ASSERT1(*it == *it2);

        ASSERT1(it);
        ASSERT1(it2);
    });
}

#endif