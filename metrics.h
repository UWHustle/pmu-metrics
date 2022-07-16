#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>

#ifndef _METRICS_H_
#define _METRICS_H_

#include "config.h"
#include "perf_events_names.h"

/***********************************************************
* Flag to enable collection of hardware metrics.
* Make sure the setup script has been run successfully
* before enabling this flag.
***********************************************************/
#define _COLLECT_PMU_METRICS_ 1

typedef struct Metrics {
	Metrics();

	/* Measure time elapsed */
	struct timespec startTime;
    struct timespec endTime;
    ulong timeElapsedns;

	int n; // number of metrics being measured
    unsigned long *metrics;
    static unsigned long *pmu_ids;
    static unsigned long *event_ids;
} Metrics;

/***********************************************************
* Function to read HW counters
***********************************************************/

unsigned long _rdpmc(unsigned long pmc_id);
unsigned long getTimeDiff(struct timespec, struct  timespec);

/************************************************************
* USAGE - To collect metrics for a particular section of code,
* wrap it with getMetricsStart() and getMetricsEnd()

<...code...>

Metrics m;
getMetricsStart(m);
<...
code snippet to monitor
...>
getMetricsEnd(m);

<...code...>

************************************************************/

void getMetricsStart(Metrics&);
void getMetricsEnd(Metrics&);
void printMetrics(Metrics&);

#endif // _METRICS_H_
