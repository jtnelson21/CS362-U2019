#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define TESTCARD "tribute"

int main()
{
	int choice1 = 0, choice2 = 0, choice3 = 0, handPos = 0, coin_bonus = 0;
	int currentPlayer = 0;
	int nextPlayer = currentPlayer + 1;
	int numPlayers = 2;
	int seed = 10;
	int i, cmp;
	int tributeRevealedCards[2];
	int **tributeTest = &tributeRevealedCards[0];
	int k[10] = {tribute, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	
	struct gameState G, testG;
	
	//initialize game
	initializeGame(numPlayers, k, seed, &G);
	
	printf("Testing Card: %s\n\n", TESTCARD);

	G.deckCount[nextPlayer] = 1;
	//Copy game state to test state
	memcpy(&testG, &G, sizeof(struct gameState));
	
	//Play the test game state card
	cardEffect(tribute, choice1, choice2, choice3, &testG, handPos, &coin_bonus);
	

	printf("Test 1: Discard Count + Deck Count of Next Player <= 1 and Deck Count > 0  \n");
	printf("\tNext Player Revealed Card: %d\t Expected Revealed Card: %d\n", *tributeTest[0], G.deck[nextPlayer][G.deckCount[nextPlayer] - 1]);
	int lastDeck = G.deck[nextPlayer][G.deckCount[nextPlayer] - 1];
	cmp = myAssert(*tributeTest[0], lastDeck);
	printf("\tNext Player Deck Count: %d\t Expected Deck Count %d\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer] - 1);
	cmp = myAssert(testG.deckCount[nextPlayer], (G.deckCount[nextPlayer] - 1));


	printf("\tTest if the Card is a Treasure, Victory, or Action Card \n");
	if (*tributeTest[0] == copper || *tributeTest[0] == silver || *tributeTest[0] == gold)
	{
		printf("\tCard is a Treasure Card: +2 coins\n");
		printf("\tCurrent Player Coins: %d\t Expected Coins: %d\n", testG.coins, G.coins + 2);
		cmp = myAssert(testG.coins, (G.coins + 2));
	}
	else if (*tributeTest[0] == estate || *tributeTest[0] == duchy || *tributeTest[0] == province || *tributeTest[0] == gardens || *tributeTest[0] == great_hall)
	{
		printf("\tCard is a Victory Card: Draw Card + 1 to Hand\n");
		printf("\tCurrent Player Hand Count: %d\t Expected Hand Count: %d\n", testG.handCount[currentPlayer], (G.handCount[currentPlayer]));
		cmp = myAssert(testG.handCount[currentPlayer], G.handCount[currentPlayer]);
	}
	else
	{
		printf("\tCard is an Action Card: +2 Actions\n");
		printf("\tCurrent Player Actions: %d\t Expected Actions: %d\n", testG.numActions, G.numActions + 2);
		cmp = myAssert(testG.numActions, (G.numActions + 2));
	}

	printf("Test2: Discard Count + Deck Count of Next Player <= 1 and Deck Count = 0\n");
	
	//Set up to test a hand count of 0 and discard pile of 5 estate cards
	tributeTest = NULL;	//Clear
	G.deckCount[nextPlayer] = 0;
	G.discardCount[nextPlayer] = 5;
	for (i = 0; i < 5; i++)
	{
		G.discard[nextPlayer][i] = estate;
	}
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(tribute, choice1, choice2, choice3, &testG, handPos, &coin_bonus);

	printf("\tTest that Discard Pile is Sent to Next Player's Deck\n");
	printf("\tNext Player's Deck Count: %d\t Expected Deck Count: %d\n", testG.deckCount[nextPlayer], G.discardCount[nextPlayer]);
	cmp = myAssert(testG.deckCount[nextPlayer], G.discardCount[nextPlayer]);
}
