/*
 * author: Noa Figenblat
 * title: Project 4 - Memory Allocator
 * due date: 4/14/22
 */

#include "mem.h"                      
extern BLOCK_HEADER* first_header;


/*
 * Function which allocates a block of memory on the heap
 * parameter: int size --> the size in bytes of the memory space to be allocated 
 * return: --> a pointer to the start of that memory space
 * return: NULL --> there is not enough contiguous free space to satisfy this request
 * (required to return a memory address aligned to 16-byte data -- address should be divisible by 16) 
 *
 * void* --> "generic" pointer type that can be converted to any other pointer type without an explicit cast
 */ 
void* Mem_Alloc(int size){

	// if the size to be allocated is 0 return NULL
	if (size == 0){
		return NULL;
	}

	
	int headerSize = 8;	// all headers have a size of 8 bytes
	int alloc_bit; // int that holds the allocated bit (1 if allocated; 0 if free)
	int blockSize; // int that holds the size of the block in bytes
	int payload;   // int that holds the size of the payload in bytes
	int padding;   // int that holds the size of the padding in bytes
	int newSize;   // int that holds the payload + header in bytes
	int origSize;  // int that holds the size of the block to be allocated

	payload = size; // user inputted size is the payload
	newSize = payload + headerSize;

	// round up requested size to meet alignment requirements
	while(newSize % 16){
		newSize++;
	}	

	padding = newSize - payload - headerSize; // padding is the difference between the adjusted size needed and (payload+header)
	blockSize = headerSize + payload + padding; // blockSize is the sum of headerSize(8), the payload (size), and the padding
	origSize = blockSize; // storing the original requested blockSize in origSize
	
    // find a free block that's big enough
	BLOCK_HEADER *current = first_header; // setting the current block header to point to the address of the first header

	// while loop that will traverse the list until either a free block that is large enough is found 
	// or the size_alloc at current = 1 (which means it hit the last header in the list)
	while(current->size_alloc!=1){
		alloc_bit = current -> size_alloc & 1;	// retreiving the allocated bit from the current block 
		blockSize = current ->size_alloc & 0xFFFFFFFE; // getting blockSize at current block
		
		// if the allocated bit = 1 (meaning the block is already allocated)
		if(alloc_bit == 1){
			current = (BLOCK_HEADER *)((unsigned long)current + blockSize);	// increment current to point to the next block in list
		}
		// else if the allocated bit = 0 (meaning the block is free) but is NOT big enough
		else if (alloc_bit == 0 && (blockSize < origSize) ){
			current = (BLOCK_HEADER *)((unsigned long)current + blockSize); // increment to the next block in list 
		}
		// else the allocated bit = 0 (the block is free) and is large enough
		else{
			break;	// break the while loop
		}
	}

    // return NULL if we didn't find a block
	// if size_alloc of current == 1, it means no block was found 
	// (if a block was found the while loop would have broken before current->size_alloc == 1 )
	
	if(current->size_alloc == 1){
		return NULL;
	}


    // allocate the block
	int freeBlockSize = current->size_alloc - newSize; // the remainder of the block after allocating 
	current->size_alloc = newSize + 1; // allocating the block
	current->payload = size; // setting the blocks payload to the input size 

    // split if necessary
	// verify the remaining block size is >= 16 (the minimum block size)
       if(freeBlockSize >= 16){
	       BLOCK_HEADER *newHeader; // newHeader pointer
	       newHeader = (BLOCK_HEADER *)((unsigned long)current + newSize); // newHeader points to the addr
	       newHeader -> size_alloc = freeBlockSize; // new block size set and free
	       newHeader -> payload = freeBlockSize - 8; // new block payload size 
       }

       void *user_Pointer = (void *)((unsigned long)current + 8); //set user pointer to address of beginning of payload
       return user_Pointer; // return user pointer to the beginning of the payload
}


// return 0 on success
// return -1 if the input ptr was invalid
/*
 * Function which frees allocated heap blocks
 * parameter: void *ptr --> a "generic" pointer to the start of the payload
 * return: 0 if the allocated block was succesfully freed
 * return: -1 if the input ptr was invalid 
 */
int Mem_Free(void *ptr){
// use immediate coalescing for both blocks before and blocks after the block being freed
    // traverse the list and check all pointers to find the correct block 

	BLOCK_HEADER *previous; // block header pointer which points to the previous block on the heap
	BLOCK_HEADER *next; // block header pointer which points to the next block on the heap
	BLOCK_HEADER *current = first_header; // initialize ptr current to address of first block on the heap

	int blockSize; // the size of the block

	previous = first_header; // initializing previous to the first header on the heap for the first iteration
				 // of the while loop

	// while loop which traverses the list until either the last block is reached or the pointer is found 
	while(current->size_alloc != 1){
		blockSize = current -> size_alloc & 0xFFFFFFFE; // getting blockSize at current block

		void *beginPayload = (void *)(unsigned long)current + 8;
		if(beginPayload == ptr){
			next = (BLOCK_HEADER *)((unsigned long)current + blockSize);
			break;
		}
		else{
			previous = current;
			current = (BLOCK_HEADER *)((unsigned long)current + blockSize); // increment the pointer to the next block
		}
	}
    // if you reach the end of the list without finding it return -1

	// if the size allocation at current = 1, then the end of the heap was reached and the pointer was not found 
	if(current -> size_alloc == 1){
		return -1; // return -1 as the input ptr is invalid
	}

	// if free is being called on a block which is already free
	if((current -> size_alloc & 1) == 0){
		return -1; // return -1 -- double free error
	}
    
    // free the block

	int currBlockSize; // current block size (block being freed)
	int nextBlockSize; // next block size
	int prevBlockSize; // previous block size

	// if the memory being freed is the only memory on the heap
	if (current == previous){
		currBlockSize = current -> size_alloc & 0xFFFFFFFE;
		nextBlockSize = next -> size_alloc & 0xFFFFFFFE;
		current -> size_alloc = currBlockSize + nextBlockSize;
		current -> payload = current -> size_alloc - 8;
		return 0;
	}
	// if the next block is free, merge the blocks
	if ((next -> size_alloc & 1) == 0){
		currBlockSize = current -> size_alloc & 0xFFFFFFFE;
		nextBlockSize = next -> size_alloc & 0xFFFFFFFE;
		current -> size_alloc = currBlockSize + nextBlockSize;
		current -> payload = current -> size_alloc - 8;
	}

	// if the previous block is free, merge the blocks
	if ((previous -> size_alloc & 1) == 0){
		currBlockSize = current -> size_alloc & 0xFFFFFFFE;
		prevBlockSize = previous -> size_alloc & 0xFFFFFFFE;
		previous -> size_alloc = prevBlockSize + currBlockSize;
		previous -> payload = previous -> size_alloc - 8;
	}
	// otherwise free the current block 
	else{
		currBlockSize = current -> size_alloc & 0xFFFFFFFE;
		current -> size_alloc = currBlockSize;
		current -> payload = current -> size_alloc - 8;
	}
    return 0; // successfully freed the memory and coelasced adjacent free blocks
}
