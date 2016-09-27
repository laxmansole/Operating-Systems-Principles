clear
make clean
make

for i in `seq 1 30`
do
	./minibench
done
