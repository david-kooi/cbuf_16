#include "Cbuf16.h"

#include <stdlib.h>
#include <stdio.h>


void Cbuf16Init(Cbuf16 *buf_t, uint32_t CBUF16_SIZE){
	buf_t->size = CBUF16_SIZE;
	buf_t->buf = malloc(sizeof(uint16_t) * buf_t->size);
    buf_t->tail = buf_t->head = 0; 
    buf_t->FIRST = 1; 
}

void Cbuf16Free(Cbuf16 *buf_t){
	free(buf_t->buf);
}

int16_t PutCbuf16(Cbuf16 *buf_t, uint16_t val){
//printf("HEAD: %d\n", buf_t->head);
//printf("TAIL: %d\n", buf_t->tail); 

    if(buf_t->head == buf_t->tail && buf_t->FIRST == 0){
        buf_t->tail++;         
        if(buf_t->tail == buf_t->size){
            buf_t->tail = 0;
        }
    }


    buf_t->buf[buf_t->head] = val;
    buf_t->head++;

    if(buf_t->FIRST = 1){
        buf_t->FIRST = 0;
    }

    if(buf_t->head == buf_t->size){
        buf_t->head = 0;
    }

    return buf_t->head;
}

int32_t GetCbuf16(Cbuf16 *buf_t){
    if(buf_t->FIRST == 1){
        return -1;
    }

    //printf("TAIL: %d\n", buf_t->tail); 
    uint16_t val = buf_t->buf[buf_t->tail]; 
    if((buf_t->tail + 1) == buf_t->head){
		// Tail behind head. Unable to retreive val
       return -1; 
    }else if(buf_t->tail + 1 == buf_t->size){
        if(buf_t->head == 0){
			// Tail behind head. Unable to retreive val
            return -1;
        }else{
            buf_t->tail = 0;
            return val;
        }
    }
    else{
        buf_t->tail++;
    }

    return val;
}
