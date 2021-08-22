#ifndef __BTN_H_
#define __BTN_H_

#include <stdint.h>

typedef enum
{
	BTN_A = 0,
	BTN_B = 1,
	BTN_C = 2,
	BTN_UP = 3,
	BTN_DOWN = 4,
	BTN_LEFT = 5,
	BTN_RIGHT = 6
} btn_t;

typedef enum
{
	BTN_RELEASED = 0,
	BTN_PRESSED = 1,
	BTN_HELD = 2
} state_t;

state_t BtnRead(btn_t btn);

#endif /* __BTN_H_ */
