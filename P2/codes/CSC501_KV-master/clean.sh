#!/bin/bash

cd kernel_module/
echo -e "\nsudo rmmod keyvalue"
sudo rmmod keyvalue
echo -e "\nsudo make clean"
sudo make clean

echo -e "\n\ncd ../library/"
cd ../library/
echo -e "\nsudo make clean"
sudo make clean

echo -e "\n\ncd ../benchmark/"
cd ../benchmark/
echo -e "\nmake clean"
make clean

