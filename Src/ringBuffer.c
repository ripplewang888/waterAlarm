/******************************************************************************
 * Copyright (C) 2016, Mashine shanghai. Ltd.
 * All rights reserved.
 *
 * Filename: ringbuffer.c
 * Author : ripple.wang
 ******************************************************************************/

#include "ringbuffer.h"
#include <string.h>
#include <stddef.h>
#include <assert.h>

#define min(a,b) ( (a) < (b) )? (a):(b)     

int ring_buf_create(ringBufTypeDef *r,unsigned char *buf,unsigned int len)
{
    r->buf = buf;
    r->size = len;
    r->front = r->rear = 0;
    return buf == NULL;
}


void ring_buf_clr(ringBufTypeDef *r)
{
    r->front = r->rear = 0;
}


unsigned int ring_buf_len(ringBufTypeDef *r)
{
    return r->rear - r->front;
}


unsigned int ring_buf_put(ringBufTypeDef *r,unsigned char *buf,unsigned int len)
{
    unsigned int i;
    unsigned int space;                      
    space = r->size + r->front - r->rear;
    len = min(len , space);                 
  
    i = min(len, r->size - r->rear % r->size);   
    memcpy(r->buf + r->rear % r->size, buf, i); 
    memcpy(r->buf, buf + i, len - i);       
    r->rear += len;     
    return len;

}



unsigned int ring_buf_get(ringBufTypeDef *r,unsigned char *buf,unsigned int len)
{
    unsigned int i;
    unsigned int space;    
    space = r->rear - r->front;                     
    len = min(len , space);                                
    i = min(len, r->size - r->front % r->size );    
    memcpy(buf, r->buf + r->front % r->size, i);    
    memcpy(buf + i, r->buf, len - i);   
    r->front += len;        
    return len;
}

