#ifndef CBUF16_H
#define CBUF16_H

#include <stdint.h>



typedef struct{
    uint32_t head,tail; 
	uint32_t size;
    uint8_t FIRST;
    uint16_t *buf;

}Cbuf16;

/*
 * Initialiize Cbuf16 to an array size of CBUF16_SIZE.
 * */
void InitCbuf16(Cbuf16 *buf_t, uint32_t CBUF16_SIZE);

/*
 * Frees the Cbuf16's array. 
 * Does not free the structure.
 * */
void FreeCbuf16(Cbuf16 *buf_t);

/*
 * Add val to the head of the Cbuf16.
 * Continuously fills. (Head moves tail) 
 * Else returns index of inserted value
 * */
int16_t PutCbuf16(Cbuf16 *buf_t, uint16_t val);

/*
 * Gets val from the tail of the Cbuf16.
 * Returns -1 if tail is behind head.  
 * This means the buffer is exahusted)
 * 
 * */
int32_t GetCbuf16(Cbuf16 *buf_t);


#endif // CBUF16_H
