#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>

#ifndef _METRICS_H_
#define _METRICS_H_

/***********************************************************
* Flag to enable collection of hardware metrics.
* Make sure the setup script has been run successfully
* before enabling this flag.
***********************************************************/

#define _COLLECT_PMU_METRICS_ 1
#define _IS_SKYLAKE_ 1

typedef struct Metrics {
    struct timespec startTime;
    struct timespec endTime;
    unsigned long timeElapsedus;
    unsigned long retiredInst;
    unsigned long coreCycles;
    unsigned long l3Miss;
    unsigned long l2Miss;
    unsigned long l1Miss;
} Metrics;


/***********************************************************
* Functions to read HW counters
***********************************************************/

unsigned long getTimeDiff(struct timespec, struct  timespec);
unsigned long rdpmc_retired_inst_all();
unsigned long rdpmc_core_cycles();
unsigned long rdpmc_tsc_reference_cyles();
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
