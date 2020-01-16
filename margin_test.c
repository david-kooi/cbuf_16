#include <stdio.h>
#include <assert.h>

#include "Cbuf16_margin.h"

#define MEM_DEPTH 100 // Total samples collected
#define TRIGGER 50    // When to start collecting for the right margin

int main(){
	Cbuf16 buf;
	Cbuf16Init(&buf, MEM_DEPTH / 2 , 500);

	int i = 0;
	uint16_t data_arr[MEM_DEPTH] = {0};	
	uint16_t ref_arr[MEM_DEPTH] = {0};


	// Load the reference array with expected data.
	// The expected data is 50 values to the left of TRIGGER and
	// 50 values to the right of TRIGGER. 
	// These 100 values comprise the MEM_DEPTH.
	for(i = 0; i < 100; i++){
		ref_arr[i] = i+1;
	}

	i = 0;
	while(IsFinishedCbuf16(&buf) == 0){
		PutCbuf16(&buf, i);	
		i++;

		if(i == TRIGGER){
			TriggerCbuf16(&buf);
		}
	}
	
	GetCbuf16Data(&buf, (uint16_t*)data_arr, MEM_DEPTH);
	for(i = 0; i < MEM_DEPTH; i++){
		assert(ref_arr[i] == data_arr[i]);
		//printf("data[%d] %d\n", i, data_arr[i]);
	}

	printf("Test Passed\n");

}
