all: 1-original 2-original 3-original 4-original 5-original 1-new 2-new 3-new 4-new 5-new

CXX       = clang++
CXXFLAGS  = -g -std=c++17 -Wall

1-new: 1-pythagoras-new.cpp
	$(CXX) 1-pythagoras-new.cpp -o 1-new $(CXXFLAGS)

1-original: 1-pythagoras-original.cpp
	$(CXX) 1-pythagoras-original.cpp -o 1-original $(CXXFLAGS)

2-new: 2-root_of_quadratic_function-new.cpp
	$(CXX) 2-root_of_quadratic_function-new.cpp -o 2-new $(CXXFLAGS)

2-original: 2-root_of_quadratic_function-original.cpp
	$(CXX) 2-root_of_quadratic_function-original.cpp -o 2-original $(CXXFLAGS)

3-new: 3-median_t-new.cpp
	$(CXX) 3-median_t-new.cpp -o 3-new $(CXXFLAGS)

3-original: 3-median_t-original.cpp
	$(CXX) 3-median_t-original.cpp -o 3-original $(CXXFLAGS)

4-new: 4-triangle_circumradius-new.cpp
	$(CXX) 4-triangle_circumradius-new.cpp -o 4-new $(CXXFLAGS)

4-original: 4-triangle_circumradius-original.cpp
	$(CXX) 4-triangle_circumradius-original.cpp -o 4-original $(CXXFLAGS)

5-new: 5-circumcenter_innercenter_distance-new.cpp
	$(CXX) 5-circumcenter_innercenter_distance-new.cpp -o 5-new $(CXXFLAGS)

5-original: 5-circumcenter_innercenter_distance-original.cpp
	$(CXX) 5-circumcenter_innercenter_distance-original.cpp -o 5-original $(CXXFLAGS)

.PHONY: clean 

clean:
	-rm -f 1-original 2-original 3-original 4-original 5-original 1-new 2-new 3-new 4-new 5-new


