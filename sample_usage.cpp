/******************************************************************
* Sample usage of the pmu-metrics library.
* IMPORTANT: Remember to taskset to the programmed core as follows:

node:~> taskset -c 1 ./benchmark.out
*******************************************************************/

#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>

#include "metrics.h"
#include "n.h"

using namespace std;

unsigned long getTimeDiff(struct timespec start_time, struct timespec end_time) {
    return (unsigned long)((end_time.tv_sec - start_time.tv_sec)*1000000 +
        double(end_time.tv_nsec - start_time.tv_nsec)/1000);
    return 0;
}

int main() {
	struct timespec start_time, end_time;
	clock_gettime(CLOCK_MONOTONIC, &start_time);
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
	clock_gettime(CLOCK_MONOTONIC, &end_time);
	cout << getTimeDiff(start_time, end_time) << endl;
	return 0;
}
