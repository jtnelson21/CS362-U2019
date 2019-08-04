#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "baron"
#define _CRT_SECURE_NO_WARNINGS 


int checkBaron(struct gameState* post, int choice1, int currentPlayer, int* c1Card, int* c1NoCard, int* c2)
{
	int cmpState = 0;
	int choice2 = 0, choice3 = 0, handPos = 0, coin_bonus = 0;
	struct gameState pre;
	int flag = 0;
	//struct gameState *pre = (struct gameState*)malloc(sizeof(struct gameState));

	//Copy game state for pre and post comparison
	memcpy(&pre, post, sizeof(struct gameState));

	int result;
	result = cardEffect(baron, choice1, choice2, choice3, post, handPos, &coin_bonus);
	pre.numBuys++;


	if (choice1 > 0)
	{
		//Check Coins Added, Baron discarded from hand and to pile
		for (int i = 0; i < pre.handCount[currentPlayer]; i++)
		{
			if (pre.hand[currentPlayer][i] == estate)
			{
				flag = 1;
				pre.coins += 4;
				pre.discardCount[currentPlayer]++;
				pre.handCount[currentPlayer]--;

				cmpState = memcmp(&pre, post, sizeof(struct gameState));
				if (cmpState != 0)
				{
					*c1Card = *c1Card + 1;	//Counter for this error
				}
				break;
			}
			//If no card player gains estate
			else if (i == pre.handCount[currentPlayer] - 1 && flag == 0)
			{
				pre.discardCount[currentPlayer]++;
				pre.supplyCount[estate]--;

				cmpState = memcmp(&pre, post, sizeof(struct gameState));
				if (cmpState != 0)
				{
					*c1NoCard = *c1NoCard + 1;
				}
				break;
			}
			else
				;
		}
	}
	else
	{
		//If Choice 2 is false
		if (supplyCount(estate, post) > 0)
		{
			pre.discardCount[currentPlayer]++;
			pre.supplyCount[estate]--;

			cmpState = memcmp(&pre, post, sizeof(struct gameState));
			if (cmpState != 0)
			{
				*c2 = *c2 + 1;
			}
		}
	}

	//assert(result == 0);

	//Uncomment to inspect errors
/*	if (cmpState != 0)
	{
		printf("baron_play Exp: currentplayer: %d, choice1: %d, handCount: %d, deckCount: %d, discardCount: %d, numBuys: %d, coins: %d, estate supplyCount: %d\n",
			currentPlayer, choice1, pre.handCount[currentPlayer], pre.deckCount[currentPlayer], pre.discardCount[currentPlayer], pre.numBuys, pre.coins,
			pre.supplyCount[estate]);

		printf("baron_play Pst: currentplayer: %d, choice1: %d, handCount: %d, deckCount: %d, discardCount: %d, numBuys: %d, coins: %d, estate supplyCount: %d\n",
			currentPlayer, choice1, post->handCount[currentPlayer], post->deckCount[currentPlayer], post->discardCount[currentPlayer], post->numBuys, post->coins,
			post->supplyCount[estate]);
	}
*/	return 0;

}


int main()
{
	int n, i, p;
	int handCount, choice1, currentPlayer, numPlayers;
	int c1Card = 0.0;
	int c1NoCard = 0.0;
	int c2 = 0.0;
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
		numPlayers = rand() % 3 + 1;	//Randomize # of players between 1-3 (index 0)
		choice1 = rand() % 2;
		G.deckCount[numPlayers] = rand() % MAX_DECK;
		G.discardCount[numPlayers] = rand() % MAX_DECK;
		G.handCount[numPlayers] = rand() % MAX_HAND;
		initializeGame((numPlayers + 1), k, 10, &G);

		currentPlayer = rand() % (numPlayers + 1) + 0;	//Pick random player from 0-3 to play card
		checkBaron(&G, choice1, currentPlayer, &c1Card, &c1NoCard, &c2);
	}
	//	exit(0);
	printf("Errors: Choice1, Card Found - %d\n", c1Card);
	printf("Errors: Choice1, False      - %d\n\n", c2);

	printf("SIMPLE FIXED TESTS.\n");

	//Tests choice1 when a player has no estate in hand
	for (i = 0; i < 30; i++)
	{
		currentPlayer = 0;
		choice1 = 1;

		initializeGame(2, k, 10, &G);
		G.deckCount[currentPlayer] = 10;
		G.discardCount[currentPlayer] = 10;
		G.handCount[currentPlayer] = 5;
		for (p = 0; p < G.handCount[currentPlayer]; p++)
		{
			G.hand[currentPlayer][p] = mine;
		}

		checkBaron(&G, choice1, currentPlayer, &c1Card, &c1NoCard, &c2);
	}

	printf("Errors: Choice1, No Card    - %d\n", c1NoCard);
	printf("Uncomment lines 73-83 checkBaron function to see results\n");
	//	TestRandom();
	return 0;

}