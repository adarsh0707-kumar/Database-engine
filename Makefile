CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRC = src/main.cpp src/parser.cpp src/executor.cpp src/storage.cpp

TARGET = db

all:
	$(CXX) $(SRC) $(CXXFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)