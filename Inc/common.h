#ifndef __COMMON_H
#define __COMMON_H
#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32l0xx_hal.h"
#include "usart.h"
#include "gpio.h"
#include "nb_bc95.h"
#include "systemConfig.h"
#include "ringBuffer.h"
#include "assert.h"
#include "stm32l0xx_hal_gpio.h"
typedef enum _rc_t{
       RT_SUCCESS       =  0,
	BC95_STATUS_FAILED        =  1,
	BC95_STATUS_INVALID_PARMS =  2,
	BC95_STATUS_TIMEOUT       =  3,
	BC95_STATUS_RESULT_ERROR =4,
} rc_t;



#ifdef __cplusplus
}
#endif
#endif /*__ NB_BC95_H */


