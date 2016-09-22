#!/bin/bash -x

echo "This script will change all cpu governers to perfomance to disable Dynamic Voltage Frequency Scaling (DVFS)\n"
echo "more info is at cpufreq-info\n"
sudo cpufreq-set -c 0 -g performance
sudo cpufreq-set -c 1 -g performance
sudo cpufreq-set -c 2 -g performance
sudo cpufreq-set -c 3 -g performance
cpufreq-info | grep 'current CPU'
