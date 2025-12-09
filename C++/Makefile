CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall

TARGET = LR6
SRCS   = LR6.cpp 1.cpp 2.cpp 3.cpp 4.cpp
OBJS   = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

1.o: 1.h
2.o: 2.h
3.o: 3.h
4.o: 4.h
LR6.o: 1.h 2.h 3.h 4.h
 
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
