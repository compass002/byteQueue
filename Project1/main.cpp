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
// iterator index which point to the head in the first block
// iter_head
// iterator index which point to the tail in the last block
// iter_tail
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
// not been used space will be marked as 'B'
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
// convert a number range 9999 to 0 to a array
void to_array(int numberA, unsigned char (&numberB)[4])
{
	int number_thousand = numberA/1000;
	int number_hundred = numberA/100 - number_thousand*1000;
	int number_ten = numberA/10 - number_thousand*1000 - number_hundred*100;
	int number_one = numberA - numberA/10 - number_thousand*1000 - number_hundred*100;

	numberB[0] = number_thousand + '0';
	numberB[1] = number_hundred + '0';
	numberB[2] = number_ten + '0';
	numberB[3] = number_one + '0';
}
// convert array to number
int to_number(unsigned char (&numberB)[4])
{
	int number_thousand = numberB[0] - '0';
	int number_hundred = numberB[1] - '0';
	int number_ten = numberB[2] - '0';
	int number_one = numberB[3] - '0';

	int result = number_one + number_ten*10 + number_hundred*100 + number_thousand*1000;
	return result;
}
int to_number(unsigned char (&numberB)[4], int &numberA)
{
	int result = to_number(numberB);
	numberA = result;
	return result;
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
			// initial the head
			unsigned char address[4];
			to_array(first_block, address);
			for(int i = 0; i != 4; i ++)
			{
				data[head + i] = address[i];
			}
			for(int i = 0; i != 4; i ++)
			{
				data[head + i + 4] = address[i];
			}
			data[head + 8] = '-';
			data[head + 9] = '1';
			// mark the block
			for(int i = 0; i != 44; i ++)
			{
				data[first_block + i] = 'B';
			}
			// after initialization, return the head address
			unsigned char *pHead = &data[head];
			return pHead;
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
			data[begin+i] = '\0';
		}
	}
}
// clear the memory with the given length
void clear(Q *q, int length)
{
	for(int i = 0; i != length; i ++)
	{
		*(q+i) = '\0';
	}
}
// destroy blocks
void destroy_blocks(int address)
{
	// get the next block's address
	bool is_next_exist = true;
	unsigned char address_next_array[4];
	for(int i = 0; i != 4; i ++)
	{
		if(data[address + i] == 'B')
		{// next block not exist
			is_next_exist = false;
		}
		address_next_array[i] = data[address + i]; 
	}
	if(is_next_exist)
	{// if next exist go on to destory next blocks
		int address_next = to_number(address_next_array);
		destroy_blocks(address_next);
	}
	// destroy this block
	clear(address, address+44);
}
// Destroy an earlier created byte queue. 
void destroy_queue(Q * q)
{
	// destroy the blocks
	unsigned char address_array[4];
	for(int i = 0; i != 4; i ++)
	{
		address_array[i] = *(q+i);
	}
	int address = to_number(address_array);
	destroy_blocks(address);
	// destroy the head
	clear(q,10);
}
// Adds a new byte to a queue. 
void enqueue_byte(Q * q, unsigned char b)
{
	//check if the block is full
	unsigned char first_number = *(q + 8);
	unsigned char second_number = *(q + 9);
	int iter = (first_nubmer - '0')*10 + (second_number - '0');
	if(iter == 40)
	{// full
		// check if there are space available for expand
		int index = get_continuous_index(200,2048,44);
		if(index == -1)
		{// no available space
			// report
		}else
		{// expand a new block
			for(int i = 0; i != 44; i ++)
			{// mark the new block
				data[index + i] = 'B';
			}
			// add the element to this block
			data[index + 4] = b;
			// update the iter
			*(q+8) = '0';
			*(q+9) = '0';
			// link the blocks
			unsigned char address_array[4];
			for(int i = 0; i != 4; i ++)
			{
				address_array[i] = *(q+i+4);
			}
			// get the previous last block's address
			int address = to_number(address_array);
			// convert the new block's address to array
			unsigned char last_block_address[4];
			to_array(index, last_block_address);
			// update the previous last block
			// update the last_block_index in the head
			for(int i = 0; i != 4; i ++)
			{
				data[address + i] = last_block_address[i];
				(q + i + 4) = last_block_address[i];
			}
		}
	}else
	{// current block is not full
		// add the element to the tail
		// get the iter
		int iter = *(q+8) * 10 + *(q+9);
		// get the last block address
		unsigned char last_block_address[4];
		for(int i = 0; i != 4; i ++)
		{
			last_block_address[i] = *(q + i + 4);
		}
		int address = to_number(last_block_address);
		// add the element to tail
		data[address + 4 + iter + 1] = b;
		// update iter in head
		iter ++;
		*(q + 8) = iter/10 - '0';
		*(q + 9) = iter - (int)(iter/10)*10 - '0';
	}
}
// Pops the next byte off the FIFO queue 
unsigned char dequeue_byte(Q * q)
{
	// if the head is the last element in current block
	// destroy this block and update the queue after pop it
	
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