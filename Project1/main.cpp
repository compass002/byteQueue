#include <iostream>
using namespace std;

//head
//tail
//size
//expand = 32
//next_break
//data
typedef unsigned char * Q;

// the given memory
unsigned char data[2048] = {'\0'};

// search for availavle space
int get_memory_index()
{
	for(int i = 0; i != 2048; i ++)
	{
		if(data[i] == '\0')
		{
			bool continuous = true;
			if(i + 32 < 2048)
			{
				for( int j = 1; j != 32; j ++ )
				{// check if there is 32 continuous space
					if(data[i+j] != '\0')
					{// not continuous
						continuous = false;
						i = i+j;
						break;
					}
				}
				if(continuous == true)
				{
					return i;
				}
			}
		}
	}
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


int main()
{
	
	system("pause");
	return 0;
}