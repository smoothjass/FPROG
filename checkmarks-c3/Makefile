all: clean c3-1 c3-2 c3-3 c3-4 c3-5

CXX       = clang++
CXXFLAGS  = -g -std=c++17 -Wall

c3-1: c3-1.cpp
	$(CXX) c3-1.cpp -o 1 $(CXXFLAGS)

c3-2: c3-2.cpp
	$(CXX) c3-2.cpp -o 2 $(CXXFLAGS)

c3-3: c3-3.cpp
	$(CXX) c3-3.cpp -o 3 $(CXXFLAGS)

c3-4: c3-4.cpp
	$(CXX) c3-4.cpp -o 4 $(CXXFLAGS)

c3-5: c3-5.cpp
	$(CXX) c3-5.cpp -o 5 $(CXXFLAGS)

.PHONY: clean 

clean:
	-rm -f 1 2 3 4 5