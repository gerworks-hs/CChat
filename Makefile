all:
	gcc -o client ./src/client.c
	gcc -o server ./src/server.c
	echo "Finished"
client:
	gcc -o client ./src/client.c
	echo "Finished"
server:
	gcc -o server ./src/server.c
	echo "Finished"
clean:
	rm -vf server
	rm -vf client
	echo "Both executables has been deleted"
