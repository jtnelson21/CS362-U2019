#include "dominion.h"
#include "dominion_helpers.h"
#include "testHelp.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Verify none of the supply piles have changed
// Returns -1 On fail, 1 on success
int kingdomNoChange(struct gameState *G, struct gameState *testG) {
	int i;
	// Check all supply piles and verify no change has occured
	for (i = 0; i <= treasure_map; i++) {
		if (G->supplyCount[i] != testG->supplyCount[i]) {
			printf("Supply %d changed.\n", i);
			return -1;
		}
	}
	// If the loop finishes, no change detected
	return 1;
}

// Verify the players were unchanged
// Returns -1 on fail, 1 on success
int oppNoChange(struct gameState *G, struct gameState *testG) {
	int i, j, x = 1;	// x is returned; set to success by default
	for (i = 1; i < testG->numPlayers; i++) {
		// Verify hand, deck, and discard counts have changed.
		if (G->handCount[i] != testG->handCount[i]) {
			printf("Player %d's handCount changed.\n", i);
			x = -1;
		}
		if (G->deckCount[i] != testG->deckCount[i]) {
			printf("Player %d's deckCount changed.\n", i);
			x = -1;
		}
		if (G->discardCount[i] != testG->discardCount[i]) {
			printf("Player %d's discardCount changed.\n", i);
			x = -1;
		}
		// Verify cards in hand are same
		for (j = 0; j < testG->handCount[i]; j++) {
			if (G->hand[i][j] != testG->hand[i][j]) {
				printf("Player %d's hand change at position %d\n", i, j);
				x = -1;
			}
		}
		// Verify cards in deck are same
		for (j = 0; j < testG->deckCount[i]; j++) {
			if (G->deck[i][j] != testG->deck[i][j]) {
				printf("Player %d's deck change at position %d\n", i, j);
				x = -1;
			}
		}
		// Verify cards in discard are same
		for (j = 0; j < testG->discardCount[i]; j++) {
			if (G->discard[i][j] != testG->discard[i][j]) {
				printf("Player %d's discard change at position %d\n", i, j);
				x = -1;
			}
		}
	}
	// If loop ends, no change detected
	return x;
}

// Verify hand remains unchanged; Assumes played card was last in hand
// Returns -1 on fail, 1 on success
int handNoChange(struct gameState *G, struct gameState *testG) {
	int currentPlayer = whoseTurn(G);
	int i;

	if (G->handCount[currentPlayer] != testG->handCount[currentPlayer]) {
		printf("handCount changed.\n");
		return -1;
	}
	else {
		for (i = 0; i < G->handCount[currentPlayer]; i++) {
			if (G->hand[currentPlayer][i] != testG->hand[currentPlayer][i]) {
				printf("Card at position %d changed.\n", i);
				printf("Original: %d\t\tNew: %d\n", G->hand[currentPlayer][i], testG->hand[currentPlayer][i]);
				return -1;
			}
		}
		// If loop finished, all is well
		return 1;
	}
}

// Verify deck remains unchanged;
// Returns -1 on fail, 1 on success
int deckNoChange(struct gameState *G, struct gameState *testG) {
	int currentPlayer = whoseTurn(G);
	int i;

	if (G->deckCount[currentPlayer] != testG->deckCount[currentPlayer]) {
		printf("deckCount changed.\n");
		return -1;
	}
	else {
		for (i = 0; i < G->deckCount[currentPlayer]; i++) {
			if (G->deck[currentPlayer][i] != testG->deck[currentPlayer][i]) {
				printf("Card at position %d changed.\n", i);
				printf("Original: %d\t\tNew: %d\n", G->deck[currentPlayer][i], testG->deck[currentPlayer][i]);
				return -1;
			}
		}
		// If loop finished, all is well
		return 1;
	}
}