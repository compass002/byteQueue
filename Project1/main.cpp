struct Q
{
	unsigned char *begin;
	unsigned char *end;
    unsigned char *size;
	unsigned char *capacity;
	const int EXPAND = 4;
};

// the given memory
unsigned char data[2048];

// search for availavle space
int getSpaceIndex()
{

}

// Creates a FIFO byte queue, returning a handle to it. 
Q * create_queue()
{
	
} 
// Destroy an earlier created byte queue. 
void destroy_queue(Q * q)
{

}
// Adds a new byte to a queue. 
void enqueue_byte(Q * q, unsigned char b)
{

}
// Pops the next byte off the FIFO queue 
unsigned char dequeue_byte(Q * q); 