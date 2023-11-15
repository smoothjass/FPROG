all: c4

.outputFolder:
	mkdir -p out
	
c4: .outputFolder
	g++-10 -std=c++20 -lstdc++ -lm c4.cpp  -Wextra  -o out/c4
	./out/c4