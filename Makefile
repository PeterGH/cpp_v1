CXXFLAGS = -g -Wall -Wno-unused-function -Wno-comment
DEPS = LeetCode.h LeetCode0.h LeetCode1.h LeetCode2.h LeetCode3.h LeetCode4.h LeetCode6.h LeetCode7.h Log.h Test.h Util.h ArgumentTest.h CppTest.h LeetCodeTest.h LeetCodeTest0.h LeetCodeTest1.h LeetCodeTest2.h LeetCodeTest3.h LeetCodeTest4.h LeetCodeTest6.h LeetCodeTest7.h LogTest.h
OBJS = main.o
TARGET = test

$(TARGET) : $(OBJS) $(DEPS)
	$(CXX) -o $(TARGET) $(OBJS)

all : $(TARGET)

clean :
	rm -f $(OBJS) $(TARGET)