#ifndef _BITSETTEST_H_
#define _BITSETTEST_H_

#include "BitSet.h"
#include "Test.h"

using namespace Test;

class BitSetTest : public TestClass
{
  public:
    BitSetTest(Log &log) : TestClass(log) {}
    ~BitSetTest(void) {}
    void Init(void);
};

void BitSetTest::Init(void)
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
		ASSERT2(m.Count() == 2, String::Format("Count = [%d]", m.Count())); m.Set(23);
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
			for (int i = 1; i < 32; i++) {
				ASSERT1(!m.Test(i));
			}

			m.LeftShift(31);
			Logger().WriteInformation("%s\n", m.ToString().c_str());
			for (int i = 0; i < 31; i++) {
				ASSERT1(!m.Test(i));
			}
			ASSERT1(m.Test(31));

			m.LeftShift(1);
			Logger().WriteInformation("%s\n", m.ToString().c_str());
			for (int i = 0; i < 32; i++) {
				ASSERT1(!m.Test(i));
			}
		}
		{
			Logger().WriteInformation("\n");
			BitSet m(32);
			m.Set();
			Logger().WriteInformation("%s\n", m.ToString().c_str());
			for (int i = 0; i < 32; i++) {
				ASSERT1(m.Test(i));
			}

			m.LeftShift(3);
			ASSERT1(!m.Test(0));
			ASSERT1(!m.Test(1));
			ASSERT1(!m.Test(2));
			Logger().WriteInformation("%s\n", m.ToString().c_str());
			for (int i = 3; i < 32; i++) {
				ASSERT1(m.Test(i));
			}

			m.LeftShift(10);
			Logger().WriteInformation("%s\n", m.ToString().c_str());
			for (int i = 0; i < 13; i++) {
				ASSERT1(!m.Test(i));
			}
			for (int i = 13; i < 32; i++) {
				ASSERT1(m.Test(i));
			}
		}
		{
			Logger().WriteInformation("\n");
			BitSet m(32);
			m.Set();
			Logger().WriteInformation("%s\n", m.ToString().c_str());
			for (int i = 0; i < 32; i++) {
				ASSERT1(m.Test(i));
			}

			m.LeftShift(31);
			Logger().WriteInformation("%s\n", m.ToString().c_str());
			for (int i = 0; i < 31; i++) {
				ASSERT1(!m.Test(i));
			}
			ASSERT1(m.Test(31));

			m.LeftShift(1);
			Logger().WriteInformation("%s\n", m.ToString().c_str());
			for (int i = 0; i < 32; i++) {
				ASSERT1(!m.Test(i));
			}
		}
		{
			Logger().WriteInformation("\n");
			BitSet m(33);
			m.Set(0);
			Logger().WriteInformation("%s\n", m.ToString().c_str());
			ASSERT1(m.Test(0));
			for (int i = 1; i < 33; i++) {
				ASSERT1(!m.Test(i));
			}

			m.LeftShift(32);
			Logger().WriteInformation("%s\n", m.ToString().c_str());
			for (int i = 0; i < 32; i++) {
				ASSERT1(!m.Test(i));
			}
			ASSERT1(m.Test(32));

			m.LeftShift(1);
			Logger().WriteInformation("%s\n", m.ToString().c_str());
			for (int i = 0; i < 33; i++) {
				ASSERT1(!m.Test(i));
			}
		}
		{
			Logger().WriteInformation("\n");
			BitSet m(33);
			m.Set();
			Logger().WriteInformation("%s\n", m.ToString().c_str());
			for (int i = 0; i < 33; i++) {
				ASSERT1(m.Test(i));
			}

			m.LeftShift(20);
			Logger().WriteInformation("%s\n", m.ToString().c_str());
			for (int i = 0; i < 20; i++) {
				ASSERT1(!m.Test(i));
			}
			for (int i = 20; i < 32; i++) {
				ASSERT1(m.Test(i));
			}

			m.LeftShift(10);
			Logger().WriteInformation("%s\n", m.ToString().c_str());
			for (int i = 0; i < 30; i++) {
				ASSERT1(!m.Test(i));
			}
			for (int i = 30; i < 32; i++) {
				ASSERT1(m.Test(i));
			}
		}
		{
			Logger().WriteInformation("\n");
			BitSet m(33);
			m.Set();
			Logger().WriteInformation("%s\n", m.ToString().c_str());
			for (int i = 0; i < 33; i++) {
				ASSERT1(m.Test(i));
			}

			m.LeftShift(32);
			Logger().WriteInformation("%s\n", m.ToString().c_str());
			for (int i = 0; i < 32; i++) {
				ASSERT1(!m.Test(i));
			}
			ASSERT1(m.Test(32));

			m.LeftShift(1);
			Logger().WriteInformation("%s\n", m.ToString().c_str());
			for (int i = 0; i < 33; i++) {
				ASSERT1(!m.Test(i));
			}
		}
		{
			Logger().WriteInformation("\n");
			BitSet m(66);
			m.Set();
			Logger().WriteInformation("%s\n", m.ToString().c_str());
			for (int i = 0; i < 66; i++) {
				ASSERT1(m.Test(i));
			}

			m.LeftShift(33);
			Logger().WriteInformation("%s\n", m.ToString().c_str());
			for (int i = 0; i < 33; i++) {
				ASSERT1(!m.Test(i));
			}
			for (int i = 33; i < 66; i++) {
				ASSERT1(m.Test(i));
			}

			m.LeftShift(33);
			Logger().WriteInformation("%s\n", m.ToString().c_str());
			for (int i = 0; i < 66; i++) {
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
			for (int i = 0; i < 31; i++) {
				ASSERT1(!m.Test(i));
			}
			ASSERT1(m.Test(31));

			m.Reverse();
			Logger().WriteInformation("%s\n", m.ToString().c_str());
			for (int i = 1; i < 32; i++) {
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
			for (int i = 0; i < 31; i++) {
				ASSERT1(!m.Test(i));
			}
			ASSERT1(m.Test(31));
			ASSERT1(m.Test(32));

			m.Reverse();
			Logger().WriteInformation("%s\n", m.ToString().c_str());
			for (int i = 2; i < 32; i++) {
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
			for (int i = 0; i < 31; i++) {
				ASSERT1(!m.Test(i));
			}
			ASSERT1(m.Test(31));
			for (int i = 32; i < 63; i++) {
				ASSERT1(!m.Test(i));
			}
			ASSERT1(m.Test(63));

			m.Reverse();
			Logger().WriteInformation("%s\n", m.ToString().c_str());
			for (int i = 1; i < 32; i++) {
				ASSERT1(!m.Test(i));
			}
			ASSERT1(m.Test(0));
			for (int i = 33; i < 64; i++) {
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
			for (int i = 0; i < 31; i++) {
				ASSERT1(!m.Test(i));
			}
			ASSERT1(m.Test(31));
			for (int i = 32; i < 63; i++) {
				ASSERT1(!m.Test(i));
			}
			ASSERT1(m.Test(63));
			ASSERT1(m.Test(64));

			m.Reverse();
			Logger().WriteInformation("%s\n", m.ToString().c_str());
			for (int i = 2; i < 33; i++) {
				ASSERT1(!m.Test(i));
			}
			ASSERT1(m.Test(0));
			ASSERT1(m.Test(1));
			for (int i = 34; i < 65; i++) {
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
			for (int i = 0; i < 31; i++) {
				ASSERT1(!m.Test(i));
			}
			ASSERT1(m.Test(31));
			for (int i = 32; i < 63; i++) {
				ASSERT1(!m.Test(i));
			}
			ASSERT1(m.Test(63));
			for (int i = 64; i < 95; i++) {
				ASSERT1(!m.Test(i));
			}
			ASSERT1(m.Test(95));

			m.Reverse();
			Logger().WriteInformation("%s\n", m.ToString().c_str());
			for (int i = 1; i < 32; i++) {
				ASSERT1(!m.Test(i));
			}
			ASSERT1(m.Test(0));
			for (int i = 33; i < 64; i++) {
				ASSERT1(!m.Test(i));
			}
			ASSERT1(m.Test(32));
			for (int i = 65; i < 96; i++) {
				ASSERT1(!m.Test(i));
			}
			ASSERT1(m.Test(64));
		}
	});

	Add("IsPower2", [&]() {
		BitSet m(100);
		for (int i = 0; i < 100; i++) {
			if (i > 0) m.Reset(i - 1);
			m.Set(i);
			Logger().WriteInformation("%s\n", m.ToString().c_str());
			ASSERT1(m.IsPower2());
		}
	});
}

#endif