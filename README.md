# Fine-grained Hardware Metrics using Intel's PMU

Intel's Performance Monitoring Unit (PMU) is a convenient way to obtain hardware metrics such as cache misses, core cycles, etc. in a lightweight non-intrusive manner. A useful application of PMU metrics is when one wants to benchmark a subsection of code, which is difficult to do with existing tools such as linux_perf, Vtune, etc.

## Usage

1. Run the setup script (requires sudo access)
```
sudo ./setup.sh -c 1
```
The `setup.sh` script programs PMU registers on the logical core (specified using the `-c` flag) to measure the following hardware metrics:

- Time elapsed (microseconds)
- Instructions executed
- Number of core cycles
- L3 misses
- L2 misses
- L1 misses

The setup for L2 and L1 misses is specific to processors from the Intel Skylake architecture family (Cloudlab `c220g5` machines have compatible processors). For a different architecture family, refer to chapter 18 and 19 of the [Intel's Developer Manual Volume 3](https://www.intel.com/content/www/us/en/architecture-and-technology/64-ia-32-architectures-software-developer-system-programming-manual-325384.html) to program the PMU registers accordingly.

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