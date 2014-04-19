all: ipc consumer

ipc: ipc.c header.c header.h
	gcc -g ipc.c header.c -o ipc
	
consumer: consumer.c header.c header.h
	gcc -g consumer.c header.c -o consumer
	
clean:
	rm -f *.o a.out ipc consumer core
