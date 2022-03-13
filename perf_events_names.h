/***********************************************************
* Names/short descriptions of performance events present
* in the library. These names are used in the printMetrics
* function.
*
* IMPORTANT: Remember to add the name of the event to the
* event_names_map in this file for newly added events to
* perf_events.h
***********************************************************/

#ifndef __PERF_EVENTS_NAMES__
#define __PERF_EVENTS_NAMES__

#include <map>
#include <string>

#include "perf_events.h"

typedef std::pair<unsigned long, std::string> event_name_pair_t;

// Update this list with newly added events
const event_name_pair_t event_names_map[] = {
	// Architectural Events
	event_name_pair_t(ARCH_CORE_CYCLES, "Core Cycles"),
	event_name_pair_t(ARCH_TSC_REF_CYCLES, "TSC Reference Cycles"),
	event_name_pair_t(ARCH_INST_RETD, "Instructions Retired"),
	event_name_pair_t(ARCH_LLC_REF, "LLC (L3) References"),
	event_name_pair_t(ARCH_LLC_MISS, "LLC (L3) Misses"),
	event_name_pair_t(ARCH_BRANCH_INST_RETD, "Branch Instructions Retired"),
	event_name_pair_t(ARCH_BRANCH_MISS_RETD, "Branch Mispredictions Retired"),

	// Skylake and Kaby Lake Non-Architectural Events
	event_name_pair_t(SKL_KBL_L2_MISS, "L2 Misses"),
	event_name_pair_t(SKL_KBL_L2_REFS, "L1 Misses (L2 References)"),
	event_name_pair_t(SKL_KBL_DTLB_MISS, "DTLB Misses"),
	event_name_pair_t(SKL_KBL_DTLB_MISS_STLB_HIT, "DTLB Misses Hit STLB"),
	event_name_pair_t(SKL_KBL_ITLB_MISS, "ITLB Misses"),
	event_name_pair_t(SKL_KBL_ITLB_MISS_STLB_HIT, "ITLB Misses Hit STLB"),
	event_name_pair_t(SKL_KBL_RS_EMPTY, "Reservoir Station Empty Cycles"),
	event_name_pair_t(SKL_KBL_MEM_LOAD_RETD, "Retired Memory Load Instructions"),
	event_name_pair_t(SKL_KBL_MEM_LOAD_L1_HIT, "Retired Memory Load Instructions Hit L1"),
	event_name_pair_t(SKL_KBL_MEM_LOAD_L2_HIT, "Retired Memory Load Instructions Hit L2"),
	event_name_pair_t(SKL_KBL_MEM_LOAD_L3_HIT, "Retired Memory Load Instructions Hit L3"),
	event_name_pair_t(SKL_KBL_MEM_STORE_RETD, "Retired Memory Store Instructions")
};

const int num_events = sizeof(event_names_map) / sizeof(event_names_map[0]);

extern std::map<unsigned long, std::string> event_names_map_copy;

#endif // __PERF_EVENTS_NAMES__
