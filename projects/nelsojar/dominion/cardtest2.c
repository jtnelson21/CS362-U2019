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
	
	printf("Testing shuffle: \n\n");
	
	
	//initialize game
	initializeGame(numPlayers, k, seed, &G);
	

	//Copy game state to test state
	memcpy(&testG, &G, sizeof(struct gameState));

	shuffle(currentPlayer, &testG);
	printf("Test 1: Shuffle called on a deck size of: %d\n", testG.deckCount[currentPlayer]);
	printf("\tDeck order was shuffled\n");
	for (i = 0; i < testG.deckCount[currentPlayer]; i++)
	{
		if( testG.deck[currentPlayer][i] != G.deck[currentPlayer][i])
		{
			printf("\tPassed\n");
			break;
		}
		if (i = (testG.deckCount[currentPlayer] - 1))
		{
			printf("\tFailed\n");
		}
		
	}

	//Copy game state to test state
	memcpy(&testG, &G, sizeof(struct gameState));
	
	testG.deckCount[currentPlayer] = 0;
	int testShuff = shuffle(currentPlayer, &testG);
	//testG.deckCount[currentPlayer] = 0;
	printf("Test 2: Deck Count is: %d, Do Nothing \n", testG.deckCount[currentPlayer]);
	printf("Shuffle Return Value: %d \t Expected Shuffle Return Value: %d\n", testShuff, -1);
	myAssert(testShuff, -1);

}
