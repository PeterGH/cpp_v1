CXXFLAGS = -g -Wall -Wno-unused-function -Wno-comment
DEPS = Argument.h LeetCode.h LeetCode0.h LeetCode2.h Log.h Test.h Util.h ArgumentTest.h CppTest.h LeetCodeTest.h LogTest.h
OBJS = main.o
TARGET = test

$(TARGET) : $(OBJS) $(DEPS)
	$(CXX) -o $(TARGET) $(OBJS)

all : $(TARGET)

clean :
	rm -f $(OBJS) $(TARGET)