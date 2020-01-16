#ifndef CBUF16_MARGIN_H
#define CBUF16_MARGIN_H

#include <stdint.h>

typedef struct{
    uint32_t head,tail, trig_head; //Head, tail, triggered head 
	uint32_t size;
    uint16_t margin;
    uint8_t FIRST, TRIGGERED, FINISHED, TSAVED;
    uint16_t *buf;
}Cbuf16;

/*
 * Initialize a Cbuf16 with a margin and buffer size
 * */
void Cbuf16Init(Cbuf16 *buf_t, int margin, uint32_t CBUF16_SIZE);

/*
 * Set the Cbuf16's trigger flag
 * */
void TriggerCbuf16(Cbuf16 *buf_t);

/*
 * Check if buffer is finished receiving data
 * */
uint8_t IsFinishedCbuf16(Cbuf16 *buf_t);
/*
 * Add val to the head of the Cbuf16.
 * Continuously fills. (Head moves tail) 
 * Else returns index of inserted value
 * */
int16_t PutCbuf16(Cbuf16 *buf_t, uint16_t val);

/*
 * Inserts mem_depth data into data_arr.
 * */
uint16_t GetCbuf16Data(Cbuf16 *buf_t, uint16_t *data_arr, uint16_t mem_depth);


#endif // CBUF16_MARGIN_H
