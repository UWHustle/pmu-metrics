#include <iostream>
#include <cstdlib>

#ifndef _METRICS_H_
#define _METRICS_H_

#include "config.h"

/***********************************************************
* Flag to enable collection of hardware metrics.
* Make sure the setup script has been run successfully
* before enabling this flag.
***********************************************************/
#define _COLLECT_PMU_METRICS_ 1

typedef struct Metrics {
	int n; // number of metrics being measured
    unsigned long *metrics;
    unsigned long *pmu_ids;
} Metrics;

/***********************************************************
* Function to read HW counters
***********************************************************/

unsigned long _rdpmc(unsigned long pmc_id);

/************************************************************
* USAGE - To collect metrics for a particular section of code,
* wrap it with getMetricsStart() and getMetricsEnd()

<...code...>

Metrics m;
initMetrics(m);
getMetricsStart(m);
<...
code snippet to monitor
...>
getMetricsEnd(m);

<...code...>

************************************************************/

void initMetrics(Metrics&);
void getMetricsStart(Metrics&);
void getMetricsEnd(Metrics&);
// void printMetrics(Metrics&);

#endif // _METRICS_H_
