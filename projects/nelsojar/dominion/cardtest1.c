#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define TESTCARD "mine"

int main()
{
	int numPlayers = 2;
	int seed = 10;
	int i, j;
	int k[10] = {tribute, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	
	struct gameState G, testG;

	printf("Test initializeGame\n\n");

	memcpy(&testG, &G, sizeof(struct gameState));	
	
	//initialize game
	initializeGame(numPlayers, k, seed, &testG);
	
	printf("Test 1: Set Correct Number of Players\n");
	printf("\tNumber of Players: %d \t Expected Number of Players: %d\n", numPlayers, testG.numPlayers);
	myAssert(numPlayers, testG.numPlayers);

	printf("Test 2: Correct Curse Cards for 2 Players\n");
	printf("\tCurse Cards: %d \t Expected Curse Cards: %d\n", testG.supplyCount[0], 10);
	myAssert(testG.supplyCount[0], 10);

	printf("Test 3: Correct Number of Victory Cards for 4 Players\n");
	numPlayers = 4;
	memcpy(&testG, &G, sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, &testG);
	printf("\tEstate Cards: %d \t Estate Cards Expected: %d\n", testG.supplyCount[estate], 12);
	myAssert(testG.supplyCount[estate], 12);

	printf("\tDuchy Cards: %d \t Duchy Cards Expected: %d\n", testG.supplyCount[duchy], 12);
	myAssert(testG.supplyCount[duchy], 12);

	printf("\tProvince Cards: %d \t Province Cards Expected: %d\n", testG.supplyCount[province], 12);
	myAssert(testG.supplyCount[province], 12);

	printf("Test 4: Set Correct Number of Kingdom Cards\n");
	for (i = adventurer; i <= treasure_map; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (k[j] == i)
			{
				if (k[j] == great_hall || k[j] == gardens)
				{
					if (numPlayers == 2)
					{
						printf("\tCard: %d\n", k[i]);
						printf("\tSupply Count: %d \t Expected Supply Count: %d\n", testG.supplyCount[i], 8);
						myAssert(testG.supplyCount[i], 8);
						break;
					}
					else
					{
						printf("\tCard: %d\n", k[j]);
						printf("\tSupply Count: %d \t Expected Supply Count: %d\n", testG.supplyCount[i], 12);
						myAssert(testG.supplyCount[i], 12);
						break;
					}
				}
				else
				{
					printf("\tCard: %d\n", k[j]);
					printf("\tSupply Count: %d \t Expected Supply Count: %d\n", testG.supplyCount[i], 10);
					myAssert(testG.supplyCount[i], 10);
					break;
				}
			}
		}
	}
	
	printf("Test 5: Player Decks Contain 3 Estates and 7 Copper\n");
	for (i = 0; i < numPlayers; i++)
	{
		int eCount = 0;
		int cCount = 0;
		for (j = 0; j < 10; j++)
		{
			if (testG.deck[i][j] == estate)
			{
				eCount++;
			}
			if (testG.deck[i][j] == copper)
			{
				cCount++;
			}
		}
		printf("\tPlayer: %d\n", i + 1);
		printf("\tNumber of Estates: %d \t Expected Estates: %d\n", eCount, 3);
		myAssert(eCount, 3);
		printf("\tNumber of Copper: %d \t Expected Copper: %d\n", cCount, 7);
		myAssert(cCount, 7);
	}

	printf("Test 6: Initialized Player's First Turn\n");
	printf("\tOutpost Played: %d \t Expected Outpost Played: %d\n", testG.outpostPlayed, 0);
	myAssert(testG.outpostPlayed, 0);
	printf("\tPhase: %d, \t Expected Phase: %d\n", testG.phase, 0);
	myAssert(testG.phase, 0);
	printf("\tNumber of Actions: %d \t Expected Actions: %d\n", testG.numActions, 1);
	myAssert(testG.numActions, 1);
	printf("\tPlayed Cards: %d \t Expected Played Cards: %d\n", testG.playedCardCount, 0);
	myAssert(testG.playedCardCount, 0);
	

	printf("Test 7: Player's Hand Count is 5\n");
	printf("\tPlayer Hand Count: %d \t Expected Hand Count: %d\n", testG.handCount[0], 5);
	myAssert(testG.handCount[0], 5);
	
	return 0;	
}
