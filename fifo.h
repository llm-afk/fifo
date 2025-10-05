#ifndef FIFO_H
#define FIFO_H

#include <stdint.h>
#include <string.h>

typedef struct
{
    uint8_t* buf;
    uint32_t buf_len;
    volatile uint32_t read;
    volatile uint32_t write;
}fifo_t;

void fifo_init(fifo_t *fifo, uint8_t *buf, uint32_t buf_len);
uint32_t fifo_getUsed(fifo_t *fifo);
uint32_t fifo_getAvai(fifo_t *fifo);
void fifo_write(fifo_t *fifo, const uint8_t *src, uint32_t len);
void fifo_read(fifo_t *fifo, uint8_t *dst, uint32_t len);
uint8_t fifo_peek(fifo_t *fifo);
void fifo_drop(fifo_t *fifo, uint32_t len);

#endif