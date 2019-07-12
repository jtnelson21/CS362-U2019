/*
Author: Brad Powell
Unit test for the Baron dominion card.

Include in your makefile (cardEffect only if you have a separate file for card effects)
unittest1: unittest1.c dominion.o rngs.o cardEffect.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o cardEffect.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "cardEffect.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "baron"

// Verify none of the supply piles have changed
// Returns -1 On fail, 1 on success
int kingdomNoChange(struct gameState *G, struct gameState *testG) {
	int i;
	// Check all supply piles and verify no change has occured
	for (i = 0; i <= treasure_map; i++) {
		if (G->supplyCount[i] != testG->supplyCount[i]) {
			return -1;
		}
	}
	// If the loop finishes, no change detected
	return 1;
}

// Verify the players were unchanged
// Returns -1 on fail, 1 on success
int oppNoChange(struct gameState *G, struct gameState *testG) {
	int i, j;
	for (i = 1; i < testG->numPlayers; i++) {
		// Verify hand, deck, and discard counts have changed.
		if (G->handCount[i] != testG->handCount[i] || G->deckCount[i] != testG->deckCount[i] || G->discardCount[i] != testG->discardCount[i]) {
			return -1;
		}
		// Verify cards in hand are same
		for (j = 0; j < testG->handCount[i]; j++) {
			if (G->hand[i][j] != testG->hand[i][j]) {
				return -1;
			}
		}
		// Verify cards in deck are same
		for (j = 0; j < testG->deckCount[i]; j++) {
			if (G->deck[i][j] != testG->deck[i][j]) {
				return -1;
			}
		}
		// Verify cards in discard are same
		for (j = 0; j < testG->discardCount[i]; j++) {
			if (G->discard[i][j] != testG->discard[i][j]) {
				return -1;
			}
		}
	}
	// If loop ends, no change detected
	return 1;
}

int main() {
	int i;
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

		
	// Initialize the game
	int seed = 100;
	int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = { baron, minion, ambassador, tribute, mine, gardens, village, smithy, adventurer, great_hall };

	initializeGame(numPlayers, k, seed, &G);
	// Since initialize game gives the player a basic deck, the starting hand has at least 2 estates.

	printf("----- Testing Card: %s -----\n", TESTCARD);
	
	// ---- Test 1: Discard estate with estate in hand -----
	printf("----- TEST 1: Choice1 = 1; discard estate -----\n");

	// copy the game state for comparison
	memcpy(&testG, &G, sizeof(struct gameState));

	// Add baron to the hand
	int currentPlayer = whoseTurn(&testG);
	testG.hand[currentPlayer][testG.handCount[currentPlayer]] = baron;
	handPos = testG.handCount[currentPlayer];
	testG.handCount[currentPlayer]++;

	cardEffect(baron, choice1, choice2, choice3, &testG, handPos, &bonus);
	updateCoins(currentPlayer, &testG, bonus);

	printf("Expected buys: 2\tActual buys: %d\n", testG.numBuys);
	printf("Expected actions: 0\tActual actions: %d\n", testG.numActions);
	printf("Expected coins: +4\tActual coins: +%d\n", testG.coins - G.coins);
	printf("Expected handCount: 4\tActual handCount: %d\n", testG.handCount[currentPlayer]);
	printf("Expected discardCount: 1\tActual discardCount: %d\n", testG.discardCount[currentPlayer]);
	printf("Expected top discard: %d\tActual top discard: %d\n", estate, testG.discard[currentPlayer][testG.discardCount[currentPlayer] - 1]);
	printf("Expected deckCount: 5\tActual deckCount: %d\n", testG.deckCount[currentPlayer]);

	// Count estates in current and previous hands
	int prevEstates = 0, curEstates = 0;
	for (i = 0; i < testG.handCount[currentPlayer]; i++) {
		if (testG.hand[currentPlayer][i] == estate) {
			curEstates++;
		}
		if (G.hand[currentPlayer][i] == estate) {
			prevEstates++;
		}
	}
	// Previous hand has one more card, so check if that last card is an estate
	if (G.hand[currentPlayer][G.handCount[currentPlayer] - 1] == estate) {
		prevEstates++;
	}
	if (curEstates == prevEstates) {
		printf("Estate count incorrect!\n");
	}
	if (kingdomNoChange(&G, &testG) == -1) {
		printf("A kingdom supply changed!\n");
	}
	if (oppNoChange(&G, &testG) == -1) {
		printf("An opponent's state changed!\n");
	}


}


