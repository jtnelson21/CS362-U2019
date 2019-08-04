#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "tribute"


int checkTribute(struct gameState* post, int currentPlayer, int* c1Error)
{
	int cmpState, i;
	int tributeCards[2];
	int choice1 = 0, choice2 = 0, choice3 = 0, handPos = 0, coin_bonus = 0;	//Required for cardEffect function
	currentPlayer = currentPlayer - 1;
	int nextPlayer = currentPlayer + 1;

	struct gameState pre;
	//struct gameState *pre = (struct gameState*)malloc(sizeof(struct gameState));

	//Copy game state for pre and post comparison
	memcpy(&pre, post, sizeof(struct gameState));

	if (currentPlayer == pre.numPlayers - 1)
	{
		nextPlayer = 0;
	}

	int result;
	result = cardEffect(tribute, choice1, choice2, choice3, post, handPos, &coin_bonus);

	//Discard played Card from Hand
	pre.handCount[currentPlayer]--;
	pre.playedCardCount++;

	if (pre.discardCount[nextPlayer] + pre.deckCount[nextPlayer] <= 1)
	{
		if (pre.deckCount[nextPlayer] > 0)
		{
			tributeCards[0] = pre.deck[nextPlayer][pre.deckCount[nextPlayer] - 1];
			pre.deckCount[nextPlayer]--;
		}
		else if (pre.discardCount[nextPlayer] > 0)
		{
			tributeCards[0] = pre.discard[nextPlayer][pre.discardCount[nextPlayer] - 1];
			pre.discardCount[nextPlayer]--;
		}
		else
		{
			;
		}
	}
	else
	{
		if (pre.deckCount[nextPlayer] == 0)
		{
			pre.deckCount[nextPlayer] += pre.discardCount[nextPlayer];
			pre.discardCount[nextPlayer] = 0;
		}

		tributeCards[0] = pre.deck[nextPlayer][pre.deckCount[nextPlayer] - 1];
		tributeCards[1] = pre.deck[nextPlayer][pre.deckCount[nextPlayer] - 1];
		pre.deckCount[nextPlayer] -= 2;
	}

	if (tributeCards[0] == tributeCards[1])
	{
		pre.playedCardCount++;
		tributeCards[1] = -1;
	}

	for (i = 0; i < 2; i++)
	{
		if (tributeCards[i] == copper || tributeCards[i] == silver || tributeCards[i] == gold)
		{
			pre.coins += 2;
		}
		else if (tributeCards[i] == estate || tributeCards[i] == duchy || tributeCards[i] == province)
		{
			for (i = 0; i < 2; i++)
			{
				if (pre.deckCount[nextPlayer] <= 0)
				{
					pre.deckCount[currentPlayer] += pre.discardCount[nextPlayer];
					pre.discardCount[currentPlayer] = 0;
					pre.handCount[currentPlayer]++;
					pre.deckCount[currentPlayer]--;
				}
				else
				{
					pre.deckCount[currentPlayer]--;
					pre.handCount[currentPlayer]++;
				}
			}
		}
		else
		{
			pre.numActions += 2;
		}
	}


	cmpState = memcmp(&pre, post, sizeof(struct gameState));
	if (cmpState != 0)
	{
		*c1Error = *c1Error + 1;	//Counter for this error
	}

	//Uncomment to inspect errors
/*	if (cmpState != 0)
	{
		printf("tribute_play Pre: currentplayer: %d, handCount: %d, deckCount: %d, discardCount: %d, numActions: %d, coins: %d, playedCardCount: %d\n",
		currentPlayer, pre.handCount[currentPlayer], pre.deckCount[currentPlayer], pre.discardCount[currentPlayer], pre.numActions, pre.coins, pre.playedCardCount);

		printf("tribute_play Pst: currentplayer: %d, handCount: %d, deckCount: %d, discardCount: %d, numActions: %d, coins: %d, playedCardCount: %d\n",
		currentPlayer, post->handCount[currentPlayer], post->deckCount[currentPlayer], post->discardCount[currentPlayer], post->numActions, post->coins, post->playedCardCount);

		//Next Player
		printf("tribute_play Pre: nextplayer: %d, handCount: %d, deckCount: %d, discardCount: %d, playedCardCount: %d\n",
		nextPlayer, pre.handCount[nextPlayer], pre.deckCount[nextPlayer], pre.discardCount[nextPlayer], pre.playedCardCount);

		printf("tribute_play Pst: nextplayer: %d, handCount: %d, deckCount: %d, discardCount: %d, playedCardCount: %d\n",
		nextPlayer, post->handCount[nextPlayer], post->deckCount[nextPlayer], post->discardCount[nextPlayer], post->playedCardCount);
	}
*/
	return 0;
}

int main()
{
	srand(time(0));
	int n, i, p;
	int handCount;
	int currentPlayer = 0;
	int numPlayers;
	int c1Error = 0.0;
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
		checkTribute(&G, currentPlayer, &c1Error);
	}
	//	exit(0);

	printf("Total Tests: %d\n", n);
	printf("Errors: %d\n", c1Error);
	printf("Uncomment lines 112-127 checkTribute function to comparison results\n");

	//	TestRandom();
	return 0;
}
