CXX      = g++
CXXFLAGS = -std=c++11 -g -O0 -Wall -Wextra -pedantic

TARGET  = campusguard
SOURCES = $(filter-out test.cpp,$(wildcard *.cpp))
OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean