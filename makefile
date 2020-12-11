CXX = g++
CXXFLAGS = -Wall -g
program: main.o TimedSorter.o
	$(CXX) $(CXXFLAGS) -o program main.o TimedSorter.o
main.o: main.cpp TimedSorter.cpp TimedSorter.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp
TimedSorter.o: TimedSorter.hpp
clean:
	rm *.o program
