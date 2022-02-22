#!/bin/bash

# The core to program
CORE=1

# Enable rdpmc instruction at user-level
echo 2 > _rdpmc.txt
cp _rdpmc.txt /sys/devices/cpu/rdpmc
rm _rdpmc.txt

# Install required libraries
apt update
apt install cpuid msr-tools
modprobe msr

# Enable all PMU units by setting IA32_PERF_GLOBAL_CTRL register (0x38f)
wrmsr -p ${CORE} 0x38f 0x70000000f

# Enable fixed counters by setting IA32_FIXED_CTR_CTRL register (0x38d)
wrmsr -p ${CORE} 0x38d 0x333

# Program the MSRs (model specific registers) to count different metrics
# Set register IA32_PERFEVTSEL0 (0x186) to count L3 misses
wrmsr -p ${CORE} 0x186 0x43412e
# Set register IA32_PERFEVTSEL1 (0x187) to count L2 references (L1 misses)
wrmsr -p ${CORE} 0x187 0x43ef24
# Set register IA32_PERFEVTSEL2 (0x188) to count L2 misses
wrmsr -p ${CORE} 0x188 0x433f24