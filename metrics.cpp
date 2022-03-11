#include "metrics.h"

unsigned long _rdpmc(unsigned long pmc_id) {
#if _COLLECT_PMU_METRICS_
    unsigned long a, d;
    __asm__ __volatile__("rdpmc" : "=a" (a), "=d" (d) : "c" (pmc_id));
    return ((unsigned long)a) | (((unsigned long)d) << 32);
#else
    return 0;
#endif
}

void initMetrics(Metrics &m) {
    m.n =  3 * FIXED_CTRS_ENBL + N_PERFEVTSEL_MSR;
    m.metrics = (unsigned long*)malloc(sizeof(unsigned long)*m.n);
    m.pmu_ids = (unsigned long*)malloc(sizeof(unsigned long)*m.n);
    int idx = 0;
    if (FIXED_CTRS_ENBL) {
        m.pmu_ids[0] = (1<<30);
        m.pmu_ids[1] = (1<<30) + 1;
        m.pmu_ids[2] = (1<<30) + 2;
        idx = 3;
    }
    for (int i=0; i<N_PERFEVTSEL_MSR; i++,idx++) {
        m.pmu_ids[idx] = i;
    }
}

void getMetricsStart(Metrics &m) {
    for (int i=0; i<m.n; i++) {
        m.metrics[i] = _rdpmc(m.pmu_ids[i]);
    }
}

void getMetricsEnd(Metrics &m) {
    for (int i=0; i<m.n; i++) {
        m.metrics[i] = _rdpmc(m.pmu_ids[i]) - m.metrics[i];
    }
}

// void printMetrics(Metrics &m) {
//     std::cout << "Retired Insructions: " << m.metrics[0] << std::endl;
//     std::cout << "Core Cycles: " << m.metrics[1] << std::endl;
//     std::cout << "Reference Cycles: " << m.metrics[2] << std::endl;
//     std::cout << "L3 Misses: " << m.metrics[3] << std::endl;
//     std::cout << "L2 Misses: " << m.metrics[4] << std::endl;
//     std::cout << "L1 Misses: " << m.metrics[5] << std::endl;    
// }
