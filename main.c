#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct Deck {
    int cards[52];
    int cardsLeft;
};


struct Player {
    int totalHandValue;
    int cards[16];
    int cardIndex;
    int cardsInHand;
};


void dealCards(struct Player* p, struct Deck* d) {
    int deckIndex = (rand()%d->cardsLeft+1);
    //Checks if the index in the array is empty, if so rerolls
    while(d->cards[deckIndex] == 0) {
        deckIndex = (rand()%d->cardsLeft+1);
    }
    //Adds the card from the deck into the player hand
    p->cards[p->cardIndex] = d->cards[deckIndex];
    p->totalHandValue += p->cards[p->cardIndex];
    //Sets the card in deck array to 0
    d->cards[deckIndex] = 0;
    d->cardsLeft -= 1;
    //Increments the card index and cards in hand for the player
    p->cardIndex += 1;
    p->cardsInHand += 1;
}

void initDeck(struct Deck* d) {
    d->cardsLeft = 52;
    int cardCount = 0;
    int suitCount = 0;
    int cardVal = 1;
    int acePresent = 0;
    while(cardCount < 52) {
        if(suitCount == 4) {
            if(cardVal == 11) {
                acePresent = 1;
            }
            suitCount = 0;
            cardVal += 1;
        }
        switch (cardVal) {
            case 11:
                if(acePresent == 1) {
                    cardVal = 10;
                }
                break;
            case 12:
                cardVal = 10;
                break;
            default:
                break;
        }

        d->cards[cardCount] = cardVal;
        cardCount += 1;
        suitCount += 1;
    }
}

void initPlayer(struct Player* p) {
    p->cardIndex = 0;
    p->totalHandValue = 0;
    p->cardsInHand = 0;
}

int dealMoreCards() {
    printf("Would you like another card? (y/n): ");
    char choice;
    scanf(" %c", &choice);
    if(choice == 'Y' || choice == 'y') {
        return 1;
    } else {
        return 0;
    }
}

void displayHand(struct Player* p) {
    printf("\nYou currently have: ");
    for(int i = 0; i < p->cardsInHand; i++) {
        printf("%i ",p->cards[i]);
    }
    printf("\n");
}

void evalWinner(struct Player* p, struct Player* d) {
    printf("\nYour hand score is: %i\n", p->totalHandValue);
    printf("\nThe dealers hand score is: %i\n", d->totalHandValue);
    if(p->totalHandValue == 21) {
        printf("Blackjack! You won.");
        return;
    } else if (d->totalHandValue == 21) {
        printf("Blackjack! Dealer won.");
        return;
    }
    if(p->totalHandValue > 21 && d->totalHandValue > 21){
        printf("You both busted.");
        return;
    } else if(p->totalHandValue > 21) {
        printf("Dealer won!");
        return;
    } else if (d->totalHandValue > 21) {
        printf("You won, dealer busted!");
        return;
    }
    if(p->totalHandValue < 21 && p->totalHandValue > d->totalHandValue) {
        printf("You won!");
        return;
    } else {
        printf("You lost!");
        return;
    }
}



void run() {
    printf("Welcome to Black Jack, would you like to play? (y/n)\n");
    char choice;
    scanf(" %c", &choice);
    int running = 0;
    struct Player play;
    initPlayer(&play);
    struct Player dealer;
    initPlayer(&dealer);
    struct Deck currDeck;
    initDeck(&currDeck);
    if(choice == 'y' || choice == 'Y') {
        running = 1;
    };
    while(running == 1) {
        dealCards(&dealer, &currDeck);
        dealCards(&play, &currDeck);
        displayHand(&play);
        int moreCards = dealMoreCards();
        char hit;
        if(moreCards == 1) {
            hit = 'y';
        }
        while(dealer.totalHandValue < 17) {
            dealCards(&dealer, &currDeck);
        }
        while(moreCards == 1) {
            if (hit == 'y' || hit == 'Y') {
                dealCards(&play, &currDeck);
                displayHand(&play);
            } else if (hit == 'n' || hit == 'N') {
                moreCards = 0;
            }
            if(play.totalHandValue > 21) {
                printf("You went above 21, you lost.");
                moreCards = 0;
                break;
            }
            moreCards = dealMoreCards();
        }
        running = 0;
    }
    evalWinner(&play, &dealer);
}

int main() {
    srand(time(0));
    run();
    return 0;
}
