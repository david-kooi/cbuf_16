#include <stdlib.h>
#include <stdio.h>

#include "Cbuf16_margin.h"


void Cbuf16Init(Cbuf16 *buf_t, int margin, uint32_t CBUF16_SIZE){
    buf_t->tail = buf_t->head = 0; 
	buf_t->size = CBUF16_SIZE;
    buf_t->TSAVED = buf_t->TSAVED = buf_t->FINISHED = 0;
    buf_t->margin = margin;
    buf_t->FIRST  = 1; 

	buf_t->buf = malloc(sizeof(uint16_t) * CBUF16_SIZE);
}

void Cbuf16Free(Cbuf16 *buf_t){
	free(buf_t->buf);
}

void TriggerCbuf16(Cbuf16 *buf_t){
	buf_t->TSAVED = 1;
}

uint8_t IsFinishedCbuf16(Cbuf16 *buf_t){
	return buf_t->FINISHED;
}


int16_t PutCbuf16(Cbuf16 *buf_t, uint16_t val){
//printf("HEAD: %d\n", buf_t->head);
//printf("TAIL: %d\n", buf_t->tail); 
//printf("v %d", val); 
    static int post_trigger_samples = 0;   
    static int samples_taken = 0;
    samples_taken++;  
 
    // Always insert
    buf_t->buf[buf_t->head] = val;
    buf_t->head++;

    // Head is at end
    if(buf_t->head == buf_t->size){
        buf_t->head = 0;
    }
    
    if(buf_t->TSAVED){ 
        if(post_trigger_samples == buf_t->margin){
            //printf("SAMPLES TAKEN %d POST TAKEN %d\n",samples_taken, post_trigger_samples); 
            buf_t->FINISHED = 1; 
        }
        post_trigger_samples++; 
        return buf_t->head;
    }

    // Maintain the margin by increasing the tail
    if(  (buf_t->head - buf_t->tail == buf_t->margin) || 
         (buf_t->head + (buf_t->size - buf_t->tail) == buf_t->margin) 
      ){
        buf_t->tail++;
    } 
    
    
    // Unmark first flag
    if(buf_t->FIRST = 1){
        buf_t->FIRST = 0;
    }
    
    if(buf_t->tail == buf_t->size){
        buf_t->tail = 0;
    }

    return buf_t->head;
}

uint16_t GetCbuf16Data(Cbuf16 *buf_t, uint16_t *data_arr, uint16_t mem_depth){
    int bidx, didx, samples_added = 0; 

    bidx = buf_t->tail; // Buffer idx
    didx = 0;			// Data idx

	// Start from buffer tail and iterate until head is reached
    while(bidx !=  buf_t->head){
       
		// Add values to data_arr
        data_arr[didx] = buf_t->buf[bidx];
        //printf("%d", data_arr[didx]); 
        didx++; bidx++;

        if(bidx == buf_t->size){
            bidx = 0;
        } 

        samples_added++;
    } 

    return samples_added;
}
