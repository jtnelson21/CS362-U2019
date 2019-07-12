/*
Author: Brad Powell
Unit test for the Baron dominion card.

Include in your makefile (cardEffect only if you have a separate file for card effects)
unittest1: unittest2.c dominion.o rngs.o cardEffect.o testHelp.o
	gcc -o unittest2 -g unittest1.c dominion.o rngs.o cardEffect.o testHelp.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "cardEffect.h"
#include "testHelp.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "minion"

int main() {
	int i, currentPlayer;
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0;

	// Initialize the game
	int seed = 100;
	int numPlayers = 3;
	struct gameState G, testG;
	int k[10] = { baron, minion, ambassador, tribute, mine, gardens, village, smithy, adventurer, great_hall };

	printf("--------------- Testing Card: %s ---------------\n", TESTCARD);

	// ---- Test 1: +2 coins -----
	printf("\n----- TEST 1: Choice1 = 1; +2 coins -----\n");

	// Set up game
	initializeGame(numPlayers, k, seed, &G);
	currentPlayer = whoseTurn(&G);
	choice1 = 1;
	choice2 = 0;
	memcpy(&testG, &G, sizeof(struct gameState));

	// Add minion to hand
	testG.hand[currentPlayer][testG.handCount[currentPlayer]] = minion;
	handPos = testG.handCount[currentPlayer];
	testG.handCount[currentPlayer]++;

	// Play card
	playCard(handPos, choice1, choice2, choice3, &testG);

	printf("Expected buys: 1\t\tActual buys: %d\n", testG.numBuys);
	printf("Expected actions: 1\t\tActual actions: %d\n", testG.numActions);
	printf("Expected coins: +2\t\tActual coins: +%d\n", testG.coins - G.coins);

	if (handNoChange(&G, &testG) == 1) {
		printf("Hand ok.\n");
	}
	if (deckNoChange(&G, &testG) == 1) {
		printf("Deck ok.\n");
	}
	if (discardNoChange(&G, &testG) == 1) {
		printf("Discard ok.\n");
	}
	if (oppNoChange(&G, &testG) == 1) {
		printf("Opponents ok.\n");
	}
	if (kingdomNoChange(&G, &testG) == 1) {
		printf("Kingdom piles ok.\n");
	}
	
}