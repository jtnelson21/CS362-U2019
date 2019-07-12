/*
Author: Brad Powell
Unit test for the Baron dominion card.

Include in your makefile (cardEffect only if you have a separate file for card effects)
unittest1: unittest1. dominion.o rngs.o cardEffect.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o cardEffect.o $CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "cardEffect.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "baron"

int main() {
	int i;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0 bonus = 0;

		
	// Initialize the game
	int seed = 100;
	int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = { baron, minion, ambassador, tribute, mine, gardens, village, smithy, market, great_hall };

	initializeGame(numPlayers, k, seed, &G);
	// Since initialize game gives the player a basic deck, the starting hand has at least 2 estates.

	printf("----- Testing Card: %s -----\n", TESTCARD);
	
	// ---- Test 1: Discard estate with estate in hand -----
	printf("----- TEST 1: Choice1 = 1; discard estate -----\n");

	// copy the game state for comparison
	memcpy(&testG, &G, sizeof(struct gameState));

	// Add baron to the hand
	int currentPlayer = whoseTurn(testG);
	testG->hand[currentPlayer][handCount] = baron;
	handpos = testG->handCount[currentPlayer]
	testG->handCount[currentPlayer]++;

	cardEffect(baron, choice1, choice2, choice3, &testG, handPos, &bonus);
}