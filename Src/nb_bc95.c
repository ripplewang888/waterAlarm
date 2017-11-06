#include "common.h"


#if configBC95_DEBUG
      #define BC95_DBG(format,...)   printf("[BC95 DEBUG] %s:%d %s:: "format"\r\n",  __FILE__, __LINE__, __FUNCTION__,##__VA_ARGS__)
#else
     #define BC95_DBG(format,...)   
#endif

extern ringBufTypeDef   g_ringBufStruct;



rc_t BC95_sendAT(uint8_t *cmdSend , uint8_t *cmdRecv,int timeoutMs)
{
    uint32_t len = 0;
    uint8_t readBuf[BUF_LEN];
    uint32_t tickstart = 0;

    /*before send command, clear the ring buffer, to ensure receive data is right*/
    ring_buf_clr(&g_ringBufStruct);
    BC95_DBG(">>>>>> sendCmd : %s",cmdSend);
    uart2_mcu_BC95_SendMsg(cmdSend,strlen((char*)cmdSend));
    tickstart = HAL_GetTick();
    while((HAL_GetTick() - tickstart) < timeoutMs)
    {
        memset(readBuf, 0, BUF_LEN);
        len = uart2_mcu_BC95_Receive(readBuf);
        strcat(cmdRecv,readBuf, len);

        if(NULL  != strstr(cmdRecv, "OK\r\n")){
            return RT_SUCCESS;
        }

        //AT ERROR
        if(NULL  != strstr(cmdRecv, "ERROR\r\n")){
            BC95_DBG("cmd receive error");
            return BC95_STATUS_RESULT_ERROR;
        }

    }
    
    /*If time out ,means do not have response. To ensure ringbuffer data right, so clear it*/
    //ring_buf_clr(&g_ringBufStruct);
    BC95_DBG("!!!Receive Timeout!!!");
    return BC95_STATUS_TIMEOUT;
}



/*
Send AT comand command.
times:  max send times,  until commmand send success.
matchstr: send until match  str success.
Attention: for LM61/BC95 transparent mode , maybe do not have return value.
*/
rc_t  send_AT_to_bc95(char *cmdSend, int times, unsigned char * cmdRecv)
{

    rc_t ret = RT_SUCCESS;
    char *token = NULL;
    uint8_t  i =0;

    assert(cmdSend != NULL);
    assert(cmdRecv != NULL);
    
    do
    {
        BC95_DBG("times i = %d, cmdSend =%s\n",i+1,cmdSend);
        ret = BC95_sendAT((uint8_t *)cmdSend, cmdRecv, BC95_AT_TIMEOUT);
        /*if command not success, will do cycle times*/
        if(ret != RT_SUCCESS){
            memset(cmdRecv, 0, BUF_LEN);
            i++;
            continue;
        }else{
            //success
            break;   
        }
                
      }while(i<times);

    if(i>=times){
        BC95_DBG("command: [%s] Failed. ret=%d, have try [%d]times\n",cmdSend,ret, i+1);
        return ret;
    }
    return ret;
}




