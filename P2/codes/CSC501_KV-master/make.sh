#!/bin/bash

cd kernel_module/
echo -e "\n\n\n\nsudo rmmod keyvalue\n\n"
sudo rmmod keyvalue

echo -e "\n\n\n\nsudo make clean\n\n"
sudo make clean
echo -e "\n\n\n\nsudo make\n\n"
sudo make
echo -e "\n\n\n\nsudo make install\n\n"
sudo make install

echo -e "\n\n\n\nsudo insmod keyvalue.ko\n\n"
sudo insmod keyvalue.ko

echo -e "\n\n\n\ncd ../library/\n\n"
cd ../library/
echo -e "\n\n\n\nsudo make clean\n\n"
sudo make clean
echo -e "\n\n\n\nsudo make\n\n"
sudo make
echo -e "\n\n\n\nsudo make install\n\n"
sudo make install

echo -e "\n\n\n\nsudo ldconfig\n\n"
sudo ldconfig

echo -e "\n\n\n\ncd ../benchmark/\n\n"
cd ../benchmark/
echo -e "\n\n\n\nmake clean\n\n"
make clean
echo -e "\n\n\n\nmake\n\n"
make

