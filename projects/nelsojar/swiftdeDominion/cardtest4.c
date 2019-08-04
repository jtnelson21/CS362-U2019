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
	int pWin = 0;
	int wIndex;
	int k[10] = {tribute, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int players[MAX_PLAYERS];
	
	struct gameState G, testG;
	
	printf("Testing getWinners: \n\n");
	
	
	//initialize game
	initializeGame(numPlayers, k, seed, &G);
	

	//Copy game state to test state
	memcpy(&testG, &G, sizeof(struct gameState));

	getWinners(players, &testG);
	
	printf("Test 1: Only One Winner (Player) Set as 1\n");
	
	for (i = 0; i < numPlayers; i++)
	{
		printf("\tPlayer %d: %d\n", i + 1, players[i]);
		if (players[i] == 1)
		{
			pWin++;
			wIndex = i;
		}
	
	}
	myAssert(pWin, 1);
}
