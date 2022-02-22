# Fine-grained Hardware Metrics using Intel's PMU

Intel's Performance Monitoring Unit (PMU) is a convenient way to obtain hardware metrics such as cache misses, core cycles, etc. in a lightweight non-intrusive manner. A useful application of PMU metrics is when one wants to benchmark a subsection of code, which is difficult to do with existing tools such as linux_perf, Vtune, etc.

## Usage

Run the setup script (requires sudo access)
```
sudo ./setup.sh -c 1
```

The `setup.sh` programs core 1 by default. You can program a different logical core by passing the `-c` flag.

Then simply wrap the code you want to benchmark with the utility functions in this library as follows

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

**NOTE**- Make sure to pin the running process to the programmed logical core using `taskset`. If core 1 has been programmed, then

```
taskset -c 1 ./a.out
```

This benchmarking library works for single-threaded code. Multi-threaded code can lauch threads that can be scheduled on arbitrary cores which may not be programmed.