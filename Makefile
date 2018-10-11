CXXFLAGS = -g -Wall
OBJS = main.o
TARGET = test

$(TARGET) : $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

all : $(TARGET)

clean :
	rm -f $(OBJS) $(TARGET)