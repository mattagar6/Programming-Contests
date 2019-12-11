sol: sol.cpp
	g++ -std=c++14 -Wall -O2 sol.cpp -o sol.out

test: gen.cpp brute.cpp
	g++ -std=c++14 -Wall -O2 gen.cpp -o gen.out
	g++ -std=c++14 -Wall -O2 brute.cpp -o brute.out

clean:
	rm *.out
	
