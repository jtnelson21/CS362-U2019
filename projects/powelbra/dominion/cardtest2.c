/*
Author: Brad Powell
Unit test for the shuffle dominion function.

Include in your makefile (cardEffect only if you have a separate file for card effects)
cardtest1: cardtest1.c dominion.o rngs.o cardEffect.o testHelp.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o cardEffect.o testHelp.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTFUNCTION "Shuffle"

int main() {
	int i, j, sentinel;	// 4 players to work with most number of decks at once
	int errTest[4];
	// k just for initialization
	int k[10] = { baron, minion, ambassador, tribute, mine, gardens, village, smithy, adventurer, great_hall };
	int seed = 100;
	struct gameState G, testG;

	initializeGame(4, k, seed, &G);

	// Set players with different deck/discard/hand counts
	// Player 0: All cards in deck, set to different cards
	// Should have shuffled deck
	G.handCount[0] = 0;
	G.discardCount[0] = 0;
	G.deckCount[0] = 10;
	for (i = 0; i < G.deckCount[0]; i++) {
		G.deck[0][i] = i;	// Curse, estate, etc.
	}

	// Player 1: Copy of player 0
	// Make sure two shuffles actually change each time (on same load of seed)
	G.handCount[1] = 0;
	G.discardCount[1] = 0;
	G.deckCount[1] = 10;
	for (i = 0; i < G.deckCount[1]; i++) {
		G.deck[1][i] = i;
	}

	// Player 2: 5 cards each in deck, hand, discard
	// Should shuffle deck, leave hand and discard alone
	G.handCount[2] = 5;
	G.discardCount[2] = 5;
	G.deckCount[2] = 5;
	for (i = 0; i < G.handCount[2]; i++) {
		G.hand[2][i] = estate;
	}
	for (i = 0; i < G.discardCount[2]; i++) {
		G.discard[2][i] = estate;
	}
	for (i = 0; i < G.deckCount[2]; i++) {
		G.deck[2][i] = i+10;	// all action cards
	}

	// Player 3: 0 cards in deck, 5 in hand, 5 in discard
	// Should lead to an error
	G.handCount[3] = 5;
	G.discardCount[3] = 5;
	G.deckCount[3] = 0;
	for (i = 0; i < G.handCount[3]; i++) {
		G.hand[3][i] = i + 5;
	}
	for (i = 0; i < G.discardCount[3]; i++) {
		G.discard[3][i] = i + 10;
	}

	// Copy configuration to our test game
	memcpy(&testG, &G, sizeof(struct gameState));


	printf("---------- Testing Function: %s ----------\n", TESTFUNCTION);
	testG.playedCardCount = 4;
	for (i = 0; i < 4; i++) {
		errTest[i] = shuffle(i, &testG);
	}
	
	// ----- Test 1: Player 0 -----
	printf("\n----- TEST 1: Normal deck -----\n");
	sentinel = 0;
	printf("Returned values should be 0: %d\t%d\n", errTest[0], errTest[1]);
	if (testG.deckCount[0] == G.deckCount[0]) {
		printf("Deck count ok.\n");
	}
	// Compare decks before and after
	for (i = 0; i < testG.deckCount[0]; i++) {
		if (testG.deck[0][i] != G.deck[0][i]) {
			sentinel = 1;
			break;
		}
	}
	if (sentinel) {
		printf("Shuffle Player 0 ok.\n");
	}
	else {
		printf("Player 0 deck didn't shuffle.\n");
	}
	// Compare player's 0 and 1 decks for difference
	sentinel = 0;
	for (i = 0; i < testG.deckCount[0]; i++) {
		if (testG.deck[0][i] != testG.deck[1][i]) {
			sentinel = 1;
			break;
		}
	}
	if (sentinel) {
		printf("Multiple shuffle of same deck ok.\n");
	}
	else {
		printf("Second shuffle of same deck the same (should be different).\n");
	}

	// ----- Test 2: Discard, hand, played -----
	printf("\n----- TEST 2: Shuffle ignores discard, hand, and played cards -----\n");
	printf("Returned value should be 0: %d\n", errTest[2]);
	if (testG.handCount[2] == G.handCount[2]) {
		printf("Hand count ok.\t");
	}
	else {
		printf("Hand count NOT ok.\t");
	}
	if (testG.discardCount[2] == G.discardCount[2]) {
		printf("Discard count ok.\t");
	}
	else {
		printf("Discard count NOT ok.\t");
	}
	if (testG.deckCount[2] == G.deckCount[2]) {
		printf("Deck count ok.\t");
	}
	else {
		printf("Deck count NOT ok.\t");
	}
	if (testG.playedCardCount == 4) {
		printf("Played count ok.\n");
	}
	else {
		printf("Played count NOT ok.\n");
	}

	// ----- Test 3: Error -----
	printf("\n----- TEST 3: Empty deck, nothing changes -----\n");
	printf("Returned value should be -1: %d\n", errTest[3]);
	if (testG.handCount[3] == G.handCount[3]) {
		printf("Hand count ok.\t");
	}
	else {
		printf("Hand count NOT ok.\t");
	}
	if (testG.discardCount[3] == G.discardCount[3]) {
		printf("Discard count ok.\t");
	}
	else {
		printf("Discard count NOT ok.\t");
	}
	if (testG.deckCount[3] == G.deckCount[3]) {
		printf("Deck count ok.\t");
	}
	else {
		printf("Deck count NOT ok.\t");
	}


	return 0;
}