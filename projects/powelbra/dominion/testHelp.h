// Functions to test various aspects of the game state

#ifndef _TESTHELP_H
#define _TESTHELP_H

#include "dominion.h"

// All NoChange functions return -1 if a change was detected, 1 otherwise

// Checks all kingdom supply piles
int kingdomNoChange(struct gameState *G, struct gameState *test);

// Checks opponents' hands, decks, and discards; current player must be 0.
int oppNoChange(struct gameState *G, struct gameState *test);

// Checks current player's hand
int handNoChange(struct gameState *G, struct gameState *test);

// Checks current player's deck
int deckNoChange(struct gameState *G, struct gameState *test);

// Check current player's discard
int discardNoChange(struct gameState *G, struct gameState *test);


#endif