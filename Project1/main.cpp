
struct Node
{
	unsigned int queueID;
	unsigned int next;
};

struct Q
{
	static unsigned int queueID;
	static Node indexArray[2048];

	unsigned int begin;
	unsigned int end;
    int size;
};
unsigned int Q::queueID = 0;// set 0 as default, means on queue created
Node Q::indexArray[2048] = {};

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