cd kernel_module/
echo "\n\n\n\nsudo rmmod keyvalue\n\n"
sudo rmmod keyvalue

echo "\n\n\n\nsudo make clean\n\n"
sudo make clean
echo "\n\n\n\nsudo make\n\n"
sudo make
echo "\n\n\n\nsudo make install\n\n"
sudo make install

echo "\n\n\n\nsudo insmod keyvalue.ko\n\n"
sudo insmod keyvalue.ko

echo "\n\n\n\ncd ../library/\n\n"
cd ../library/
echo "\n\n\n\nsudo make clean\n\n"
sudo make clean
echo "\n\n\n\nsudo make\n\n"
sudo make
echo "\n\n\n\nsudo make install\n\n"
sudo make install

echo "\n\n\n\nsudo ldconfig\n\n"
sudo ldconfig

echo "\n\n\n\ncd ../benchmark/\n\n"
cd ../benchmark/
echo "\n\n\n\nmake clean\n\n"
make clean
echo "\n\n\n\nmake\n\n"
make

