project: main.o queue.o function.o FIFO.o RR.o SJF.o SRTF.o
	gcc -o project main.o queue.o function.o FIFO.o RR.o SJF.o SRTF.o

main.o: main.c
	gcc -c main.c
queue.o: queue.c
	gcc -c queue.c
function.o: function.c
	gcc -c function.c
FIFO.o: FIFO.c
	gcc -c FIFO.c
RR.o: RR.c
	gcc -c RR.c
SJF.o: SJF.c
	gcc -c SJF.c
SRTF.o: SRTF.c
	gcc -c SRTF.c

clean: 
	/bin/rm project *.o
