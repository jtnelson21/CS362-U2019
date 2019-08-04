#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


int main()
{
	int choice1 = 0, choice2 = 0, choice3 = 0, handPos = 0, coin_bonus = 0;
	int currentPlayer = 0;
	int numPlayers = 2;
	int seed = 10;
	int i, cmp;
	int k[10] = {tribute, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	
	struct gameState G, testG;
	
	printf("Testing endTurn: \n\n");
	
	
	//initialize game
	initializeGame(numPlayers, k, seed, &G);
	

	//Copy game state to test state
	memcpy(&testG, &G, sizeof(struct gameState));

	endTurn(&testG);
	
	printf("Test 1: Hand is Discarded\n");
	printf("\tCurrent Hand Count: %d \t Expected Hand Count: %d\n", testG.handCount[currentPlayer], 0);
	myAssert(testG.handCount[currentPlayer], 0);

	printf("\tCurrent Discard Count: %d \t Expected Discard Count: %d\n", testG.discardCount[currentPlayer], G.handCount[currentPlayer]);
	myAssert(testG.discardCount[currentPlayer], G.handCount[currentPlayer]);

	printf("Test 2: Advance Whose Turn to the Next Player\n");
	printf("\twhoseTurn Player: %d \t Expected Player: %d\n", testG.whoseTurn, G.whoseTurn + 1);
	myAssert(testG.whoseTurn, (G.whoseTurn + 1));	

	printf("Test 3: Player Stats Reset\n");
	printf("\tCurrent Number Actions: %d \t Expected Number  Actions: %d\n", testG.numActions, 1);
	myAssert(testG.numActions, 1);
	printf("\tCurrent Number Buys: %d \t Expected Number Buys: %d\n", testG.numBuys, 1);
	myAssert(testG.numBuys, 1);
	printf("\tCurrent Played Card Count: %d \t Expected Played Card Count: %d\n", testG.playedCardCount, 0);
	myAssert(testG.playedCardCount, 0);

	printf("Test 4: Player Coins Updated\n");
	int testCoins;
	for (i = 0; i < testG.handCount[whoseTurn(&testG)]; i++)
	{
		if (testG.hand[whoseTurn(&testG)][i] == copper)
		{
			testCoins += 1;
		}
		else if (testG.hand[whoseTurn(&testG)][i] == silver)
		{
			testCoins += 2;
		}
		else if (testG.hand[whoseTurn(&testG)][i] == gold)
		{
			testCoins += 3;
		}
	}
	printf("\tSet Next Player Coins: %d \t Expected Coins: %d\n", testG.coins, testCoins);
	myAssert(testG.coins, testCoins);
}
