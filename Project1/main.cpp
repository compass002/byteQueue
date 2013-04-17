
struct Node
{
	unsigned int queueID;
	unsigned int next;
};
struct Q
{
	unsigned int begin;
	unsigned int end;
    int size;
};

unsigned int numberOfQueues;
Node indexArray[2048];
unsigned char data[2048];// the given memory
// Creates a FIFO byte queue, returning a handle to it. 
Q * create_queue()
{
	
} 
// Destroy an earlier created byte queue. 
void destroy_queue(Q * q); 
// Adds a new byte to a queue. 
void enqueue_byte(Q * q, unsigned char b); 
// Pops the next byte off the FIFO queue 
unsigned char dequeue_byte(Q * q); 