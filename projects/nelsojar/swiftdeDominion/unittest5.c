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
	int choice1 = 0, choice2 = 0, choice3 = 0, handPos = 0, coin_bonus = 0;
	int currentPlayer = 0;
	int numPlayers = 2;
	int seed = 10;
	int i, cmp;
	int k[10] = {tribute, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	
	struct gameState G, testG;
	
	//initialize game
	initializeGame(numPlayers, k, seed, &G);
	
	printf("Testing Card: %s\n\n", TESTCARD);

	//Copy game state to test state
	memcpy(&testG, &G, sizeof(struct gameState));
	
	choice1 = 3;
	//Play the test game state card
	cardEffect(mine, choice1, choice2, choice3, &testG, handPos, &coin_bonus);
	
	printf("current: %d\n", testG.hand[currentPlayer][choice1]);
	//Test for failure if not a treasure card
	printf("Test 1: If Choice1 is not a treasure card (<4 or >6), no changes\n");
	printf("\tchoice1: %d\n", testG.hand[currentPlayer][choice1]);
	printf("\tCurrent Player Hand Count: %d\t Expected Hand Count: %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer]);
	cmp = myAssert(testG.handCount[currentPlayer], (G.handCount[currentPlayer]));
	printf("\tCurrent Played Count: %d\t Expected Played Count: %d\n", testG.playedCardCount, G.playedCardCount);
	cmp = myAssert(testG.playedCardCount, G.playedCardCount);

	printf("Test 2: If Choice2 is not a card (<0 or >26 , do nothing\n");
	//Copy game state to test state
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 4;
	choice2 = 27;
	cardEffect(mine, choice1, choice2, choice3, &testG, handPos, &coin_bonus);
	printf("\tchoice1: %d\n", choice1);
	printf("\tchoice2: %d\n", choice2);
	printf("\tCurrent Player Hand Count: %d\t Expected Hand Count: %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer]);
	cmp = myAssert(testG.handCount[currentPlayer], (G.handCount[currentPlayer]));
	printf("\tCurrent Player Discard Count: %d\t Expected Discard Count: %d\n", testG.discardCount[currentPlayer], G.discardCount[currentPlayer]);
	cmp = myAssert(testG.discardCount[currentPlayer], (G.discardCount[currentPlayer]));

	printf("Test 3: If Choice2 is a valid card\n");
	//Copy game state to test state
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 4;
	choice2 = 1;
	printf("\tchoice1: %d\n", choice1);
	printf("\tchoice2: %d\n", choice2);
	cardEffect(mine, choice1, choice2, choice3, &testG, handPos, &coin_bonus);	
	printf("\tCurrent Player Hand Count: %d\t Expected Hand Count: %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer]  - 1);
	cmp = myAssert(testG.handCount[currentPlayer], (G.handCount[currentPlayer] - 1));
	printf("\tCurrent Player Discard Count: %d\t Expected Discard Count: %d\n", testG.discardCount[currentPlayer], G.discardCount[currentPlayer]);
	cmp = myAssert(testG.discardCount[currentPlayer], (G.discardCount[currentPlayer]));


	//Copy game state to test state
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 4;
	choice2 = 16;
	int chosenCost = getCost(testG.hand[currentPlayer][choice1]);	//Checks cost of hand card efore play
	cardEffect(mine, choice1, choice2, choice3, &testG, handPos, &coin_bonus);
	printf("Test 4: Cost of choice1 +  3 > cost of choice2\n");
	printf("\tchoice1: %d\n", choice1);
	printf("\tchoice2: %d\n", choice2);
	printf("\tChoice1 Cost + 3: %d\t Choice2 Cost: %d\n", chosenCost + 3, getCost(choice2));
	if (chosenCost + 3 > getCost(choice2))
	{
		printf("\tPassed\n");
	}
	else
	{
		printf("\tFailed\n");
	}

}	
