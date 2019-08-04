#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "minion"


int checkMinion(struct gameState* post, int choice1, int choice2, int currentPlayer, int* c1Error, int* c2Error)
{
	int cmpState;
	int choice3 = 0, handPos = 0, coin_bonus = 0;
	struct gameState pre;
	//struct gameState *pre = (struct gameState*)malloc(sizeof(struct gameState));
	int shufFlag = 0;

	//Copy game state for pre and post comparison
	memcpy(&pre, post, sizeof(struct gameState));

	int result;
	result = cardEffect(minion, choice1, choice2, choice3, post, handPos, &coin_bonus);

	pre.numActions++;
	pre.handCount[currentPlayer] -= 1;
	pre.playedCardCount += 1;


	if (choice1)
	{
		//Check Coins Added, Baron discarded from hand and to pile
		pre.coins += 2;
		cmpState = memcmp(&pre, post, sizeof(struct gameState));
		if (cmpState != 0)
		{
			*c1Error = *c1Error + 1;	//Counter for this error
		}

	}
	else if (choice2)
	{
		for (int i = 0; i < pre.numPlayers; i++)
		{
			//printf("DeckC: %d\n", pre.deckCount[i]);
			//Flag to signify a shuffle occured
			if (pre.deckCount[i] <= 4)
			{
				shufFlag = 1;
			}

			if (i == currentPlayer || pre.handCount[i] >= 5)
			{
				pre.playedCardCount += pre.handCount[i];

				//Update Discard Count for a Re-shufle
				if (shufFlag == 1)
				{
					pre.deckCount[i] += pre.discardCount[i];
					pre.discardCount[i] = 0;
					pre.deckCount[i] -= 4;
				}
				else
				{
					//pre.discardCount[currentPlayer] += 4;
					pre.deckCount[i] -= 4;
				}

				pre.handCount[i] = 4;
			}
		}


		cmpState = memcmp(&pre, post, sizeof(struct gameState));
		if (cmpState != 0)
		{
			*c2Error = *c2Error + 1;	//Counter for this error
		}
	}

	//Uncomment to inspect errors
/*	if (cmpState != 0)
	{
		printf("minion_play Exp: currentplayer: %d, choice1: %d, choic2: %d, handCount: %d, deckCount: %d, discardCount: %d, numActions: %d, coins: %d, playedCardCount: %d\n",
		currentPlayer, choice1, choice2, pre.handCount[currentPlayer], pre.deckCount[currentPlayer], pre.discardCount[currentPlayer], pre.numActions, pre.coins,
	pre.playedCardCount);

		printf("minion_play Pst: currentplayer: %d, choice1: %d, choice2: %d handCount: %d, deckCount: %d, discardCount: %d, numActions: %d, coins: %d, playedCardCount: %d\n",
		currentPlayer, choice1, choice2, post->handCount[currentPlayer], post->deckCount[currentPlayer], post->discardCount[currentPlayer], post->numActions, post->coins, post->playedCardCount);
	}
*/	return 0;
}

int main()
{
	srand(time(0));
	int n, i, p;
	int handCount, choice1, choice2;
	int currentPlayer = 0;
	int numPlayers;
	int c1Error = 0.0;
	int c2Error = 0.0;
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	struct gameState G;
	//struct gameState *G = (struct gameState*)malloc(sizeof(struct gameState));	//Use for a deeper comparison?

	printf("Testing Card: %s\n\n", TESTCARD);
	printf("RANDOM TESTS.\n");

	SelectStream(2);
	PutSeed(3);

	for (n = 0; n < 10000; n++)
	{
		for (i = 0; i < sizeof(struct gameState); i++)
		{
			((char*)& G)[i] = rand() % 256;//floor(Random() * 256);
		}

		//Used rand() because Random fron rngs.c wasn't giving random numbers
		numPlayers = rand() % 3 + 1;

		//Makes it so 2 choices can't have the same values
		choice1 = rand() % 2;
		if (choice1 == 0)
		{
			choice2 = 1;
		}
		else
		{
			choice2 = 0;
		}

		//initializeGame(currentPlayer, k, 10, &G);
		for (p = 0; p < numPlayers; p++)
		{
			//initializeGame(currentPlayer, k, 10, &G);
			G.deckCount[p] = rand() % MAX_DECK;
			G.discardCount[p] = rand() % MAX_DECK;
			G.handCount[p] = rand() % MAX_HAND;
		}
		initializeGame((numPlayers + 1), k, 10, &G);
		currentPlayer = rand() % (numPlayers + 1) + 0;
		//printf("Players: %d\n", G.numPlayers);	
		checkMinion(&G, choice1, choice2, currentPlayer, &c1Error, &c2Error);
	}
	//	exit(0);

	printf("Total Tests: %d\n", n);
	printf("Errors: Choice1, True  - %d\n", c1Error);
	printf("Errors: Choice2, False - %d\n\n", c2Error);
	printf("Uncomment lines 84-93 checkMinion function to check results\n");

	//	TestRandom();
	return 0;
}
