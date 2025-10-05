#include "fifo.h"

#define FIFO_MASK(fifo, val) ((val) & ((fifo)->buf_len - 1))

void fifo_init(fifo_t *fifo, uint8_t *buf, uint32_t buf_len)
{
    fifo->buf = buf;
    fifo->buf_len = buf_len;
    fifo->read = 0;
    fifo->write = 0;
}

uint32_t fifo_getUsed(fifo_t *fifo)
{
    return fifo->write - fifo->read;
}

uint32_t fifo_getAvai(fifo_t *fifo)
{
    return fifo->buf_len - (fifo->write - fifo->read);
}

void fifo_write(fifo_t *fifo, const uint8_t *src, uint32_t len)
{
    const uint32_t write_idx = FIFO_MASK(fifo, fifo->write);
    const uint32_t len_to_end = fifo->buf_len - write_idx;

    if (len <= len_to_end) 
    {
        memcpy(fifo->buf + write_idx, src, len);
    } 
    else 
    {
        memcpy(fifo->buf + write_idx, src, len_to_end);
        memcpy(fifo->buf, src + len_to_end, len - len_to_end);
    }
    fifo->write += len;
}

void fifo_read(fifo_t *fifo, uint8_t *dst, uint32_t len)
{
    const uint32_t read_idx = FIFO_MASK(fifo, fifo->read);
    const uint32_t len_to_end = fifo->buf_len - read_idx;

    if (len <= len_to_end) 
    {
        memcpy(dst, fifo->buf + read_idx, len);
    } 
    else 
    {
        memcpy(dst, fifo->buf + read_idx, len_to_end);
        memcpy(dst + len_to_end, fifo->buf, len - len_to_end);
    }
    fifo->read += len;
}

uint8_t fifo_peek(fifo_t *fifo)
{
    return fifo->buf[FIFO_MASK(fifo, fifo->read)];
}

void fifo_drop(fifo_t *fifo, uint32_t len)
{
    fifo->read += len;
}
