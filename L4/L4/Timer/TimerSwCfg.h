#ifndef TIMERSWCFG_H_
#define TIMERSWCFG_H_


/*******************************************************************************
 * includes
 ******************************************************************************/
#include <stdint.h>
#include "StatuError.h"

/*******************************************************************************
 * defines
 ******************************************************************************/
#define CPL_SAL_TIMER_VALUE_MAX	4294967295
#ifndef NULL
#define NULL ((void *)0)
#endif
/*******************************************************************************
 * typedefs
 ******************************************************************************/

/**
 * @brief Timer base value.
 */
typedef uint32_t TimerSwValue;

/*******************************************************************************
 * timer structures
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * @}
 */

#endif /* TIMERSWCFG_H_ */