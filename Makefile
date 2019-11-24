CXXFLAGS = -g -Wall -Wno-unused-function -Wno-comment
DEPS = Argument.h LeetCode.h Log.h Test.h Util.h ArgumentTest.h LeetCodeTest.h LogTest.h
OBJS = main.o
TARGET = test

$(TARGET) : $(OBJS) $(DEPS)
	$(CXX) -o $(TARGET) $(OBJS)

all : $(TARGET)

clean :
	rm -f $(OBJS) $(TARGET)