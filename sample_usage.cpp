#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

#include "metrics.h"

#define N 1000000 // 1M

using namespace std;

int main() {
	vector<int> vect(N);
	Metrics m;

	// Initialize the array with random numbers
	for (int i=0; i<N; i++) {
		vect[i] = rand();
	}

	// Sort the elements, measure metrics
	getMetricsStart(m);
	sort(vect.begin(), vect.end());
	getMetricsEnd(m);
	return 0;
}