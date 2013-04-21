#include <stdexcept>
#include <iostream>
using namespace std;

// unsigned char data[2048]
//=============================================================
//                     THE MEMORY BUFFER
// 2048 bytes
//=============================================================
//          district that store heads of each queues
//          the heads store management informations
// ( let's set the maximum number of heads to be 30,
// ( so that this distric takes
// ( 330 bytes
//=============================================================
//          district that store datas of each queue
// ( each block consume 45 bytes
// ( this district can hold 38 blocks
// ( up to 
// ( 1718 bytes
//=============================================================
//*************************************************************
//*************************************************************
//*************************************************************
//*************************************************************
//*************************************************************
//*************************************************************
//=============================================================
//                      DESIGN OF HEAD
// 11 bytes
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
// 255 mark the end
//=============================================================
//*************************************************************
//*************************************************************
//*************************************************************
//*************************************************************
//*************************************************************
//*************************************************************
//=============================================================
//                     DESIGN OF BLOCK
// 45 bytes
// 5 bytes for manage informations
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
// not been used space will be marked as 255
//=============================================================
// 255 mark the end
//=============================================================


const int HEAD_DISTRICT_BOUNDARY = 330;
const int THE_END_BOUNDARY = 2048;

const int MARK_AS_USED = 255;
const int ADDRESS_LENGTH = 4;
const int ONE_LENGTH = 1;

const int HEAD_LENGTH = 11;// 4/4/1/1/1
const int BLOCK_LENGTH = 45;// 4/40/1
const int THE_HEAD_ITER = 8;
const int THE_TAIL_ITER = 9;

typedef unsigned char  Q;

// the given memory
unsigned char data[2048] = {'\0'};

