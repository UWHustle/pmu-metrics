#!/bin/bash

# Enable rdpmc instruction at user-level
echo 2 > _rdpmc.txt
cp _rdpmc.txt /sys/devices/cpu/rdpmc
rm _rdpmc.txt

# Install required libraries
apt update
apt install cpuid msr-tools
modprobe msr