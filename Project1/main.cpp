#include <iostream>
using namespace std;

//head_index
//tail_index
//size
//blocks
//(expand = 32)
//next_block_index
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