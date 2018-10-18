CXXFLAGS = -g -Wall
DEPS = Argument.h Log.h Test.h ArgumentTest.h LogTest.h
OBJS = main.o
TARGET = test

$(TARGET) : $(OBJS) $(DEPS)
	$(CXX) -o $(TARGET) $(OBJS)

all : $(TARGET)

clean :
	rm -f $(OBJS) $(TARGET)