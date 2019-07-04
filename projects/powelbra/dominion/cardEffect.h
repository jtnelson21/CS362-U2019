#ifndef _CARDEFFECT_H
#define _CARDEFFECT_H

#include "dominion.h"

/* Function to handle the Baron card. 'Choice' is the decision to discard an estate (1)
or gain an estate (0). Also needs the game state and the card's position in hand. */
void playBaron(int choice, struct gameState *state, int handPos);

/* Choice 1 is > 0 to gain coins while Choice 2 is > 0 for redraw.*/
void playMinion(int choice1, int choice2, struct gameState *state, int handPos);



#endif