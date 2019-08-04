#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define TESTCARD "ambassador"

int main()
{
	int choice1 = 0, choice2 = 0, choice3 = 0, handPos = 0, coin_bonus = 0;
	int thisPlayer = 0;
	int numPlayers = 2;
	int seed = 10;
	int i, j, cmp;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	
	struct gameState G, testG;
	
	//initialize game
	initializeGame(numPlayers, k, seed, &G);
	
	printf("Testing Card: %s\n\n", TESTCARD);

	//Copy game state to test state
	memcpy(&testG, &G, sizeof(struct gameState));
	
	//Play the test game state card
	 cardEffect(ambassador, choice1, choice2, choice3, &testG, handPos, &coin_bonus);
	

	//Test that the game remains unchanged if bad choice1
	printf("Test 1: Choice1 Equals HandPos, Game unchanged \n");
	printf("\tCurrent Player Supply Count: %d\t Expected SupplyCount: %d\n", testG.supplyCount[testG.hand[thisPlayer][choice1]], G.supplyCount[G.hand[thisPlayer][choice1]]);
	cmp = myAssert(testG.supplyCount[testG.hand[thisPlayer][choice1]], G.supplyCount[G.hand[thisPlayer][choice1]]);		

	//Test Choice 2 More than 2 cards selected - Unchanged
	printf("Test 2: Choice2 > 2, Game Unchanged\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	choice2 = 3;
	cardEffect(ambassador, choice1, choice2, choice3, &testG, handPos, &coin_bonus);
	printf("\tCurrent Player Supply Count: %d\t Expected SupplyCount: %d\n", testG.supplyCount[testG.hand[thisPlayer][choice1]], G.supplyCount[G.hand[thisPlayer][choice1]]);
	cmp = myAssert(testG.supplyCount[testG.hand[thisPlayer][choice1]], G.supplyCount[G.hand[thisPlayer][choice1]]);

	//Test Choice 2 Number of Cards Added to Supply then Subtracted by Numplayers - 1
	printf("Test 3: The Current Player Has Enough Cards To Discard, +2 Card To Supply\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	choice2 = 1;
	cardEffect(ambassador, choice1, choice2, choice3, &testG, handPos, &coin_bonus);
	int expectedSupply = G.supplyCount[G.hand[thisPlayer][choice1]] + choice2 - (numPlayers - 1);	//Add Choice2 to supply, then remove 1 for each player
	printf("\tCurrent Player Supply Count: %d\t Expected SupplyCount: %d\n", testG.supplyCount[testG.hand[thisPlayer][choice1]], expectedSupply);
	cmp = myAssert(testG.supplyCount[testG.hand[thisPlayer][choice1]], expectedSupply);

	printf("Test 4: Each Other Player Gains A Copy of Reveal Card\n");
	int testCard;
	int gCard;
	for (i = 0; i < numPlayers; i++)
	{
		testCard = 0;
		gCard = 0;
		if (i != thisPlayer)
		{
			printf("\tPlayer: %d\n", i);
			//Search Test Hand For Revealed Card, get total
			for (j = 0; j < testG.discardCount[i]; j++)
			{
				if (testG.discard[i][j] == testG.discard[0][choice1])
				{
					testCard++;
				}
			}
			//Search Pre Test Hand For Revealed Card, get total
			for (j = 0; j < G.discardCount[i];  j++)
			{
				printf("J: %d\n", G.hand[0][j]);
				
				if (G.discard[i][j] == testG.discard[0][choice1])
				{
					gCard++;
				}
			}
			printf("\tCount of Revealed Card: %d\t Expected Count: %d\n", testCard, gCard);
			int expectedRevealCount = gCard;
			cmp = myAssert(testCard, expectedRevealCount);
		}
	} 
	return 0;
}	
