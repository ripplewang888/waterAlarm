#ifndef _RING_BUF_H_
#define _RING_BUF_H_

#define BUF_LEN   128


/*���λ�����������*/
typedef struct
{
     unsigned char *buf;    /*���λ�����        */
     unsigned int size;     /*���λ�����        */
     unsigned int front;    /*ͷָ��            */
     unsigned int rear;     /*βָ��            */
}ringBufTypeDef;

/*-------------------------�ⲿ�ӿ�����----------------------------*/

int ring_buf_create(ringBufTypeDef *r,unsigned char *buf,unsigned int size);

void ring_buf_clr(ringBufTypeDef *r);

unsigned int ring_buf_len(ringBufTypeDef *r);

unsigned int ring_buf_put(ringBufTypeDef *r,unsigned char *buf,unsigned int len);

unsigned int ring_buf_get(ringBufTypeDef *r,unsigned char *buf,unsigned int len);


#endif

