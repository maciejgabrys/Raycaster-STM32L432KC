#ifndef __GAME_H_
#define __GAME_H_

#include <complex.h>

typedef struct
{
	float complex pos;
	float arg;
} player_t;

void GameInit(void);
void GameLoop(void);

#endif /* __GAME_H_ */
