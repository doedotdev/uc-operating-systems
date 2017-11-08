# opsys
University of Cincinnati - Operating Systems

## Problem 1 Usage

g++ hw1.cpp -o part1
./part1 hornbd96@gmail.com

## Problem 2 Usage

compile the server `gcc -o server server.c`

You start the server, it creates some share memory. `./server`

compile the client `gcc -o client client.c`

Create a file called called read.txt with some words in it.

You start the client in another window, it reads from read.txt whatever is in there into shared memory. `./client read.txt`

Server sees that the shared memory was changed, and reads it.

If the text isn't `STOP!!!` then it writes it into write.txt.

```
doemac:2 benjamin.horn$ gcc -o server server.c 
doemac:2 benjamin.horn$ ./server 
Server: Created shared memory segment
Start Client in another console/terminal window.
   gcc -o client client.c
   ./client read.txt
Server: Shared memory from client found.
Server: Found shared memory containing: STOP!!!
Server: Writing new found text in write.txtServer: Stop string found! 
Server: Detached shared memory
Server: Removed shared memory
Server: Done
doemac:2 benjamin.horn$ 
```

```
doemac:2 benjamin.horn$ gcc -o client client.c
doemac:2 benjamin.horn$ ./client read.txt
Client: Received a shared memory segment.
Client: Attached the shared memory.
Client: Wrote in shared memory: STOP!!!
Client: Informed server data is waiting.
Client: Detached shared memory.
Client: Done.
doemac:2 benjamin.horn$ 
```

## Problem 3 Usage

```
READER ---
doemac:3 benjamin.horn$ gcc -o read3 read3.c 
doemac:3 benjamin.horn$ ./read3 
Output: 1111111111
Output: 1111111111
Output: 1111111111
Output: 1111111111
Output: 1111111111
Output: 1111111111
Output: 1111111111
Output: 9999999999
Output: 9999999999
Output: 1111111111
Output: 1111111111
Output: 1111111111
Output: 1111111111
Output: 1111111111
Output: 5555555555
Output: 5555555555
Output: 5555555555
Output: 5555555555
Output: 5555555555
Output: 5555555555
doemac:3 benjamin.horn$ 
```

```
WRITER ---
doemac:3 benjamin.horn$ gcc -o write3 write3.c 
doemac:3 benjamin.horn$ ./write3
^C
doemac:3 benjamin.horn$ ./write3
^C  
doemac:3 benjamin.horn$ ./write3
^C
doemac:3 benjamin.horn$ 
```