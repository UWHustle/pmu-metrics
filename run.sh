#!/bin/bash

CORE=19

for N in {10000000,1000000,100000,10000,1000,100}
do
	echo "#define N ${N}" > "n.h"
	make clean && make
	echo "N:" ${N}
	for i in {1..10}
	do
		taskset -c ${CORE} ./benchmark.out
	done
	echo "-------------"
done

git checkout -- n.h
