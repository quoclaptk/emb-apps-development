/*
 * userConf.h
 *
 *  Created on: Mar 11, 2022
 *      Author: quocl
 */

#ifndef _USERCONF_H_
#define _USERCONF_H_
#include <stdio.h>
#include "NUC100Series.h"

static __inline__ void delayMicroseconds(uint32_t usec)
{
  if (usec == 0)return;
  /*
   *  The following loop:
   *
   *    for (; ul; ul--) {
   *      __asm__ volatile("");
   *    }
   *
   *  produce the following assembly code:
   *
   *    loop:
   *      subs r3, #1        // 1 Core cycle
   *      bne.n loop         // 1 Core cycle + 1 if branch is taken
   */

  // VARIANT_MCK / 1000000 == cycles needed to delay 1uS
  //                     3 == cycles used in a loop
  uint32_t n = usec * (SystemCoreClock / 1000000)/3;
  __asm__ __volatile__(
      "1:              \n"
      "   sub %0, #1   \n" // substract 1 from %0 (n)
      "   bne 1b       \n" // if result is not 0 jump to 1
      : "+r"(n)            // '%0' is n variable with RW constraints
      :                    // no input
      :                    // no clobber
  );
  // https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html
  // https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html#Volatile
}
static __inline__ void delay(uint32_t ms)
{
	for(;ms;ms--)
	{
		delayMicroseconds(1000);
	}
}
extern void transmitData(uint8_t addr, uint8_t data);
extern void masterTransmit(uint8_t addr, uint8_t *data, uint8_t size);
extern void masterReceive(uint8_t addr, uint8_t *data, uint8_t size);
extern uint8_t spiWrite(uint8_t data);
extern void _cs(bool level);

#endif /* USERCONF_H_ */
