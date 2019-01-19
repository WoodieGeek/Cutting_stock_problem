ex: link
	./.run
link: test matrix
	g++ -o .run .test .matrix -std=c++17
test: 
	g++ test.cpp -c -std=c++17 -o .test
matrix: ../matrix.cpp ../matrix.h 
	g++ ../matrix.cpp -c -std=c++17 -o .matrix
