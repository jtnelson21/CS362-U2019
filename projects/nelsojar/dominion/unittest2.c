#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define TESTCARD "minion"

int main()
{
	int choice1 = 0, choice2 = 0, choice3 = 0, handPos = 0, coin_bonus = 0;
	int thisPlayer = 0;
	int numPlayers = 2;
	int seed = 10;
	int i, cmp;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	
	struct gameState G, testG;
	
	//initialize game
	initializeGame(numPlayers, k, seed, &G);
	
	printf("Testing Card: %s\n\n", TESTCARD);

	//Copy game state to test state
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	
	//Play the test game state card
	cardEffect(minion, choice1, choice2, choice3, &testG, handPos, &coin_bonus);

	//Test Choice1 true, +1 Action
	printf("Test 1: Choice1 true, +1 Action\n");
	int addAction = 1;
	printf("\tNumber of Actions: %d\t Expected Number of Actions: %d\n", testG.numActions, G.numActions + addAction);
	cmp = myAssert(testG.numActions, G.numActions + addAction);

	//Test Choice1 true, +2 Coins
	printf("Test 2: Choice1 true, +2 Coins\n");
	printf("\tNumber of Coins: %d\t Expected Number of Coins: %d\n", testG.coins, G.coins + 2);
	cmp = myAssert(testG.coins, G.coins + 2);

	
	//Copy game state to test state
	memcpy(&testG, &G, sizeof(struct gameState));
	choice2 = 1;
	choice1 = 0;

	//Play the test game state card
	cardEffect(minion, choice1, choice2, choice3, &testG, handPos, &coin_bonus);
	
	
	//Test Choice2 true, discard card from hand
	printf("Test 3: Choice2 true, 4 Hand Count \n");
	printf("\tCurrent Player Hand Count: %d\t Expected Hand Count: %d\n", testG.handCount[thisPlayer], 4);
	cmp = myAssert(testG.handCount[thisPlayer], 4);

	//Test Choice21 true, deck count reduces
	printf("Test 4: Choice2 true, -4 Deck Count \n");
	printf("\tCurrent Player Deck Count: %d\t Expected Deck Count: %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 4);
	int expectedDeck = G.deckCount[thisPlayer] - 4;
	cmp = myAssert(testG.deckCount[thisPlayer], expectedDeck);

	//Test Choice2 true, discard hand
	printf("Test 5: Choice2 true, Discard Count\n");
	printf("\tCurrent Player Discard Count: %d\t Expected Discard Count: %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	int expectedDiscard = G.discardCount[thisPlayer];
	cmp = myAssert(testG.discardCount[thisPlayer], expectedDiscard);

	//Test Choice2 true, played card count
	printf("Test 6: Choice2 true, Played Card Count\n");
	printf("\tPlayed Card Count: %d\t Expected Played Card Count: %d\n", testG.playedCardCount, G.playedCardCount + G.handCount[thisPlayer]);
	int expectedPlayedCount = G.playedCardCount + G.handCount[thisPlayer];
	cmp = myAssert(testG.playedCardCount, expectedPlayedCount);

		
	//Test other players cards
	printf("Test 7: Choice2 true, Other Players 4 Hand Count, -4 Deck Count\n");
	for (i = 0; i < numPlayers; i++)
	{	
		if (i != thisPlayer)
		{
			printf("\tPlayer: %d\n", i);

			printf("\tHand Count >=5 Before Card Play: %d\n", testG.handCount[1]);
			
			//Run through tests if the other players has >= 5 Cards
			if (G.handCount[i] >=5)
			{
				printf("\tPassed\n");
				printf("\tHandCount: %d\t Expectd Hand Count: %d\n", testG.handCount[i], 4);
				myAssert(testG.handCount[i], 4);

				printf("\tDeck Count: %d \t Expected Deck Count: %d\n", testG.deckCount[i], G.deckCount[i] - 4);
				expectedDeck = G.deckCount[i] - 4;
				cmp = myAssert(testG.deckCount[i], expectedDeck);

				printf("\tDiscard Count: %d\t Expected Discard Count: %d\n", testG.discardCount[i], G.discardCount[i] + G.handCount[i]);
				expectedDiscard = G.discardCount[i] + G.handCount[i];
				cmp = myAssert(testG.discardCount[i], expectedDiscard);
			}
			else
			{
				printf("\tFailed\n");
			}
		}
	}

	return 0;

}
