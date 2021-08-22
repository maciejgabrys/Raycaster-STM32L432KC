#ifndef __SCR_H_
#define __SCR_H_

#include <stdint.h>
#include "main.h"

#define SCR_WIDTH	96
#define SCR_HEIGHT	64

extern uint8_t scr_buf[SCR_WIDTH * SCR_HEIGHT];

//#define ScrDraw(x, y, color) (scr_buf[(SCR_HEIGHT - 1 - (y)) * SCR_WIDTH + (SCR_WIDTH - 1 - (x))] = color)
#define ScrDraw(x, y, color) (scr_buf[(y) * SCR_WIDTH + (x)] = color)

void ScrInit(void);
void ScrWait(void);
void ScrRefresh(void);
void ScrDeinit(void);

#endif /* __SCR_H_ */
