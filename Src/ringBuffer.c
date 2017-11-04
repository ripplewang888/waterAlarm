/******************************************************************************
 * Copyright (C) 2016, roger
 * All rights reserved.
 *
 * �ļ�����: ringbuffer.c
 * ժ     Ҫ�����λ�����           
 * ��    ��: linux/kfifo    
 ******************************************************************************/

#include "ringbuffer.h"
#include <string.h>
#include <stddef.h>
#include <assert.h>

#define min(a,b) ( (a) < (b) )? (a):(b)     

/******************************************************************************
 *������   :ring_buf_init
 *�������� :����һ���ջ��λ�����
 *������� :r ���λ��������ƿ�
 *����ֵ   :��0��ʾ�ɹ� 
 *****************************************************************************/
int ring_buf_create(ringBufTypeDef *r,unsigned char *buf,unsigned int len)
{
    r->buf = buf;
    r->size = len;
    r->front = r->rear = 0;
    return buf == NULL;
}
/**********************************************************************
 *������   :ring_buf_clr
 *�������� :��ջ��λ����� 
 *������� :r - ����յĻ��λ�����
 *����ֵ   :None 
 *********************************************************************/
void ring_buf_clr(ringBufTypeDef *r)
{
    r->front = r->rear = 0;
}

/**********************************************************************
 *������   :ring_buf_len
 *�������� :���㻷�λ��������� (�ֽ�Ϊ��λ)
 *������� :r.���λ��������ƿ�
 *����ֵ   :���λ���������Ч�ֽ��� 
 *********************************************************************/
unsigned int ring_buf_len(ringBufTypeDef *r)
{
    return r->rear - r->front;
}

/**********************************************************************
 *������   :ring_buf_put
 *�������� :��ָ�����ȵ����ݷŵ����λ������� 
 *������� :buf - ���ݻ�����
 *          len - ���������� 
 *����ֵ   :ʵ�ʷŵ��е����� 
 *********************************************************************/
unsigned int ring_buf_put(ringBufTypeDef *r,unsigned char *buf,unsigned int len)
{
    unsigned int i;
    unsigned int space;                      
    space = r->size + r->front - r->rear;
    len = min(len , space);                  /*�õ�ʵ��д������ݳ���*/
    /*min(���пռ��С,��real_in��ʼ����������β�Ŀռ�) -------------*/
    i = min(len, r->size - r->rear % r->size);   
    /*
     * ��len > lʱ������buffer��ʣ�������
     *��ʣ��Ĵ�СΪlen - l 
     */            
    memcpy(r->buf + r->rear % r->size, buf, i); 
    memcpy(r->buf, buf + i, len - i);       
    r->rear += len;     
    return len;

}


/**********************************************************************
 *������   :rueueGet
 *�������� :�ӻ��λ������ж�ȡָ�����ȵ����� 
 *������� :len - ��ȡ���� 
 *������� :buf - ������ݻ�����
 *����ֵ   :ʵ�ʶ�ȡ���� 
 *********************************************************************/
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

