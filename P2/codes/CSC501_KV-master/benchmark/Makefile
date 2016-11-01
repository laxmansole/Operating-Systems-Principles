all: benchmark validate

benchmark: benchmark.c
	$(CC) -g -O0 benchmark.c -o benchmark -lckv -pthread
validate: validate.c
	$(CC) -g -O0 validate.c -o validate -lckv -pthread
clean:
	rm -f benchmark validate
