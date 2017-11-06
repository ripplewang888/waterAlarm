#ifndef __NB_BC95_H
#define __NB_BC95_H
#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32l0xx_hal.h"
#include "usart.h"


#define  AT_REBOOT                                               "AT+NRB\r\n"
#define  AT_CFUN_FULL                                           "AT+CFUN=1\r\n"
#define  AT_CFUN_DISABLE                                     "AT+CFUN=0\r\n"
#define  AT_GET_MANUFACTURER_REVERSION        "AT+CGMR\r\n"
#define  AT_SETBAND_5                                          "AT+NBAND=5\r\n"
#define  AT_SET_FREQUENCY                                  "AT+NEARFCN=0,2509\r\n"
#define  AT_SET_APN                                           "AT+CGDCONT=1,\"IP\",\"TELE\"\r\n"
#define  AT_SET_PLMM                                         "AT+COPS=1,2,\"46011\"\r\n"
#define  AT_SET_CSQ                                              "AT+CSQ\r\n"
#define  AT_GET_NEU_STATUS                                "AT+NUESTATS\r\n"
#define  AT_SET_ATTACH                                      "AT+CGATT=1\r\n"
#define  AT_GET_ATTACH                                     "AT+CGATT?\r\n"
#define  AT_GET_IMEI                                             "AT+CGSN=1\r\n"
#define  AT_GET_IMSI                                             "AT+CIMI\r\n"
#define  AT_GET_ADDRESS                                   "AT+CGPADDR\r\n"
#define  AT_DO_PING                                           "AT+NPING=192.168.76.10\r\n"
#define  AT_SOCKET_CREATE                               "AT+NSOCR=DGRAM,17,6001,1\r\n"
#define  AT_SOCKET_SEND                                   "AT+NSOST=0,101.200.193.50,9100,2,4142\r\n"
#define  AT_SOCKET_CLOSE                                 "AT+NSOCL=0\r\n"


#define BC95_AT_TIMEOUT                                 3000
#define AT_TRY_TIMES                                       5

#ifdef __cplusplus
}
#endif
#endif /*__ NB_BC95_H */

