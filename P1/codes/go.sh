#!/bin/bash 

hello_main(){
	rm -rf hello_main.o hello_main
	gcc -c -o hello_main.o hello_main.c
	gcc -o hello_main hello_main.c
	for i in 1 2 3 4 5 6 7 8 9 10
	do
		./hello_main | grep 'clock cycles'
		sleep 5 
	done
}

runcache(){
	rm -rf cache.o cache
	gcc -c -o cache.o cacheAccessTime.c
	gcc -o cache cacheAccessTime.c

	./cache
}

exp(){

cd $1.*
pwd
make clean
make
for i in `seq 1 $2`:
	do 
		nice -20 ./minibench
	done
cd -
}

exp $1 $2
#hello_main
#runcache
