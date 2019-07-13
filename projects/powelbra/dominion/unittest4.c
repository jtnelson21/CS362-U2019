/*
Author: Brad Powell
Unit test for the Tribute dominion card.

Include in your makefile (cardEffect only if you have a separate file for card effects)
unittest1: unittest4.c dominion.o rngs.o cardEffect.o testHelp.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o cardEffect.o testHelp.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "cardEffect.h"
#include "testHelp.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "Tribute"

int main() {
	int i, currentPlayer, player;
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0;

	// Initialize the game
	int seed = 100;
	int numPlayers = 3;
	struct gameState G, testG;
	int k[10] = { baron, minion, ambassador, tribute, mine, gardens, village, smithy, adventurer, great_hall };

	printf("--------------- Testing Card: %s ---------------\n", TESTCARD);

	// ---- Test 1: 2 action cards -----
	printf("\n----- TEST 1: 2 action cards -----\nDEBUG statements:\n");

	// Set up game
	initializeGame(numPlayers, k, seed, &G);
	currentPlayer = whoseTurn(&G);
	player = currentPlayer + 1;
	G.deck[player][G.deckCount[player] - 1] = baron;
	G.deck[player][G.deckCount[player] - 2] = smithy;
	memcpy(&testG, &G, sizeof(struct gameState));

	// Add tribute to hand
	testG.hand[currentPlayer][testG.handCount[currentPlayer]] = tribute;
	handPos = testG.handCount[currentPlayer];
	testG.handCount[currentPlayer]++;

	// Play card
	playCard(handPos, choice1, choice2, choice3, &testG);

	printf("\n*~*~*~* Unit Tests *~*~*~*\n");
	printf("Expected buys: 1\t\tActual buys: %d\n", testG.numBuys);
	printf("Expected actions: 3\t\tActual actions: %d\n", testG.numActions);
	printf("Expected coins: +0\t\tActual coins: +%d\n", testG.coins - G.coins);
	printf("Expected handCount: 4\t\tActual handCount: %d\n", testG.handCount[currentPlayer]);

	if (deckCheck(currentPlayer, &G, &testG) == 1) {
		printf("Deck ok.\n");
	}
	if (discardCheck(currentPlayer, &G, &testG) == 1) {
		printf("Discard ok.\n");
	}
	if (kingdomNoChange(&G, &testG) == 1) {
		printf("Kingdom piles ok.\n");
	}

	// Check changes in next player (discard +2, deck -2)
	player = currentPlayer + 1;
	printf("Next player expected dicardCount: 2\tActual discardCount: %d\n", testG.discardCount[player]);
	printf("Next player expected deckCount: %d\tActual deckCount: %d\n", G.deckCount[player] - 2, testG.deckCount[player]);
	if (handCheck(player, &G, &testG) == 1) {
		printf("Next player's hand ok.\n");
	}

	// Check next next player is untouched
	player++;
	if (deckCheck(player, &G, &testG) == 1) {
		printf("Third player deck ok.\t");
	}
	if (handCheck(player, &G, &testG) == 1) {
		printf("Third player hand ok.\t");
	}
	if (discardCheck(player, &G, &testG) == 1) {
		printf("Third player discard ok.\n");
	}






}