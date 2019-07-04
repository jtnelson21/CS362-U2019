#include "cardEffect.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

void playBaron(int choice, struct gameState *state, int handPos) {
	int currentPlayer = whoseTurn(state);

	state->numBuys++;//Increase buys by 1!
	if (choice > 0) {//Boolean true or going to discard an estate
		int p = 0;//Iterator for hand!
		int card_not_discarded = 1;//Flag for discard set!
		while (card_not_discarded) {
			if (state->hand[currentPlayer][p] == estate) {//Found an estate card!
				state->coins += 4;//Add 4 coins to the amount of coins
				state->discard[currentPlayer][state->discardCount[currentPlayer]] = state->hand[currentPlayer][p];	// Add to the discard pile
				state->discardCount[currentPlayer]++;
				for (; p < state->handCount[currentPlayer]; p++) {	// Starts from current position in hand and continues
					state->hand[currentPlayer][p] = state->hand[currentPlayer][p + 1];
				}
				state->hand[currentPlayer][state->handCount[currentPlayer]] = -1;
				state->handCount[currentPlayer]--;
				card_not_discarded = 0;//Exit the loop
			}
			else if (p > state->handCount[currentPlayer]) {
				if (DEBUG) {
					printf("No estate cards in your hand, invalid choice\n");
					printf("Must gain an estate if there are any\n");
				}
				gainCard(estate, state, 0, currentPlayer);
				card_not_discarded = 0;//Exit the loop
			}

			else {
				p++;//Next card
			}
		}
	}

	else {
		gainCard(estate, state, 0, currentPlayer);
	}

	// Discard card, using 0 to put it in the played pile
	discardCard(handPos, currentPlayer, state, 0);

}

void playMinion(int choice1, int choice2, struct gameState *state, int handPos) {
	int currentPlayer = whoseTurn(state);
	int i, j;	// Variables for loops
	//+1 action
	state->numActions++;

	if (choice1) {		//+2 coins
		state->coins = state->coins + 2;
		//discard card from hand
		discardCard(handPos, currentPlayer, state, 0);
	}

	else if (choice2) {		//discard hand, redraw 4, other players with 5+ cards discard hand and draw 4
		//discard hand ********* May need to be changed to a manual discard since this function puts cards into the played area ***********
		while (numHandCards(state) > 0) {
			discardCard(handPos, currentPlayer, state, 0);
		}

		//draw 4
		for (i = 0; i < 4; i++) {
			drawCard(currentPlayer, state);
		}

		//other players discard hand and redraw if hand size > 4
		for (i = 0; i < state->numPlayers; i++) {
			if (i != currentPlayer) {
				if (state->handCount[i] > 4) {
					//discard hand
					while (state->handCount[i] > 0) {
						discardCard(handPos, i, state, 0);
					}

					//draw 4
					for (j = 0; j < 4; j++) {
						drawCard(i, state);
					}
				}
			}
		}
	}
}