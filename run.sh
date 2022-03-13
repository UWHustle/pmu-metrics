#!/bin/bash

CORE=19

for N in {10000000,}
do
	echo "#define N ${N}" > "n.h"
	make clean && make
	echo ${N}
	for i in {1..2}
	do
		taskset -c ${CORE} ./benchmark.out
	done
	echo "-------------"
done
