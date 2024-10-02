/*
 * author: Noa Figenblat
 * title: Project 6 - Cache Memory
 * due: 05/06/2022
 *
 */ 

#include <stdio.h>

// THE CACHE
struct LINE{
    char valid;
    int tag;
    char data[32];
};

struct SET{
    struct LINE line[1];
};

struct CACHE {
    struct SET set[8];
} cache;

// GLOBALDATA
// increment these in your function
unsigned hit_count  = 0;
unsigned miss_count = 0;
unsigned read_data_count = 0;

// SYSTEM BUS 
// call Read_Data_From_Ram to update this
char system_bus[32];



// READ DATA FROM RAM
// this function copies 32 character from the text file to
// the system_bus array aligned with the system bus
// (we will not test this with input larger than the text file)
void Read_Data_From_Ram(unsigned address) {
    address >>= 5; address <<= 5; // get align the data
    read_data_count++;
    FILE *file;
    file = fopen("alice_in_wonderland.txt", "r");
    fseek(file, address, SEEK_SET);
    for (int i = 0; i<32; i++) system_bus[i] = fgetc(file);
    return;
}


/*
 * Function to check if the data in the cache is valid and if the tag matches.
 * Cache hit: return the char matching the address and incremement the hit count
 * Cache miss: read data from system bus, copy into the cache, increment miss count, and
 * return the char matching the address
 *
 * Number of Tag bits: 24 
 * Number of Set bits: 3 
 * Number of Offset bits: 5
 * Address size: 32 
 * | TAG | SET | OFFSET |
 *
 * param: unsigned address
 * return: char retChar 
 */ 
char Read_Data_From_Cache(unsigned address){
    
	char retChar; // char variable to hold the char being returned

	// extracting tag, set, and offset from address passed into the function
	unsigned t = (address >> 8) & ((1 << 24)-1); // tag 
	unsigned s = (address >> 5) & ((1 << 3)-1); // set
	unsigned b = (address >> 0) & ((1 << 5)-1); // offset

	unsigned isValid = cache.set[s].line[0].valid; // contains either 1(valid) or 0(invalid)
	unsigned isMatch = cache.set[s].line[0].tag; // contains the address's tag

	// if the cache is NOT valid OR the tag does NOT match 
	if((isValid == 0) || (isMatch != t)){
		miss_count ++; // increment the miss count
	
		Read_Data_From_Ram(address); // update the system bus
	
		// for loop copying the system bus into the cache 
		for (int i = 0; i < 32; i++){
			cache.set[s].line[0].data[i] = system_bus[i];
		}

		cache.set[s].line[0].valid = 1; // overwrite cache to now be valid
		cache.set[s].line[0].tag = t; // overwrite tag to match 
		
		retChar = cache.set[s].line[0].data[b]; // extracting char to return from cache 

		return retChar;
	}
	// if the cache is BOTH valid and the tag matches
	else {
		hit_count ++; // increment the hit count 
		retChar = cache.set[s].line[0].data[b]; // extracting char to return from cache
		return retChar;
	}
}


int main() {
    // INITIALIZE CACHE
    for (int i = 0; i<8; i++) cache.set[i].line[0].valid = 0;
    
    // READ SOME DATA
    char c;
    c = Read_Data_From_Cache(0); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(1); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(2); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(3); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(4); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );



    // PERSONAL TESTS
    
   /* 
    for (int i = 0; i < 500; i++){
	    c = Read_Data_From_Cache(i);
	    printf("Reading character at index %d    : data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", i, c, hit_count, miss_count, read_data_count);
    }
*/
    return 0;
}

