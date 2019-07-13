/*
Author: Brad Powell
Unit test for the Mine dominion card.

Include in your makefile (cardEffect only if you have a separate file for card effects)
unittest1: unittest5.c dominion.o rngs.o cardEffect.o testHelp.o
	gcc -o unittest5 -g unittest5.c dominion.o rngs.o cardEffect.o testHelp.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "cardEffect.h"
#include "testHelp.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "Mine"

int main() {
	int i, currentPlayer;
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0;

	// Initialize the game
	int seed = 100;
	int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = { baron, minion, ambassador, tribute, mine, gardens, village, smithy, adventurer, great_hall };

	printf("--------------- Testing Card: %s ---------------\n", TESTCARD);

	// ---- Test 1: copper -> silver -----
	printf("\n----- TEST 1: copper -> silver -----\nDEBUG statements:\n");

	// Set up game
	initializeGame(numPlayers, k, seed, &G);
	currentPlayer = whoseTurn(&G);
	G.hand[currentPlayer][0] = copper;	// make sure there's a treasure to use
	choice1 = 1;
	choice2 = silver;
	updateCoins(currentPlayer, &G, 0);
	memcpy(&testG, &G, sizeof(struct gameState));

	// Add mine to hand
	testG.hand[currentPlayer][testG.handCount[currentPlayer]] = mine;
	handPos = testG.handCount[currentPlayer];
	testG.handCount[currentPlayer]++;

	// Play card
	playCard(handPos, choice1, choice2, choice3, &testG);

	printf("\n*~*~*~* Unit Tests *~*~*~*\n");
	printf("Expected buys: 1\t\tActual buys: %d\n", testG.numBuys);
	printf("Expected actions: 0\t\tActual actions: %d\n", testG.numActions);
	printf("Expected coin value: +1\t\tActual coins: +%d\n", testG.coins - G.coins);
	printf("Expected handCount: 5\t\tActual hancount: %d\n", testG.handCount[currentPlayer]);

	if (deckCheck(currentPlayer, &G, &testG) == 1) {
		printf("Deck ok.\t");
	}
	if (discardCheck(currentPlayer, &G, &testG) == 1) {
		printf("Discard ok.\t");
	}
	if (oppNoChange(&G, &testG) == 1) {
		printf("Opponents ok.\n");
	}
	
	// Check only the target treasure changes
	printf("Supply pile %d should change: ", silver);
	kingdomNoChange(&G, &testG);






}