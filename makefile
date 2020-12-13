AP_waiting_manager: amuspark.o
	gcc -o AP_waiting_manager amuspark.o
amuspark.o: amuspark.c
	gcc -c amuspark.c
