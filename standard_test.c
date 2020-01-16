#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Cbuf16.h"


int main(){
	// Create buffer on stack and initialize
	
	uint32_t buf_size = 10000;
	Cbuf16 buf;
	Cbuf16Init(&buf, buf_size);
	
	int i;
	for(i = 0; i < buf_size + 500; i++){
		PutCbuf16(&buf, i);
	}

	//printf("HEAD: %d\n", buf.buf[0]);
	//printf("TAIL: %d\n", GetCbuf16(&buf));

	assert(buf.buf[0] == buf_size);
	assert(GetCbuf16(&buf) == 500);


	printf("Passed Test\n");
}
