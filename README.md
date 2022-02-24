# Fine-grained Hardware Metrics using Intel's PMU

Intel's Performance Monitoring Unit (PMU) is a convenient way to obtain hardware metrics such as cache misses, core cycles, etc. in a lightweight non-intrusive manner. A useful application of PMU metrics is when one wants to benchmark a subsection of code, which is difficult to do with existing tools such as linux_perf, Vtune, etc.

## Usage

1. Run the setup script (requires sudo access)
```
sudo ./setup.sh -c 1
```
The `setup.sh` script programs PMU registers on the logical core specified by the `-c` flag to measure the following hardware metrics:

- Time elapsed (microseconds)
- Instructions executed
- Number of core cycles
- L3 misses
- L2 misses (only for Skylake and Kaby Lake architecture families)
- L1 misses (only for Skylake and Kaby Lake architecture families)

The performance metrics for L1 and L2 cache misses are specific to the Skylake and Kaby Lake architecture families, while the rest of the metrics work across all architectures. Cloudlab `c220g5` machines have Intel Xeon 4114 Silver processors that belong to the Skylake architecture family. To check the architecture family of your processor,

```
node:~> cat /sys/devices/cpu/caps/pmu_name
skylake
```

If your CPU belongs to a different architecture family, disable the flag `_IS_SKYLAKE_` in file `metrics.h`. To program the PMU registers for a different architecture family and for other metrics, refer to chapter 18 and 19 of the [Intel's Developer Manual Volume 3](https://www.intel.com/content/www/us/en/architecture-and-technology/64-ia-32-architectures-software-developer-system-programming-manual-325384.html). This [blogpost](https://dbdrifter.blogspot.com/2022/02/hardware-counters-for-non-intrusive.html) will serve as a guide to navigate the manual.

2. After running the setup script, simply wrap the code you want to benchmark with the utility functions in this library as follows
```
...

Metrics m;
getMetricsStart(m);
<...
code to bechmark
...>
getMetricsEnd(m);
printMetrics(m);

...
```

3. Make sure to pin the process to the programmed logical core using `taskset`. If core 1 has been programmed, then
```
taskset -c 1 ./a.out
```

This benchmarking library works for single-threaded code. Multi-threaded code can lauch threads that can be scheduled on arbitrary cores which may not be programmed. In such cases, a more complex approach of setting the program's CPU affinity to a subset of programmed cores, as well as collecting metrics from multiple cores will be required.