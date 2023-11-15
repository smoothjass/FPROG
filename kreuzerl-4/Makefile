all: sort

.outputFolder:
	mkdir -p out
	
sort: .outputFolder
	clang -std=c++17 -lstdc++ -lm sorting.cpp -Wall -Wextra -Werror -o out/sorting
	./out/sorting