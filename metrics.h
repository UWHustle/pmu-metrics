#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>

#ifndef _METRICS_H_
#define _METRICS_H_

/***********************************************************
* Flag to enable collection of hardware metrics.
* Make sure the PMU registers have been initialized, and the
* rdpmc instruction is enabled for user-level programs
* before initializing this flag.
***********************************************************/

#define _COLLECT_PMU_METRICS_ 0

typedef struct Metrics {
    struct timespec startTime;
    struct timespec endTime;
    unsigned long timeElapsedus;
    unsigned long retiredInst;
    unsigned long l3Miss;
    unsigned long l2Miss;
    unsigned long l1Miss;
} Metrics;


/***********************************************************
* Functions to read HW counters
***********************************************************/

unsigned long getTimeDiff(struct timespec, struct  timespec);
unsigned long rdpmc_retired_inst_all();
unsigned long rdpmc_llc_cache_misses();
unsigned long rdpmc_l2_cache_misses();
unsigned long rdpmc_l2_cache_refs();


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
printMetrics(m);
<...code...>

************************************************************/

void getMetricsStart(Metrics&);
void getMetricsEnd(Metrics&);
void printMetrics(Metrics&);

#endif // _METRICS_H_
