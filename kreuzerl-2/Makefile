all: 1 2 3 4 5

CXX       = clang++
CXXFLAGS  = -g -std=c++17 -Wall

test: test.cpp
	$(CXX) test.cpp -o test $(CXXFLAGS)

1: pythagoras.cpp
	$(CXX) pythagoras.cpp -o 1 $(CXXFLAGS)

2: root_of_quadratic_function.cpp
	$(CXX) root_of_quadratic_function.cpp -o 2 $(CXXFLAGS)

3: median_t.cpp
	$(CXX) median_t.cpp -o 3 $(CXXFLAGS)

4: triangle_circumradius.cpp
	$(CXX) triangle_circumradius.cpp -o 4 $(CXXFLAGS)

5: circumcenter_innercenter_distance.cpp
	$(CXX) circumcenter_innercenter_distance.cpp -o 5 $(CXXFLAGS)

.PHONY: clean 

clean:
	-rm -f 1 2 3 4 5 test


