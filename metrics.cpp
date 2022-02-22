#include "metrics.h"

unsigned long getTimeDiff(struct timespec start_time, struct timespec end_time) {
    return (unsigned long)((end_time.tv_sec - start_time.tv_sec)*1000000 +
        double(end_time.tv_nsec - start_time.tv_nsec)/1000);
    return 0;
}

// Total number of instructions executed (retired)
unsigned long rdpmc_retired_inst_all() {
#if _COLLECT_PMU_METRICS_
    unsigned long a, d, c;
    c = (1<<30);
    __asm__ __volatile__("rdpmc" : "=a" (a), "=d" (d) : "c" (c));
    return ((unsigned long)a) | (((unsigned long)d) << 32);
#else
    return 0;
#endif
}

// Total number of core cycles
// Note that when CPU frequency scaling is enabled (default), time elapsed 
// does not scale linearly with core cycles.
unsigned long rdpmc_core_cycles() {
#if _COLLECT_PMU_METRICS_
    unsigned long a, d, c;
    c = (1<<30) + 1;
    __asm__ __volatile__("rdpmc" : "=a" (a), "=d" (d) : "c" (c));
    return ((unsigned long)a) | (((unsigned long)d) << 32);
#else
    return 0;
#endif
}

// Counts cycles at the same rate as the system's time stamp counter (TSC).
// Reference cycles are unaffected by CPU frequency scaling.
unsigned long rdpmc_tsc_reference_cyles() {
#if _COLLECT_PMU_METRICS_
    unsigned long a, d, c;
    c = (1<<30) + 2;
    __asm__ __volatile__("rdpmc" : "=a" (a), "=d" (d) : "c" (c));
    return ((unsigned long)a) | (((unsigned long)d) << 32);
#else
    return 0;
#endif
}

// This gives L3 cache misses
unsigned long rdpmc_llc_cache_misses() {
#if _COLLECT_PMU_METRICS_
    // LONGEST_LAT_CACHE.MISS
    // mask:event = 0x43412e in 0x186
    unsigned long a, d, c;
    c = 0;
    __asm__ __volatile__("rdpmc" : "=a" (a), "=d" (d) : "c" (c));
    return ((unsigned long)a) | (((unsigned long)d) << 32);
#else
    return 0;
#endif
}

// This gives L2 cache references
// These are basically L1 misses
unsigned long rdpmc_l2_cache_refs() {
#if _COLLECT_PMU_METRICS_ && _IS_SKYLAKE_
    // L2_RQSTS.REFERENCES
    // mask:event = 0x43ef24 in 0x187
    unsigned long a, d, c;
    c = 1;
    __asm__ __volatile__("rdpmc" : "=a" (a), "=d" (d) : "c" (c));
    return ((unsigned long)a) | (((unsigned long)d) << 32);
#else
    return 0;
#endif
}

// This gives L2 cache misses
unsigned long rdpmc_l2_cache_misses() {
#if _COLLECT_PMU_METRICS_ && _IS_SKYLAKE_
    // L2_RQSTS.MISS
    // mask:event = 0x433f24 in 0x188
    unsigned long a, d, c;
    c = 2;
    __asm__ __volatile__("rdpmc" : "=a" (a), "=d" (d) : "c" (c));
    return ((unsigned long)a) | (((unsigned long)d) << 32);
#else
    return 0;
#endif
}

void getMetricsStart(Metrics &m) {
    clock_gettime(CLOCK_MONOTONIC, &(m.startTime));
    m.l3Miss = rdpmc_llc_cache_misses();
    m.l2Miss = rdpmc_l2_cache_misses();
    m.l1Miss = rdpmc_l2_cache_refs();
    m.retiredInst = rdpmc_retired_inst_all();
    m.coreCycles = rdpmc_core_cycles();
}

void getMetricsEnd(Metrics &m) {
    m.coreCycles = rdpmc_core_cycles() - m.coreCycles;
    m.retiredInst = rdpmc_retired_inst_all() - m.retiredInst;
    m.l1Miss = rdpmc_l2_cache_refs() - m.l1Miss;
    m.l2Miss = rdpmc_l2_cache_misses() - m.l2Miss;
    m.l3Miss = rdpmc_llc_cache_misses() - m.l3Miss;
    clock_gettime(CLOCK_MONOTONIC, &(m.endTime));
    m.timeElapsedus = getTimeDiff(m.startTime, m.endTime);
}

void printMetrics(Metrics &m) {
    std::cout << "Time elapsed (us): " << m.timeElapsedus << std::endl;
    std::cout << "Retired Insructions: " << m.retiredInst << std::endl;
    std::cout << "Core Cycles: " << m.coreCycles << std::endl;
    std::cout << "L3 Misses: " << m.l3Miss << std::endl;
    std::cout << "L2 Misses: " << m.l2Miss << std::endl;
    std::cout << "L1 Misses: " << m.l1Miss << std::endl;    
}
