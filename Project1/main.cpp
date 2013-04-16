
struct Node
{
	unsigned int queueID;
	unsigned int next;
};

struct Q
{
	unsigned char *mBegin;
	unsigned char *mEnd;
    int size;
};

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