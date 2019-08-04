#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define TESTCARD "baron"


int main()
{
	int choice1 = 0, choice2 = 0, choice3 = 0, handPos = 0, coin_bonus = 0;
	int thisPlayer = 0, currentPlayer = 0;
	int numPlayers = 2;
	int seed = 10;
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

	struct gameState G, testG;

	//initialize game
	initializeGame(numPlayers, k, seed, &G);

	printf("Testing Card: %s\n", TESTCARD);
	//printf("Test 1: +1 Buy Added\n");

	//Copy game state to test state
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;

	//Play the test game state card
	cardEffect(baron, choice1, choice2, choice3, &testG, handPos, &coin_bonus);

	//Test Choice1 true, +1 Buy
	int newBuys = 1;
	printf("Test 1: Choice1 true - +1 Buy Added\n");
	printf("\tNumber of Buys: %d \t Expected Buys: %d\n", testG.numBuys, G.numBuys + newBuys);
	int cmp = myAssert(testG.numBuys, G.numBuys + newBuys);

	//Test Choice1 true, Discard Estate
	printf("Test 2: Choice1 true - Discard an Estate From Hand\n");
	int tCardCount = 0;
	int gCardCount = 0;
	int i, j;

	for (i = 0; i < G.handCount[thisPlayer]; i++)
	{

		if (G.hand[currentPlayer][i] == estate)
		{
			gCardCount++;
		}
	}
	for (j = 0; j < testG.handCount[thisPlayer]; j++)
	{
		if (testG.hand[currentPlayer][j] == estate)
		{
			tCardCount++;
		}
	}
	printf("\tEstate Card: %d \t Expected Estate Cards: %d\n", tCardCount, (gCardCount - 1));
	cmp = myAssert(tCardCount, (gCardCount - 1));

	//Test Choice1 true, +4 Coins
	printf("Test 3: Choice1 true - +4 Coins\n");
	printf("\tCoins: %d \t Expected Coins: %d\n", testG.coins, G.coins + 4);
	cmp = myAssert(testG.coins, G.coins + 4);


	//Copy game state to test state	
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 0;

	//Play the Baron card
	cardEffect(baron, choice1, choice2, choice3, &testG, handPos, &coin_bonus);


	//Test Choice1 false, +1 Buy
	newBuys = 1;
	printf("Test 4: Choice1 false - +1 Buys\n");
	printf("\tNumber of Buys: %d \t Expected Buys: %d\n", testG.numBuys, G.numBuys + newBuys);
	cmp = myAssert(testG.numBuys, G.numBuys + newBuys);


	//Test Choice1 false, +1 Estate to Discard
	printf("Test 5: Choice1 false - +1 Estate in Discard\n");
	tCardCount = 0;
	gCardCount = 0;

	for (i = 0; i < G.discardCount[currentPlayer]; i++)
	{
		if (G.discard[currentPlayer][i] == estate)
		{
			gCardCount++;
		}
	}
	for (j = 0; j < testG.discardCount[currentPlayer]; j++)
	{
		if (testG.discard[currentPlayer][j] == estate)
		{
			tCardCount++;
		}
	}
	printf("\tNumber of Estate: %d \t Expected Estate: %d\n", tCardCount, (gCardCount + 1));
	cmp = myAssert(tCardCount, (gCardCount + 1));


	return 0;

}
