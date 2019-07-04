#ifndef _CARDEFFECT_H
#define _CARDEFFECT_H

#include "dominion.h"

/* Function to handle the Baron card. 'choice' is the decision to discard an estate (1)
or gain an estate (0). Also needs the game state and the card's position in hand. */
void playBaron(int choice, struct gameState *state, int handPos);

/* choice 1 is > 0 to gain coins while choice 2 is > 0 for redraw.*/
void playMinion(int choice1, int choice2, struct gameState *state, int handPos, int *bonus);

/* choice1 is the position in hand of which card is being revealed - cannot be the
same as the Ambassador being played.
choice2 is how many of the revealed card are being returned. Must be 0, 1, or 2.
Returns -1 on error, else 0		*/
int playAmbassador(int choice1, int choice2, struct gameState *state, int handPos);


#endif