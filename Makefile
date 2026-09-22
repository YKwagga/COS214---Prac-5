CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic
TARGET = campusguard
SOURCES = $(wildcard *.cpp)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	-del /Q $(TARGET).exe $(TARGET) 2>NUL || exit 0

.PHONY: clean
