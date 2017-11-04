#ifndef _RING_BUF_H_
#define _RING_BUF_H_

#define BUF_LEN   128


/*环形缓冲区管理器*/
typedef struct
{
     unsigned char *buf;    /*环形缓冲区        */
     unsigned int size;     /*环形缓冲区        */
     unsigned int front;    /*头指针            */
     unsigned int rear;     /*尾指针            */
}ringBufTypeDef;

/*-------------------------外部接口声明----------------------------*/

int ring_buf_create(ringBufTypeDef *r,unsigned char *buf,unsigned int size);

void ring_buf_clr(ringBufTypeDef *r);

unsigned int ring_buf_len(ringBufTypeDef *r);

unsigned int ring_buf_put(ringBufTypeDef *r,unsigned char *buf,unsigned int len);

unsigned int ring_buf_get(ringBufTypeDef *r,unsigned char *buf,unsigned int len);


#endif

