#include <iostream>
using namespace std;

//unsigned char data[2048]
//=============================================================
//                     THE MEMORY BUFFER
//2048 bytes
//=============================================================
//          district that store heads of each queues
//          the heads store essential informations
//( let's set the maximum number of heads to be 20,
//( so that this distric takes
//( 320 bytes
//=============================================================
//          district that store datas of each queue
//( each block consume 44 bytes
//( this district can hold 39 blocks
//( up to 
//( 1728 bytes
//=============================================================
//*************************************************************
//*************************************************************
//*************************************************************
//*************************************************************
//*************************************************************
//*************************************************************
//=============================================================
//                      DESIGN OF HEAD
//16 bytes
//=============================================================
//=============================================================
//mark the begin
//H
//D
//=============================================================
//queue ID, marked to seperate each queues
//id_0
//id_1
//id_2
//id_3
//=============================================================
//first block index
//fist_index_0
//fist_index_1
//fist_index_2
//fist_index_3
//=============================================================
//last block index
//last_index_0
//last_index_1
//last_index_2
//last_index_3
//=============================================================
//iterator index which point to the tail in the block
//iter_0
//iter_1
//=============================================================
//( size and capacity, 
//( if not not necessary, 
//( do not design this part
//=============================================================
//( block initial length (a constant value)
//( the length when expand the queue to add a new block
//( however, while pop the head element, 
//( the length of the first block will decrease
//( length_0
//( length_1
//( length_2
//( length_3
//( .......................
//( let's set the block initial length to 44
//=============================================================
//*************************************************************
//*************************************************************
//*************************************************************
//*************************************************************
//*************************************************************
//*************************************************************
//=============================================================
//                     DESIGN OF BLOCK
//44 bytes
//4 bytes for manage informations
//40 bytes for datas
//=============================================================
//point to the index of next block first element address
//next_0
//next_1
//next_2
//next_3
//=============================================================
//remain datas
//.......
//datas
//.......
//not been used space will be marked as '\0'
//=============================================================







//datas
typedef unsigned char  Q;

// the given memory
unsigned char data[2048] = {'\0'};

// search for availavle space
int get_memory_index()
{
	bool succeed = false;
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
					succeed = true;
					return i;
				}
			}
		}
	}
	if( succeed == false )
		return -1;
}

// Creates a FIFO byte queue, returning a handle to it. 
Q * create_queue()
{
	int index = get_memory_index();
	if( index != -1 )
	{// there are available space
		data[index] = '0' + index;//head_index
		data[index + 1] = '0' + index;//tail_index
		data[index + 2] = '0';//size
		data[index + 3] = 1;//blocks
		data[index + 4] = '\0';//next_block_index
		//datas
		for(int i = 0; i != 32-5; i ++)
		{
			// mark the space
			data[index + 5 + i] = '.';
		}
		unsigned char *pHead = &data[index];
		return pHead;
	}else
	{
		return 0;
	}

} 
// clear the memory from [begin,end)
void clear(int begin, int end)
{
	int range = end - begin;
	for(int i = 0; i != range; i ++ )
	{
		data[begin + i] = '\0';
	}
}
// Destroy an earlier created byte queue. 
void destroy_queue(Q * q)
{
	if(q != 0)
	{
		int head_index = *q - '0';
		int next = data[head_index + 4];
		clear(head_index, head_index+32);
		while(next != '\0')
		{
			int temp_index = next;
			next = data[temp_index+4];
			clear(temp_index, temp_index+32);
		}
	}else
	{
		// error
	}
}
// Adds a new byte to a queue. 
void enqueue_byte(Q * q, unsigned char b)
{
	if(q != 0)
	{
		int head_index = *q - '0';
		int blocks = data[head_index + 3];
		int capacity = blocks * 32;
		int size = data[head_index + 2];
		int free_space = capacity - size;
		if( free_space <= 0 )
		{// space is enough

		}else
		{
			int new_index = get_memory_index();
			if( new_index != -1 )
			{// there are available space
				data[new_index] = *q;//head_index
				//data[new_index + 1] = *(q+1);//tail_index
				data[new_index + 2] = *(q+2)+1;//size
				data[new_index + 3] = *(q+3)+1;//blocks
				data[new_index + 4] = '\0';//next_block_index
				//datas
				for(int i = 0; i != 32-5; i ++)
				{
					// mark the space
					data[new_index + 5 + i] = '.';
				}
				// add the character to the tail
				data[new_index + 5] = b;
				data[new_index + 1] = new;//tail_index
			}else
			{// fail
			}
		}

	}else
	{
		// error
	}
}
// Pops the next byte off the FIFO queue 
unsigned char dequeue_byte(Q * q)
{
}


int main()
{
	
	system("pause");
	return 0;
}