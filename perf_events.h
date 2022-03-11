/***********************************************************
* Performance events supported by the PMU.
*
* The UMASK:EVENT_NUM values of selected performance events
* have been included in this file. Please refer to the 
* Intel Developer's Manual Vol. 3B Chapter 19 to add more
* non-architectural performance events.
*
* IMPORTANT: Remember to add the name of the event in
* the event_names_map at the end of this file for newly
* added events. 
***********************************************************/

#include <map>
#include <string>

typedef std::pair<unsigned long, std::string> event_name_pair_t;

/***********************************************************
* Architectural Performance Events.
* There are 7 in all (Table 19-1 in the manual):
- Unhalted core cycles
- Unhalted TSC reference cycles
- Number of instructions retired
- Number of last-level cache (typically L3) refs
- Number of last-level cache (typically L3) misses
- Number of branch instructions retired
- Number of branch mispredictions (misses) retired
***********************************************************/
#define ARCH_CORE_CYCLES			0x003C
#define ARCH_TSC_REF_CYCLES			0x013C
#define ARCH_INST_RETD				0x00C0
#define ARCH_LLC_REF				0x4F2E
#define ARCH_LLC_MISS				0x412E
#define ARCH_BRANCH_INST_RETD		0x00C4
#define ARCH_BRANCH_MISS_RETD		0x00C5

/***********************************************************
* Note that first three architectural events are supported as
* fixed counters in PMU version 2 or higher. Given the limited
* number of PERFEVTSEL MSRs, they should be used for events
* other than the fixed counters if they are available.
***********************************************************/
#define FIXED_CTR_0		ARCH_INST_RETD
#define FIXED_CTR_1		ARCH_CORE_CYCLES
#define FIXED_CTR_2		ARCH_TSC_REF_CYCLES

/***********************************************************
* Non-Architectural Performance Events for SKYLAKE and
* KABY LAKE microarchitectures.
* Note: This is a subset of available events, refer to 
* Table 19-3 in the manual for a complete list.
***********************************************************/

/******** L2/L1 Misses ********/
// All requests that missed L2 (L2_RQSTS.MISS)
#define SKL_KBL_L2_MISS				0x3F24
// All requests to L2, presumably L1 misses (L2_RQSTS.REFERENCES)
#define SKL_KBL_L2_REFS				0xEF24

/******** DTLB Misses *********/
// DTLB load misses causing a page walk
// (DTLB_LOAD_MISSES.MISS_CAUSES_A_WALK)
#define SKL_KBL_DTLB_MISS			0x0108
// DLTB load misses that hit the STLB (DTLB_LOAD_MISSES.STLB_HIT)
#define SKL_KBL_DTLB_MISS_STLB_HIT	0x2008

/******** ITLB Misses *********/
// ITLB misses causing a page walk
// (ITLB_MISSES.MISS_CAUSES_A_WALK)
#define SKL_KBL_ITLB_MISS			0x0185
// ITLB misses that hit STLB (ITLB_MISS.STLB_HIT)
#define SKL_KBL_ITLB_MISS_STLB_HIT	0x2085

/******** Reservation Station ********/
// Cycles the reservation station (RS) was empty for the thread
// (RS_EVENTS.EMPTY_CYCLES)
#define SKL_KBL_RS_EMPTY			0x015E

/******** Memory load/store *********/
// All retired load instructions (MEM_INST_RETIRED.ALL_LOADS)
#define SKL_KBL_MEM_LOAD_RETD		0x81D0
// All retired load instructions that hit the L1 cache
// (MEM_INST_RETIRED.L1_HIT)
#define SKL_KBL_MEM_LOAD_L1_HIT		0x01D1
// All retired load instructions that hit the L2 cache
// (MEM_INST_RETIRED.L2_HIT)
#define SKL_KBL_MEM_LOAD_L2_HIT		0x02D1
// All retired load instructions that hit the L3 cache
// (MEM_INST_RETIRED.L3_HIT)
#define SKL_KBL_MEM_LOAD_L3_HIT		0x04D1
// All retired store instructions (MEM_INST_RETIRED.ALL_STORES)
#define SKL_KBL_MEM_STORE_RETD		0x82D0

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