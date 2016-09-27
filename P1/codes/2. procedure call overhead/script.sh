for i in `seq 0 7`
do
	var="-D_foo$i""_DEFINED"

	gcc -o test test.c $var=1
	echo "\n\n\n\n$i seperator\n\n"

	for j in `seq 0 99`
	do
		./test
		echo ""
	done
done
