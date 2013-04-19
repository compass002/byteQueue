#include <iostream>
using namespace std;

// unsigned char data[2048]
//=============================================================
//                     THE MEMORY BUFFER
// 2048 bytes
//=============================================================
//          district that store heads of each queues
//          the heads store essential informations
// ( let's set the maximum number of heads to be 20,
// ( so that this distric takes
// ( 200 bytes
//=============================================================
//          district that store datas of each queue
// ( each block consume 44 bytes
// ( this district can hold 42 blocks
// ( up to 
// ( 1848 bytes
//=============================================================
//*************************************************************
//*************************************************************
//*************************************************************
//*************************************************************
//*************************************************************
//*************************************************************
//=============================================================
//                      DESIGN OF HEAD
// 10 bytes
//=============================================================
//=============================================================
// first block index
// fist_index_0
// fist_index_1
// fist_index_2
// fist_index_3
//=============================================================
// last block index
// last_index_0
// last_index_1
// last_index_2
// last_index_3
//=============================================================
// iterator index which point to the tail in the block
// iter_0
// iter_1
//=============================================================
// ( size and capacity, 
// ( if not not necessary, 
// ( do not design this part
//=============================================================
// ( block initial length (a constant value)
// ( the length when expand the queue to add a new block
// ( however, while pop the head element, 
// ( the length of the first block will decrease
// ( length_0
// ( length_1
// ( length_2
// ( length_3
// ( .......................
// ( let's set the block initial length to 44
//=============================================================
//*************************************************************
//*************************************************************
//*************************************************************
//*************************************************************
//*************************************************************
//*************************************************************
//=============================================================
//                     DESIGN OF BLOCK
// 44 bytes
// 4 bytes for manage informations
// 40 bytes for datas
//=============================================================
// point to the index of next block first element address
// next_0
// next_1
// next_2
// next_3
//=============================================================
// remain datas
// .......
// datas
// .......
// not been used space will be marked as '\0'
//=============================================================





typedef unsigned char  Q;
// the given memory
unsigned char data[2048] = {'\0'};

// search continuous memory space in a given range [begin,end)
// should have "length" continuous bytes
// return the address or -1 if fail
int get_continuous_index(int begin, int end, int length)
{
	int range = end - begin;
	if( range <= 0 )
	{
		cerr<<"\nerror: range should bigger than 0.\n";
		return -1;
	}else
	{
		if(range <= length)
		{
			cerr<<"\nerror: length exceed the range.\n";
			return -1;
		}else
		{
			int count = 0;
			for(int i = 0; i != range; i ++)
			{
				if(data[begin+i] == '\0')
				{
					count ++;
				}else
				{
					count = 0;
				}
				if(count == length)
				{
					return begin+i-count;
				}
			}
		}
	}
}
// initial a head by address
void initial_head(int address)
{
	int iter = 0;
	data[address + iter] = 'H';
	iter ++;
	data[address + iter] = 'D';
	iter ++;
}
// Creates a FIFO byte queue, returning a handle to it. 
// if fail to create a queue, return 0
Q * create_queue()
{

	// search head district
	int head = get_continuous_index(0,320,10);
	if(head != -1)
	{
		// search block district
		int first_block = get_continuous_index(320,2048,44);
		if(first_block != -1)
		{// able to initial a queue
			// initial the queue
			// initial the head first

			// after initialization, return the head address

		}
	}
	return 0;
} 
// clear the memory from [begin,end)
void clear(int begin, int end)
{
	int range = end - begin;
	if( range <= 0 )
	{
		cerr<<"\nerror: range should bigger than 0.\n";
		return;
	}else
	{
		for(int i = 0; i != range; i ++)
		{
			data[begin+i] == '\0';
		}
	}
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
unsigned char dequeue_byte(Q * q)
{
}


int main()
{
	Q * q0 = create_queue(); 
	enqueue_byte(q0, 0); 
	enqueue_byte(q0, 1); 
	Q * q1 = create_queue(); 
	enqueue_byte(q1, 3); 
	enqueue_byte(q0, 2); 
	enqueue_byte(q1, 4); 
	printf("%d", dequeue_byte(q0)); 
	printf("%d\n", dequeue_byte(q0)); 
	enqueue_byte(q0, 5); 
	enqueue_byte(q1, 6); 
	printf("%d", dequeue_byte(q0)); 
	printf("%d\n", dequeue_byte(q0)); 
	destroy_queue(q0); 
	printf("%d", dequeue_byte(q1)); 
	printf("%d", dequeue_byte(q1)); 
	printf("%d\n", dequeue_byte(q1)); 
	destroy_queue(q1); 
	// should be:
 	// 0 1 2 5 3 4 6 
	//===================================
	system("pause");
	return 0;
}