void on_out_of_memory()
{
	cerr<<"\nerror: not enough memory.\n";
	throw("error: not enough memory.");
}
void on_illegal_operation()
{
	cerr<<"\nerror: illegal operation.\n";
	throw("error: illegal operation.");
}
// search continuous memory space in a given range [begin,end)
// should have "length" continuous bytes
// return the address or -1 if fail
int get_continuous_index(int begin, int end, int length)
{
	// check if the imput paraments are legal
	int range = end - begin;
	if( range <= 0 )
	{
		cerr<<"\nerror: range should bigger than 0.\n";
		on_illegal_operation();
		return -1;
	}else
	{
		if(range <= length)
		{
			cerr<<"\nerror: length exceed the range.\n";
			on_illegal_operation();
			return -1;
		}else
		{// all the paraments are legal
			// search if there is enough space
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
				{// there are enough space
					return begin+i+1-count;
				}
			}
			// the memory is not enough
			cout<<"\n there is not enough space for such length.\n";
			return -1;
		}
	}
}
// convert a number range 9999 to 0 to a array
void to_array(int numberA, unsigned char (&numberB)[4])
{
	int number_thousand = numberA/1000;
	int number_hundred = (numberA - number_thousand*1000)/100;
	int number_ten = (numberA - number_thousand*1000 - number_hundred*100)/10;
	int number_one = numberA - number_thousand*1000 - number_hundred*100 - number_ten*10;

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
	int head = get_continuous_index(0,HEAD_DISTRICT_BOUNDARY,HEAD_LENGTH);
	if(head != -1)
	{
		// search block district
		int first_block = get_continuous_index(HEAD_DISTRICT_BOUNDARY,THE_END_BOUNDARY,BLOCK_LENGTH);
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
			data[head + 8] = 0;
			data[head + 9] = 0;
			// mark the end
			data[head + 10] = MARK_AS_USED;
			// mark the block
			for(int i = 0; i != BLOCK_LENGTH; i ++)
			{
				data[first_block + i] = MARK_AS_USED;
			}
			// after initialization, return the head address
			Q *pHead = &data[head];
			return pHead;
		}else
		{
			cerr<<"\nerror: not enough memory to initial a block for a queue.\n";
			on_out_of_memory();
			return 0;
		}
	}else
	{
		cerr<<"\nerror: not enough memory to initial a head for a queue.\n";
		on_out_of_memory();
		return 0;
	}
}
// clear the memory from [begin,end)
void clear(int begin, int end)
{
	int range = end - begin;
	if( range <= 0 )
	{
		cerr<<"\nerror: range should bigger than 0.\n";
		on_illegal_operation();
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
		if(data[address + i] == MARK_AS_USED)
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
	clear(address, address + BLOCK_LENGTH);
}
// Destroy an earlier created byte queue. 
void destroy_queue(Q * q)
{
	// check if the queue has blocks
	bool is_block_exist = true;
	for(int i = 0; i != 4; i ++)
	{
		if(*(q+i) == 255)
			is_block_exist = false;
	}
	if(is_block_exist)
	{
		// destroy the blocks
		unsigned char address_array[4];
		for(int i = 0; i != 4; i ++)
		{
			address_array[i] = *(q+i);
		}
		int address = to_number(address_array);
		destroy_blocks(address);
	}
	// destroy the head
	clear(q, HEAD_LENGTH);
}

// Adds a new byte to a queue. 
void enqueue_byte(Q * q, unsigned char b)
{
	// check if the queue has blocks
	bool is_block_exist = true;
	for(int i = 0; i != 4; i ++)
	{
		if(*(q+i) == 255)
			is_block_exist = false;
	}
	if(is_block_exist)
	{
		// check if the block is full
		int tail_iter = *(q + THE_TAIL_ITER);
		if(tail_iter == BLOCK_LENGTH - ADDRESS_LENGTH - ONE_LENGTH)// should be 40
		{// full
			// check if there are space available for expand
			int index = get_continuous_index(HEAD_DISTRICT_BOUNDARY,THE_END_BOUNDARY,BLOCK_LENGTH);
			if(index == -1)
			{// no available space
				// report error
				cerr<<"\nerror: there is not enough memory to create a new block.\n";
				on_out_of_memory();
			}else
			{// expand a new block
				for(int i = 0; i != BLOCK_LENGTH; i ++)
				{// mark the new block
					data[index + i] = MARK_AS_USED;
				}
				// add the element to this block
				data[index + 4] = b;
				// update the iter
				*(q+9) = 1;
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
					*(q + i + 4) = last_block_address[i];
				}
			}
		}else
		{// current block is not full
			// add the element to the tail
			// get the last block address
			unsigned char last_block_address[4];
			for(int i = 0; i != 4; i ++)
			{
				last_block_address[i] = *(q + i + ADDRESS_LENGTH);
			}
			int address = to_number(last_block_address);
			// add the element to tail
			data[address + ADDRESS_LENGTH + tail_iter] = b;
			// update iter in head
			tail_iter ++;
			*(q + ADDRESS_LENGTH*2 + ONE_LENGTH) = tail_iter;
		}
	}else
	{
		// check if there are space available for expand
		int index = get_continuous_index(HEAD_DISTRICT_BOUNDARY,THE_END_BOUNDARY,BLOCK_LENGTH);
		if(index == -1)
		{// no available space
			// report error
			cerr<<"error: there is not enough memory to create a new block.";
			on_out_of_memory();
		}else
		{// expand a new block
			for(int i = 0; i != BLOCK_LENGTH; i ++)
			{// mark the new block
				data[index + i] = MARK_AS_USED;
			}
			// add the element to this block
			data[index + 4] = b;
			// update the iter
			*(q+THE_HEAD_ITER) = 0;
			*(q+THE_TAIL_ITER) = 1;
			// update index
			// convert the new block's address to array
			unsigned char block_address[4];
			to_array(index, block_address);
			for(int i = 0; i != 4; i ++)
			{
				*(q + i) = block_address[i];
				*(q + i + 4) = block_address[i];
			}
		}
	}
}
// Pops the next byte off the FIFO queue 
unsigned char dequeue_byte(Q * q)
{
	// check if block exist
	bool is_block_exist = true;
	for(int i = 0; i != 4; i ++)
	{
		if(*(q+i) == 255)
			is_block_exist = false;
	}
	if(is_block_exist)
	{
		// get the first block address
		unsigned char first_block_address[4];
		for(int i = 0; i != 4; i ++)
		{
			first_block_address[i] = *(q+i);
		}
		int address = to_number(first_block_address);
		// check if the first block is the last block
		// this is different with check next block,
		// because next block may be not the last block
		int is_same = 0;
		for(int i = 0; i != 4; i ++)
		{
			if(*(q+i) == *(q+i+ADDRESS_LENGTH))
				is_same ++;
		}
		if(is_same != 4)
		{// the first block is not the last block
			// no doubt the queue is not empty
			// able to delete element
			int head_iter = *(q + THE_HEAD_ITER);
			unsigned char result = data[address + ADDRESS_LENGTH + head_iter];
			// if the head is the last element in current block
			// destroy this block and update the queue after pop it
			if(head_iter == BLOCK_LENGTH - ADDRESS_LENGTH - ONE_LENGTH - 1)// should be 39
			{// the last element
				// change the next block to be the first block
				for(int i = 0; i != 4; i ++)
				{
					*(q+i) = data[address + i];
				}
				// update the iter
				*(q + THE_HEAD_ITER) = 0;
				// release the block
				clear(address, address + BLOCK_LENGTH);
			}else
			{// not the last element
				// release the element
				data[address + ADDRESS_LENGTH + head_iter] = 255;
				head_iter ++;
				*(q+ THE_HEAD_ITER) = head_iter;
			}
			return result;
		}else
		{// this is the last block also the first block, the only block
			// check if this block is empty, in other words
			// head iter equals tail iter
			int head_iter = *(q + THE_HEAD_ITER);
			int tail_iter = *(q + THE_TAIL_ITER);
			if(head_iter >= tail_iter)
			{// this queue is empty or have errors
				// can not delete element from a empty queue
				cerr<<"\nerror: this queue has block, but is empty, can not delete element.";
				on_illegal_operation();
				return 255;
			}else
			{// not empty
				// able to delete element
				unsigned char result = data[address + ADDRESS_LENGTH + head_iter];
				// if the head is the last element in current block
				// destroy this block and update the queue after pop it
				if(head_iter == BLOCK_LENGTH - ADDRESS_LENGTH - ONE_LENGTH - 1)// should be 39
				{// the last element
					for(int i = 0; i != 4; i ++)
					{
						*(q+i) = MARK_AS_USED;
						*(q+i+ADDRESS_LENGTH) = MARK_AS_USED;
					}
					// update the iter
					*(q + THE_HEAD_ITER) = 0;
					*(q + THE_TAIL_ITER) = 0;
					// release the block
					clear(address, address + BLOCK_LENGTH);
				}else
				{// not the last element
					// release the element
					data[address + ADDRESS_LENGTH + head_iter] = 255;
					head_iter ++;
					*(q+ THE_HEAD_ITER) = head_iter;
				}
				return result;
			}	
		}
	}else
	{
		cerr<<"error: this queue is empty, blocks not exist.";
		on_illegal_operation();
		return 255;
	}
}


int main()
{
	Q *q90 = create_queue();
	/*for(int j = 0; j != (2048/255)+1; j ++)
	{
		for(int i = 0; i != 256; i ++)
		{
			enqueue_byte(q90, i);
		}
	}*/
	for(int i = 0; i != 5; i ++)
	{
		enqueue_byte(q90,i);
	}
	for(int i = 0; i != 5; i ++)
	{
		dequeue_byte(q90);
	}
	/*for(int i = 0; i != 10; i ++)
	{
		enqueue_byte(q90,i);
	}*/
	for(int i = 0; i != 5; i ++)
	{
		dequeue_byte(q90);
	}
	//destroy_queue(q90);
	/*for(int i = 0; i != 5; i ++)
	{
		dequeue_byte(q90);
	}
	for(int i = 0; i != 255; i ++)
	{
		enqueue_byte(q90,i);
	}
	for(int i = 0; i != 455; i ++)
	{
		dequeue_byte(q90);
	}*/
	destroy_queue(q90);
	/*Q *q0 = create_queue();
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
	destroy_queue(q1);*/
	// should be:
	// 0 1
	// 2 5
	// 3 4 6 
	//===================================
	system("pause");
	return 0;
}