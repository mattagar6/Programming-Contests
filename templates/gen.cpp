#include <bits/stdc++.h>
using namespace std;

mt19937 rng;
//$ mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rand(int a, int b) {
	return a + rng() % (b - a + 1);
}


int main(int argc, char *argv[]) {
	
	rng.seed(atoi(argv[1]));
	
	return 0;
}
